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
  delay(300000); //5 minutes = 300000 ms
}

void loop() { 
  bool doorClosed = isDoorClosed();
  bool catPresent = isCatPresent();
  
  if(doorClosed && catPresent){
    Serial.println("Turning spray ON");
    digitalWrite(waterPumpOnPin, HIGH);
    delay(400);
    Serial.println("Turning spray Off");
    digitalWrite(waterPumpOnPin, LOW);
    systemPauseSeconds(5);
  }else if(!doorClosed){
    systemPauseSeconds(300); //5 minutes = 300 sec
  }
}

/* isDoorClosed(): Checks bedroom's door is open or closed */
bool isDoorClosed(){
  
  int doorDistance = sonar.ping_cm();
  Serial.println(doorDistance);
  
  if(doorDistance >  initialDoordistance + 5) {
    Serial.println("Door is open");
     return false;
  }else{
    Serial.println("Door is closed");
    return true;
  } 
}

/* isCatPresent(): Checks if cat is standing in front of machine or just passing by */
bool isCatPresent(){

  int movement = digitalRead(PIROutputPin);
     
  if(movement == HIGH) {
    Serial.println("GINGOL detected!"); //Gingol is our cat's name
    return true;
  }else{
    Serial.println("No movement detected");
    return false;
  } 
}

/* systemPauseSeconds(): When bedroom door is open, start delay so we have time to enter into the room again without being sprayed */
void systemPauseSeconds(int seconds){
  
  for(int i = seconds; i > 0; i--){
        Serial.print("Delay ends in: ");
        Serial.print(i);
        Serial.println(" seconds");
        delay(1000);
  }
}
