#include <NewPing.h>
#include <Servo.h>

//ultrasound values
int triggerPin = 10;
int echoPin = 11;
int ultrasoundVccPin = 13;
int minDistance_cm = 0;
int maxDistance_cm = 83;

//servo values
int servoPin = 8;
int initialAngle = 0;
int finalAngle = 35;

NewPing sonar(triggerPin, echoPin, maxDistance_cm);
Servo servo;

void setup() {
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
  
  Serial.print("distance:");
  Serial.println(sonar.ping_cm());
  
  if(isCatPresent()){
    
    turnSprayOn();
    delay(300);
    turnSprayOff();
  }

 delay(1000);
}


void turnSprayOn(){
  Serial.print("Spray ON");
  servo.write(finalAngle);
  delay(300);
  servo.write(initialAngle);
  delay(300);
  servo.write(finalAngle);
  delay(300);
  servo.write(initialAngle);
}

void turnSprayOff(){
  servo.write(finalAngle);
  delay(300);
  servo.write(initialAngle);
}


/* isCatPresent(): Checks if cat is standing in front of machine or just passing by */
bool isCatPresent(){

  int catDistance = sonar.ping_cm();
  if(catDistance > minDistance_cm) {
    Serial.println("Cat passing by detected");
    
    //check again after delay
    delay(3000);
    catDistance = sonar.ping_cm();
    
    if(catDistance > minDistance_cm) {
      Serial.println("Cat staying confirmed");
      return true;
    }
  }
    
   return false;
}
