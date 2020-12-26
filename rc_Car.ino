#include <SoftwareSerial.h>
SoftwareSerial BTSerial(11, 12);
String myString = "";
int Ain1 = 7;
int Ain2 = 8;
int pwmA = 6;
int Bin1 = 4;
int Bin2 = 5;
int pwmB = 3;
int mSpeed = 150;
void setup() {
  pinMode(Ain1, OUTPUT);
  pinMode(Ain2, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(Bin1, OUTPUT);
  pinMode(Bin2, OUTPUT);
  pinMode(pwmB, OUTPUT);
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  if(BTSerial.available()){
    char data = (char)BTSerial.read();
    myString += data;
    delay(5);
  }
  
  if(!myString.equals("")){
    Serial.println(myString);
    myString = "";
  }
  
  if(BTSerial.available()){
    char data = (char)BTSerial.read();
    Serial.println(data);
    switch(data){
      case 'f':
        forward();
        break;
      case 'b':
        backward();
        break;
      case 'l':
        left();
        break;
      case 'r':
        right();
        break;
      case 's':
        stopping();
        break;
    }
  }
}

void forward()
{
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, LOW);
  analogWrite(pwmA, mSpeed);
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(pwmB, mSpeed);
}

void backward()
{
  digitalWrite(Ain1, LOW);
  digitalWrite(Ain2, HIGH);
  analogWrite(pwmA, mSpeed);
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, HIGH);
  analogWrite(pwmB, mSpeed);
}

void left()
{
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, LOW);
  analogWrite(pwmA, 0);
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(pwmB, mSpeed);
}

void right()
{
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, LOW);
  analogWrite(pwmA, mSpeed);
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(pwmB, 0);
}

void stopping()
{
  digitalWrite(Ain1, LOW);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, LOW);
  //analogWrite(pwmB, 0);
}
