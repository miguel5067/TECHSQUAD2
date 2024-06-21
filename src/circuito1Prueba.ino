#include <Servo.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

// Pines del módulo L298N
int ENA = 7;  
int IN1 = 6;
int IN2 = 5;  

Servo servo;  // para controlar el servomotor
int velocidad = 140;  // Velocidad fija para el motor
int velocidadRetroceso = 220;  // Velocidad máxima para retroceder

// Pines del sensor ultrasónico delantero
int TRIG1 = 8;
int ECHO1 = 9;

// Pines del sensor ultrasónico izquierdo
int TRIG2 = 3;
int ECHO2 = 4;

// pin del servo delantero
int servoPin = 24;

// COMANDOS DE DIRECCION 

void moveForward() { // Avanzar hacia adelante
  servo.write(90);  // Vuelve el servomotor a la posición inicial
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, velocidad);  // Controla la velocidad del motor con el valor fijo establecido
}

void turnRight() { // Giro hacia la derecha 
  servo.write(127); // (Regular el valor de giro)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);  
  analogWrite(ENA, velocidad);  // Controla la velocidad del motor con el valor fijo establecido
}

void turnLeft() { // Giro hacia la izquierda
  servo.write(35); // (Regular el valor de giro)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW); 
  analogWrite(ENA, velocidad);  // Controla la velocidad del motor con el valor fijo establecido
}

void moveBack() { // Retroceder
  servo.write(127); // Vuelve el servomotor a la posición inicial
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, velocidadRetroceso);  // Aumenta la velocidad del motor para retroceder
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);  // Detiene el motor
}

float getDistance(int TRIG, int ECHO) {
  pinMode(TRIG, OUTPUT);
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  pinMode(ECHO, INPUT);
  return pulseIn(ECHO, HIGH, 30000) / 59.0;
}

// INICIALIZACION DE LOS PINES 

void setup() {
  Serial.begin(9600);  // Inicia la comunicación serie
  servo.attach(24); // Conecta el servomotor al pin 24

  // Configura los pines del módulo L298N como salidas
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Configura los pines del sensor ultrasónico delantero
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);

  // Configura los pines del sensor ultrasónico izquierdo
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);

  // Inicia el movimiento hacia adelante
  moveForward();
}

void loop() {
  float distanciaDelantera = getDistance(TRIG1, ECHO1);
  float distanciaIzquierda = getDistance(TRIG2, ECHO2);

  Serial.print("Distancia Delantera: ");
  Serial.println(distanciaDelantera);
  Serial.print("Distancia Izquierda: ");
  Serial.println(distanciaIzquierda);

  if (distanciaDelantera <= 15) {  // Si el sensor delantero detecta un obstáculo a 15 cm o menos
    stop();
    delay(2000); // Espera 2 segundos
    moveBack();
    delay(1750); // Retrocede por 4 segundos
    stop(); // Detiene después de retroceder
  } else if (distanciaDelantera <= 35 && distanciaIzquierda <= 35) {  // Si ambos sensores detectan un obstáculo a 35 cm o menos
    turnRight();
    delay(1000); // Espera 1 segundo para girar
  } else if (distanciaDelantera <= 35) {  // Si solo el sensor delantero detecta un obstáculo a 35 cm o menos
    turnLeft();
    delay(1000);  // Da un pequeño retraso para realizar el giro
    distanciaDelantera = getDistance(TRIG1, ECHO1);  // Vuelve a medir la distancia después del giro
    if (distanciaDelantera <= 15) {  // Si después del giro detecta un obstáculo a 15 cm o menos
      stop();
      delay(2000); // Espera 2 segundos
      moveBack();
      delay(1750); // Retrocede por 4 segundos
      stop(); // Detiene después de retroceder
    }
  } else {  // Si no hay obstáculo
    moveForward();
  }
}
