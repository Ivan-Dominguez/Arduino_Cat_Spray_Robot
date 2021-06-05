#include <NewPing.h>

int waterPumpOnPin = 13;

//intiatiate sonar object
int triggerPin = 10;
int echoPin = 11;
int maxDistance_cm = 500;
int initialDoordistance = 0;
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
  int ultrasoundVccPin = 12;
  pinMode(ultrasoundVccPin,OUTPUT);
  digitalWrite(ultrasoundVccPin, HIGH);
  delay(300);
  initialDoordistance = sonar.ping_cm();
 
  //setup waterPump power pin
  pinMode(waterPumpOnPin, OUTPUT);
  digitalWrite(waterPumpOnPin, LOW);

  Serial.begin(9600);
  delay(1000);
}

void loop() { 

   //digitalWrite(waterPumpOnPin, HIGH);
//int doorDistance = sonar.ping_cm();
//Serial.println("doorDistance");
 
  if(isDoorClosed() && isCatPresent()){
    Serial.println("Turning spray ON");
    digitalWrite(waterPumpOnPin, HIGH);
    delay(300);
    Serial.println("Turning spray Off");
    digitalWrite(waterPumpOnPin, LOW);
  }
  
  delay(250);
}

/* isDoorClosed(): Checks bedroom's door is open or closed */
bool isDoorClosed(){
  
  int doorDistance = sonar.ping_cm();
  
  if(doorDistance >  initialDoordistance + 5) {
    Serial.println("Door is open");
    Serial.println(initialDoordistance);
    Serial.println(doorDistance);
     return false;
  }else{
    Serial.println("Door is closed");
    return true;
  } 
}

/* isCatPresent(): Checks if cat is standing in front of machine or just passing by */
bool isCatPresent(){
  int delayInSeconds = 9;

  int movement = digitalRead(PIROutputPin);
     
    if(movement == HIGH) {
      Serial.println("GINGOL detected!"); //Gingol is our cat's name
    
      for(int i = delayInSeconds; i > 0; i--){
        Serial.print("Checking again in: ");
        Serial.print(i);
        Serial.println(" seconds");
        delay(1000);
      }

      //checking if cat still standing by the door after delay
      movement = digitalRead(PIROutputPin);
      Serial.println(movement);
      
      Serial.println("checking cat again");
      if(movement == HIGH) {
        
        Serial.println("Cat staying confirmed");
        return true;
      }
        
  }else{
      Serial.println("No movement");
      return false;
  }
  
}
