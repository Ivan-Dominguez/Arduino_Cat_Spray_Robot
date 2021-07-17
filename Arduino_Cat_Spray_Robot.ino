#include <NewPing.h>

#define PIRVccPin 7
#define PIROutputPin 6
#define triggerPin 10
#define echoPin 11
#define ultrasoundVccPin 12
#define waterPumpOnPin 13
#define maxDistance_cm 7000

//intantiate sonar object
int initialDoordistance = 0;
NewPing sonar(triggerPin, echoPin, maxDistance_cm);

void setup() {
  
  //setup PIR
  pinMode(PIRVccPin, OUTPUT);
  digitalWrite(PIRVccPin, HIGH);
  pinMode(PIROutputPin, INPUT);
  
  //setup ultrasound
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

  delay(250);
}

/* isDoorClosed(): Checks bedroom's door is open or closed */
bool isDoorClosed(){
  
  int doorDistance = sonar.ping_cm();
  Serial.println(doorDistance);
  
  if(doorDistance >  initialDoordistance + 10) {
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
