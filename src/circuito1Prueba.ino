#include <Servo.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

// Pines del módulo L298N
int ENA = 5;  
int IN1 = 4;
int IN2 = 6;  

Servo servo;  // para controlar el servomotor
int velocidad = 200;  // Velocidad fija para el motor (regular!)

// Pines del sensor ultrasónico delantero
int TRIG1 = 7;
int ECHO1 = 8;

// Pines del sensor ultrasónico izquierdo
int TRIG2 = 10;
int ECHO2 = 11;

// COMANDOS DE DIRECCION 

void moveForward() { // Avanzar hacia adelante
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  servo.write(91);  // Vuelve el servomotor a la posición inicial
}

void Stop() { // Detenerse (si quieren lo pueden quitar)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  servo.write(91);  // Vuelve el servomotor a la posición inicial
}

void turnRight() { // Giro hacia la derecha 
  servo.write(50); // (Regular el valor de giro)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);  
}

void turnLeft() { // Giro hacia la izquierda
  servo.write(140); // (regular el valor de giro)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);   
}

// INICIALIZACION DE LOS PINES 

void setup() {
  Serial.begin(9600);  // Inicia la comunicación serie
  servo.attach(9); // Conecta el servomotor al pin 9

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

  if (distanciaDelantera <= 15 && distanciaIzquierda <= 15) {  // Si ambos sensores detectan un obstáculo a 15 cm o menos
  //Pueden variar esto 
    Stop();
    delay(100);
    turnRight();
    delay(580);
    moveForward();
    delay(450);
  } else if (distanciaDelantera <= 15) {  // Si solo el sensor delantero detecta un obstáculo a 15 cm o menos
  //Pueden variar esto 
    Stop();
    delay(100);
    turnRight();
    delay(580);
    moveForward();
    delay(450);
  } else {  // Si no hay obstáculo
    moveForward();
  }

  analogWrite(ENA, velocidad);  // Controla la velocidad del motor con el valor fijo establecido

}
