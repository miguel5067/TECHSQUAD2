
int motorPin1 = 9;  // Pin de control del motor 1 (sentido de giro)
int motorPin2 = 10; // Pin de control del motor 2 (velocidad)

#include <Servo.h>
Servo servo;             // Objeto del servomotor
int pinServo = 8;        // Pin para el servomotor
int pinSensor1 = A0;     // Pin para el primer sensor analógico
int pinSensor2 = A4;     // Pin para el segundo sensor analógico

void setup() {
  pinMode(motorPin1, OUTPUT);//MOTOR 
  pinMode(motorPin2, OUTPUT);//MOTOR 

  servo.attach(pinServo);    // Adjuntar el pin del servomotor al objeto servo
  pinMode(pinSensor1, INPUT);  // Configurar el primer sensor como entrada
  pinMode(pinSensor2, INPUT);  // Configurar el segundo sensor como entrada
}

void loop() {
   digitalWrite(motorPin1, HIGH);//sentido de las llanatas
   analogWrite(motorPin2, 255);//velocidad maxima 255

  int sensorValue1 = analogRead(pinSensor1);  // Leer el valor del primer sensor
  int sensorValue2 = analogRead(pinSensor2);  // Leer el valor del segundo sensor

  if (sensorValue1 > 500 && sensorValue2 > 500) {   // Si ambos sensores detectan algo
    // Acción cuando ambos sensores detectan algo
    servo.write(90);  // Girar a una posición deseada
  } else if (sensorValue1 > 500) {   // Si solo el primer sensor detecta algo
    // Acción cuando solo el primer sensor detecta algo
    servo.write(120);  // Girar a otra posición deseada
  } else if (sensorValue2 > 500) {   // Si solo el segundo sensor detecta algo
    // Acción cuando solo el segundo sensor detecta algo
    servo.write(-20);  // Girar a otra posición deseada
  } else {
    // Acción cuando ninguno de los sensores detecta algo
    servo.write(90);  // Girar a una posición neutral
  }
}




  




