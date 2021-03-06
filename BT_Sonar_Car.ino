#include <SoftwareSerial.h>
#define HEAD_LEFT_LED A0    //LED, 전조등
#define HEAD_RIGHT_LED A1    //LED, 전조등
#define TAIL_LEFT_LED A2    //LED, 미등
#define TAIL_RIGHT_LED A3    //LED, 미등
#define IN1 3       //DC 모터
#define IN2 4
#define ENA 5
#define IN3 8
#define IN4 7
#define ENB 6
#define TRIGPIN 9   //초음파센서
#define ECHOPIN 10
SoftwareSerial BTSerial(11, 12);   //블루투스 객체변수 생성
int mSpeed = 200;           //정방향속도
int rSpeed = mSpeed * 0.8;  //역방향속도
long duration;    //초음파 지속시간
float distance;   //초음파 거리

float getDistance(){   //초음파 거리 함수
  digitalWrite(TRIGPIN, HIGH);      
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);

  duration = pulseIn(ECHOPIN, HIGH);
  distance = (float)duration * 340 / 10000 / 2; 
  
  return distance;
}

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  
  analogWrite(HEAD_LEFT_LED, 0);
  analogWrite(HEAD_RIGHT_LED, 0);
  analogWrite(TAIL_LEFT_LED, 0);
  analogWrite(TAIL_RIGHT_LED, 0);
  BTSerial.begin(9600);
}

void loop() {
  distance = getDistance();
  if(distance < 15){         //거리가 15cm 보다 작으면
    flashHeadOn();
    Stop();
  }else{
    char ch;
    if(BTSerial.available()){  //블루투스에 데이터가 존재한다면
      ch = BTSerial.read();    // 그 데이터를 읽음
      if(ch=='f'){
        Forward();
      }
      else if(ch=='b'){
        Backward();
        flashTailOn();
      }
      else if(ch=='l'){
        turnLeft();
        flashLEFT();
      } 
      else if(ch=='r'){
        turnRight();
        flashRight();
      }
      else if(ch=='s'){
        Stop();
      }
    }
    flashAllOff();
  }
//  Serial.print(distance);
//  Serial.println("cm");
//  delay(1000);
}

void Stop(){    //정지
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void Forward(){   //전진
  analogWrite(ENA, mSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENB, mSpeed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void Backward(){    //후진
  analogWrite(ENA, rSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENB, rSpeed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft(){    //좌회전
  analogWrite(ENA, rSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENB, mSpeed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight(){   //우회전
  analogWrite(ENA, mSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENB, rSpeed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void flashHeadOn(){
  analogWrite(HEAD_LEFT_LED, 255);
  analogWrite(HEAD_RIGHT_LED, 255);
}

void flashTailOn(){
  analogWrite(TAIL_LEFT_LED, 255);
  analogWrite(TAIL_RIGHT_LED, 255);
  delay(500);
  analogWrite(TAIL_LEFT_LED, 0);
  analogWrite(TAIL_RIGHT_LED, 0);
  delay(500);
}

void flashLEFT(){
  analogWrite(HEAD_LEFT_LED, 255);
  delay(500);
  analogWrite(HEAD_RIGHT_LED, 0);
  delay(500);
}

void flashRight(){
  analogWrite(HEAD_RIGHT_LED, 255);
  delay(500);
  analogWrite(HEAD_LEFT_LED, 0);
  delay(500);
}

void flashAllOff(){
  analogWrite(HEAD_LEFT_LED, 0);
  analogWrite(HEAD_RIGHT_LED, 0);
  analogWrite(TAIL_LEFT_LED, 0);
  analogWrite(TAIL_RIGHT_LED, 0);
}
