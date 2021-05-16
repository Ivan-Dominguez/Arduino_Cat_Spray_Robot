#include <NewPing.h>
#include <Servo.h>

//PIR values
int PIRVccPin = 7;
int PIROutputPin = 6;

//ultrasound values
int triggerPin = 10;
int echoPin = 11;
int ultrasoundVccPin = 13;
int minDistance_cm = 0;
int maxDistance_cm = 150;

//servo values
int servoPin = 8;
int initialAngle = 0;
int finalAngle = 35;

NewPing sonar(triggerPin, echoPin, maxDistance_cm);
Servo servo;

void setup() {
  //setup PIR
  pinMode(PIRVccPin, OUTPUT);
  digitalWrite(PIRVccPin, HIGH);
  pinMode(PIROutputPin, INPUT);
  
  //setup ultrasound
  pinMode(ultrasoundVccPin,OUTPUT);
  digitalWrite(ultrasoundVccPin, HIGH);

  //setup servo
  servo.attach(servoPin);
  servo.write(initialAngle);
  Serial.begin(9600);
  delay(500);
}

void loop() { 
  
  if(isCatPresent()){
    turnSprayOn();
    delay(300);
    turnSprayOff();
  }
  
  delay(10);
}

void turnSprayOn(){
  Serial.println("Turning spray ON");
  servo.write(finalAngle);
  delay(300);
  servo.write(initialAngle);
  delay(300);
  servo.write(finalAngle);
  delay(300);
  servo.write(initialAngle);
}

void turnSprayOff(){
  Serial.println("Turning spray OFF");
  servo.write(finalAngle);
  delay(300);
  servo.write(initialAngle);
}


/* isCatPresent(): Checks if cat is standing in front of machine or just passing by */
bool isCatPresent(){
  int delayInSeconds = 3;
  
  for(int i = 0; i < delayInSeconds; i++){
    
     int movement = digitalRead(PIROutputPin);
     
     if(movement == HIGH) {
        Serial.print("Cat detected for ");
        Serial.print(i+1);
        Serial.println(" seconds");
        delay(1000);
        
     }else{
      Serial.println("No movement");
      return false;
     }
  }
  
  Serial.println("Cat satying confirmed");
  return true;
}
