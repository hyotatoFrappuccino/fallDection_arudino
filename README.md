# fallDection_arudino

제작 기간 : 23.7.4 ~ 23.7.7 (4일간) [K-4INT Maker Camp 창의혁신 DNA School 커넥트 교육 - 강원대학교 공학교육혁신센터]  
사용 프로그램 : 아두이노, 앱인벤터, 3D 프린터 모델링  
팀원 : 이효재([Github](https://github.com/hyotatoFrappuccino)), 이지혜([Github](https://github.com/2jihye10)), 최지원, 윤지환  

기능 : 화장실에서 실신(쓰러짐)했을 경우 이를 감지하여 보호자에게 알림을 전송

사용 센서 : 사운드 감지, 부저, 블루투스, 적외선  
알고리즘 : 초기 N분간 데시벨을 측정하여 평균을 낸 후, 평균을 기준으로 하여 변화폭의 평균을 구하여 이 값이 크면 활동 상태(샤워 시 크고작은 소리가 나므로), 작으면 쓰러짐 상태(가만히 샤워기만 틀고 있으면 샤워기 소리의 평균만 나타날 것이므로 변화폭의 평균이 적을 것이라 예상)로 판별하여 1차 경고 후 반응이 없으면 최종적으로 보호자 어플로 알림을 전송 (블루투스, 앱인벤터 이용)

<img width="400" alt="결과물" src="https://github.com/hyotatoFrappuccino/fallDection_arudino/assets/66837740/b1480533-318b-473f-8532-359b92a3b896">

[단순 시연 영상(유튜브 영상 바로가기 클릭)](https://youtu.be/e40RCA_U70M)
<img width="400" alt="결과물" src="https://github.com/hyotatoFrappuccino/fallDection_arudino/assets/66837740/a5c4e5ad-74b9-4d79-85f7-7f36f72c721f">

<img width="400" alt="수료증" src="https://github.com/hyotatoFrappuccino/fallDection_arudino/assets/66837740/13bff361-7da1-4f57-af68-e38106ee623c">
