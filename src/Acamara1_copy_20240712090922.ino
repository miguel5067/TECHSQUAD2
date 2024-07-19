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
int velocidad = 130;  // Velocidad fija para el motor
int velocidadGiro = 170;

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
  myServo.write(125);
  analogWrite(ENA, velocidadGiro );
}

void turnLeft() { // Giro hacia la izquierda
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW); 
  myServo.write(45);
  analogWrite(ENA, velocidadGiro );
}

// INICIALIZACION DE LOS PINES 
void setup() {
  // Para la Pixy2
  pixy.init();

  Serial.begin(9600);  // Inicia la comunicación serie
  myServo.attach(8); // Conecta el servomotor al pin 24

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
  
  if (pixy.ccc.numBlocks) {
    for (i = 0; i < pixy.ccc.numBlocks; i++) {
      color = pixy.ccc.blocks[i].m_signature; 
      
      if (color == 1) { // Color rojo (firma 1)
        turnRight();
        break; // Tomar acción inmediatamente cuando se detecta el color
      } else if (color == 2) { // Color verde (firma 2)
        turnLeft();
        break; // Tomar acción inmediatamente cuando se detecta el color
      }
    }
  } else {
    moveForward();
  }
  
  analogWrite(ENA, velocidad);  // Controla la velocidad del motor con el valor fijo establecido
}
