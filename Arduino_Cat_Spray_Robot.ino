#include <Servo.h>
#include <NewPing.h>

//servo motor values
int initialAngle = 0;
int finalAngle = 35;
Servo servo;

//intiatiate sonar object
int triggerPin = 10;
int echoPin = 11;
int maxDistance_cm = 200;
NewPing sonar(triggerPin, echoPin, maxDistance_cm);

//PIR output pin
int PIROutputPin = 6;

void setup() {
  
  //setup PIR
  int PIRVccPin = 7;
  pinMode(PIRVccPin, OUTPUT);
  digitalWrite(PIRVccPin, HIGH);
  pinMode(PIROutputPin, INPUT);
  
  //setup ultrasound
  int ultrasoundVccPin = 13;
  pinMode(ultrasoundVccPin,OUTPUT);
  digitalWrite(ultrasoundVccPin, HIGH);

  //setup servo
  int servoPin = 8;
  servo.attach(servoPin);
  servo.write(initialAngle);
  Serial.begin(9600);
  delay(500);
}

void loop() { 
 
  if(isDoorClosed() && isCatPresent()){
    turnSprayOn();
    delay(300);
    turnSprayOff();
  }
  
  delay(250);
}

/*turnSprayOn(): Activate servo motor sequence to turn on spray bottle */
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

/*turnSprayOff(): Activate servo motor sequence to turn off spray bottle */
void turnSprayOff(){
  Serial.println("Turning spray OFF");
  servo.write(finalAngle);
  delay(300);
  servo.write(initialAngle);
}

/* isDoorClosed(): Checks bedroom's door is open or closed */
bool isDoorClosed(){
  
  int closedDoorDistance_cm = 90;
  int doorDistance = sonar.ping_cm();
  Serial.println(doorDistance);
  
  if(doorDistance > closedDoorDistance_cm) {
    Serial.println("Door is open");
     return false;
  }else{
    Serial.println("Door is closed");
    return true;
  } 
}

/* isCatPresent(): Checks if cat is standing in front of machine or just passing by */
bool isCatPresent(){
  int delayInSeconds = 10;

  int movement = digitalRead(PIROutputPin);
     
    if(movement == HIGH) {
      Serial.println("GINGOL detected!"); //Ginglos is our cat's name
    
      for(int i = delayInSeconds; i > 0; i--){
        Serial.print("Checking again in: ");
        Serial.print(i);
        Serial.println(" seconds");
        delay(1000);
      }

      //checking if cat still standing by the door after delay
      movement = digitalRead(PIROutputPin);
      if(movement == HIGH) {
        Serial.println("Cat staying confirmed");
        return true;
      }
        
  }else{
      Serial.println("No movement");
      return false;
  }
  
}
