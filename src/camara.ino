#include <Servo.h>
#include <Arduino.h>
#include <Wire.h>
#include <Pixy2.h>

// Para la Pixy2
Pixy2 pixy;
int color;

// Pines del módulo L298N
int ENA = 7;  
int IN1 = 6;
int IN2 = 5;  

Servo myServo;  // para controlar el servomotor
int velocidad = 140;  // Velocidad fija para el motor
int velocidadGiro = 200;

// Rango de detección para cada color
//limite de 0 a 319 es por coordenadas 
const int rangoRojoMin = 50;    // Valor mínimo de X para detección de rojo
const int rangoRojoMax = 200;  // Valor máximo de X para detección de rojo
const int rangoVerdeMin = 100; // Valor mínimo de X para detección de verde
const int rangoVerdeMax = 250; // Valor máximo de X para detección de verde

// COMANDOS DE DIRECCION 
void Stop() { // Detenerse
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  myServo.write(90);
}

void moveForward() { // Avanzar hacia adelante
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  myServo.write(90);
}

void turnRight() { // Giro hacia la derecha 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);  
  myServo.write(120);
  analogWrite(ENA, velocidadGiro);
}

void turnLeft() { // Giro hacia la izquierda
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW); 
  myServo.write(55);
  analogWrite(ENA, velocidadGiro);
}

// INICIALIZACION DE LOS PINES 
void setup() {
  // Para la Pixy2
  pixy.init();

  Serial.begin(9600);  // Inicia la comunicación serie
  myServo.attach(8); // Conecta el servomotor al pin 8

  // Configura los pines del módulo L298N como salidas
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Inicia el movimiento hacia adelante
  moveForward();
}

void loop() {
  int i; 
  pixy.ccc.getBlocks();
  
  bool rojoDetectado = false;
  bool verdeDetectado = false;

  if (pixy.ccc.numBlocks) {
    for (i = 0; i < pixy.ccc.numBlocks; i++) {
      color = pixy.ccc.blocks[i].m_signature; 
      
      int xPos = pixy.ccc.blocks[i].m_x; // Coordenada X del bloque detectado

      if (color == 1 && xPos >= rangoRojoMin && xPos <= rangoRojoMax) { // Color rojo (firma 1) en el rango especificado
        rojoDetectado = true;
        Serial.print("Rojo detectado en X: ");
        Serial.println(xPos);
      } else if (color == 2 && xPos >= rangoVerdeMin && xPos <= rangoVerdeMax) { // Color verde (firma 2) en el rango especificado
        verdeDetectado = true;
        Serial.print("Verde detectado en X: ");
        Serial.println(xPos);
      }
    }
  }

  if (rojoDetectado) {
    turnLeft();
  } else if (verdeDetectado) {
    turnRight();
  } else {
    moveForward();
  }
  
  analogWrite(ENA, velocidad);  // Controla la velocidad del motor con el valor fijo establecido
}

