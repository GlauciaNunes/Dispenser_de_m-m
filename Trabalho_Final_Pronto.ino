#include <Servo.h>

const int trigPin = 8;
const int echoPin = 7;
const int servoPin = 3;

Servo servoMotor;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servoMotor.attach(servoPin);
  dispenserParado(); // Inicialmente, o dispenser está parado
}

void loop() {
  long distance = measureDistance();

  Serial.print("Distancia: ");
  Serial.println(distance);

  if (distance <= 10) {
    dispenserAcionado();
  } 
  else {
    dispenserParado();
  }
}

long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

void dispenserAcionado() {
  long distance = measureDistance();

  if (distance <= 10) {
    servoMotor.write(60);
    delay(500);
  } 
  else {
    servoMotor.write(0);
    delay(500);
  }
}

void dispenserParado() {
  long distance = measureDistance();

  if (distance > 10 && distance <= 15) {
    servoMotor.write(60);
    delay(500);
  } 
  else {
    servoMotor.write(0);
    delay(500);
  }
}