#include<Wire.h>
//20201116 Subin Lee
const int MPU=0x68; 
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
const int trigPin = 9;
const int echoPin = 10;
long duration, dur;
int distance, dis;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(trigP, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoP, INPUT);
  Serial.begin(9600); // Starts the serial communication
  //gyro&acc
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  //Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
   Serial.println(distance);
    Serial.print('a');
    delay(1);
  Serial.println(duration);
  Serial.print('b');
  delay(1);
//
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read();  
  GyX=Wire.read()<<8|Wire.read();  
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read();  

  Serial.print(AcX);
  Serial.print('c');
  delay(1);
    Serial.print(AcY);
     Serial.print('d');
   delay(1);
  Serial.println(AcZ); 
  Serial.print('e');
  delay(10);
}
