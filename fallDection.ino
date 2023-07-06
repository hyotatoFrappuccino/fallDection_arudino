#include <HuemonelabKit.h>
#include <SoftwareSerial.h>

using namespace std;
int SoundSensor = A0;  // 사운드 센서 설정
int moveSensor_Val; // 동작 감지 센서 측정 값 (1=동작, 0=가만히)
Buzzer buzzer(13); // 디지털 핀 중 PWM 상관 X
SoftwareSerial BTserial(2,3);
int infraredFront = 12; // 적외선 센서 앞
int infraredFrontVal = 0; // 임시 변수
int infraredBack = 11; // 적외선 센서 뒤  
int infraredBackVal = 0; // 임시 변수

const int sampleTime = 2; // (분)
const int sampleInterval = 5; // 샘플링 간격 (0.n초)
const int sampleNumber = sampleTime * 60 * 10 / sampleInterval; // 샘플 수
const double threshold = 0.5; // 평균값 임계점

int list[sampleNumber]; // 샘플 배열
int count = 0; // 배열 개수
int index = 0; // 현재 위치
int exist = 0; // 재실중 표시
int existDelay = 5000; // 입퇴장시 5초간 입퇴장 판별 X
int warnCount = 0;
int warning = 0; // 1차 경고 표시
int warningWait = 5; // 1차 경고 표시 후 n초간 반응 없으면 알림 전송

void setup() {
  Serial.begin(9600); // Serial 통신 시작
  BTserial.begin(9600);
  pinMode(SoundSensor,INPUT);
  pinMode(infraredFront, INPUT);
  pinMode(infraredBack, INPUT); 
}

void loop() {
  // ========= 적외선 센서 출입 인식 =========
  // 1. 입장
  if (!exist){
    if (!infraredFrontVal && !digitalRead(infraredFront)){
      infraredFrontVal = 1;
    }
    else if (infraredFrontVal && !digitalRead(infraredBack)){
      exist = 1;
      Serial.println("입장");
    }
  }

  // 2. 퇴장
  else if (exist){
    if (!infraredBackVal && !digitalRead(infraredBack)){
      infraredBackVal = 1;
   }
    else if (infraredBackVal && !digitalRead(infraredFront)){
      reset(0);
      Serial.println("퇴장");
    }
  }

  if (exist) { // 재실중인 경우에만 사운드 감지
    int sound = analogRead(SoundSensor);
    list[index] = sound;

    if (index >= sampleNumber) {
      index = 0;
    }
    else {
      index++;
    }

    if (count < sampleNumber){
      count++;

      // debug
      Serial.print("count: ");
      Serial.println(count);
    }
    else {
      // 샘플링의 평균을 구함
      int sum = 0;
      for (int i = 0; i < count; i++) {
          sum += list[i];
      }
      double average = (double)sum / count;
      Serial.print(", Average of sample: ");
      Serial.print(average);

      // 평균 변화폭의 평균을 구함
      double aveSum = 0;
      for (int i = 0; i < sampleNumber; i++) {
          aveSum += abs(average - list[i]);
      }
      
      double result = (double)aveSum / sampleNumber;
      Serial.print(",  Average of Variable Breadth: ");
      Serial.print(result);
      Serial.print(", warning: ");
      Serial.println(warning);
      Serial.print(", result <= threshold: ");
      Serial.print(result <= threshold);
      
      if (warning == 0 && result <= threshold) {
        warning = 1;
        Serial.print("위험 감지.");
//        buzzer.note('c');  // 도 출력 1초
//        buzzer.note('e');  // 미 출력 1초
//        buzzer.note('c');  // 도 출력 1초
//        buzzer.note('e');  // 미 출력 1초
//        buzzer.note('c');  // 도 출력 1초
//        buzzer.note('e');  // 미 출력 1초
        Serial.println(" 사운드센서에 큰 소리를 내거나 동작을 하여 위험 알림이 전송되지 않게하세요.");
        delay(2000);
      }
      if (warning == 1){
        warnCount++;
        if(result > threshold) {
          warning = 0;
          //buzzer.note('e'); // 출력 1초
          Serial.print("위험모드 해제.");
          reset(1);
          delay(2000);
        }
        else if (warnCount > 10) { // overflow 이슈로 직접 수 지정. (delay 고려)
          BTserial.print(1);
          Serial.print("앱 알림 전송");
          reset(1);
          delay(2000);
        }
      }
    }
  }
  delay(sampleInterval*100);
  // delay(100);
}

void reset(int exist_persist) {
  exist = exist_persist;
  count = 0;
  index = 0;
  warning = 0;
  warnCount = 0;
}
