#include <Servo.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

// Pines del sensor ultrasónico
const int TRIG_PIN = 2;
const int ECHO_PIN = 3;

// Pines del motor DC (con módulo L298N)
const int ENA = 7;
const int IN1 = 6;
const int IN2 = 5;

// Pines del servo motor
const int SERVO_PIN = 8;

// velocidadedes 
int velocidad = 175;
int velocidadRetroceso = 210; 
int velocidadGiro = 170;

// Crear objeto Servo
Servo myServo;

void moveForward() { // Avanzar hacia adelante
  myServo.write(85);  // Vuelve el servomotor a la posición inicial
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, velocidad);  // Controla la velocidad del motor con el valor fijo establecido
}

void turnRight() { // Giro hacia la derecha 
  myServo.write(125); // (Regular el valor de giro)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);  
  analogWrite(ENA, velocidadGiro );  // Controla la velocidad del motor con el valor fijo establecido
}

void turnLeft() { // Giro hacia la izquierda
  myServo.write(45); // (Regular el valor de giro)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW); 
  analogWrite(ENA, velocidadGiro );  // Controla la velocidad del motor con el valor fijo establecido
}

void moveBack() { // Retroceder a la derecha 
  myServo.write(115); // Vuelve el servomotor a la posición inicial
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, velocidadRetroceso);  // Aumenta la velocidad del motor para retroceder
}

void stop() { //deneter el motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);  // Detiene el motor
}

void setup() {
  // Inicializar la comunicación serie
  Serial.begin(9600);

  // Configurar los pines del sensor ultrasónico
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Configurar los pines del motor DC
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Inicializar el servo motor
  myServo.attach(SERVO_PIN);

  // Poner el servo motor en la posición central (90 grados)
  myServo.write(90);
  moveForward(); // inicia el movimiento hacia adelante 
}

void loop() {
  // Enviar pulso de disparo
  digitalWrite(TRIG_PIN, LOW);
  //delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  //delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Medir el tiempo del eco
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calcular la distancia en centímetros
  float distance = duration * 0.034 / 2;

  // Imprimir la distancia en el monitor serial
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 35) { // si la distancia delantera es menor a 35cm 
    stop();
    delay(1000); // Espera 1 segundos
    moveBack();
    delay(1570); // Retrocede por 1.5 segundos
    stop(); // Detiene después de retroceder
    delay(500);// espera medio segundo
  } else if (distance <= 47) {  // Si solo el sensor delantero detecta un obstáculo a 45 cm o menos
    turnLeft();
  } else {  // Si no hay obstáculo
    moveForward();
  }
  // Esperar 250 ms antes de la siguiente medición
  delay(225);
}
