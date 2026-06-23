#include <Servo.h>
#include <SoftwareSerial.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define SERVO_PIN 11
#define GREEN_LED 3 
#define RED_LED 2    
#define BUZZER 4

SoftwareSerial espSerial(6, 5); 

Servo doorServo;
const int triggerDistance = 15; 
bool isDoorOpen = false;
bool manualOverride = false; 

void setup() {
  Serial.begin(9600);       
  espSerial.begin(9600);    
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  doorServo.attach(SERVO_PIN);
  
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  doorServo.write(90); 
  digitalWrite(RED_LED, HIGH);   
  digitalWrite(GREEN_LED, LOW);  
  digitalWrite(BUZZER, LOW);     
}

void loop() {
  if (espSerial.available()) {
    String command = espSerial.readStringUntil('\n');
    command.trim();
    
    if (command == "MANUAL_OPEN" && !isDoorOpen) {
      manualOverride = true; 
      openDoorRoutine();
    } 
    else if (command == "MANUAL_CLOSE" && isDoorOpen) {
      manualOverride = false; 
      closeDoorRoutine();
    }
  }

  if (!manualOverride) {
    digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    long duration = pulseIn(ECHO_PIN, HIGH, 30000); 
    int distance = duration * 0.034 / 2;
    
    if (distance > 0 && distance <= triggerDistance && !isDoorOpen) {
      openDoorRoutine();
      espSerial.println("OPEN"); 
    } 
    else if ((distance > triggerDistance || distance == 0) && isDoorOpen) {
      delay(3000); 
      closeDoorRoutine();
      espSerial.println("CLOSED"); 
    }
  }
  delay(100); 
}

void openDoorRoutine() {
  doorServo.write(0); 
  isDoorOpen = true;
  digitalWrite(RED_LED, LOW);    
  digitalWrite(GREEN_LED, HIGH); 
  digitalWrite(BUZZER, HIGH); 
  delay(500); 
  digitalWrite(BUZZER, LOW);
}

void closeDoorRoutine() {
  doorServo.write(90); 
  isDoorOpen = false;
  digitalWrite(GREEN_LED, LOW);  
  digitalWrite(RED_LED, HIGH);   
}
