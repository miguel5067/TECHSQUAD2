#include <Servo.h>
#include <Wire.h>
#include <Arduino.h>
#include <Pixy2.h>
#include <SoftwareSerial.h>

// Ultrasonic Sensor
const int TRIG_PIN = 2; // Trigger pin
const int ECHO_PIN = 3; // Echo pin

// Motor Pins

const int ENA = 7;
const int IN1 = 6;
const int IN2 = 5;

// Servo Pins
const int SERVO_PIN = 8;

/*
  Valor para decidir si gira a la izquierda o derecha
  Izquierda = true, Derecha = false
  Esto solo va a cambiar durante la ejecución del código
  Dependiendo si el pilar #12 es rojo o verde,
  Si es rojo, cambiará a false, si es verde se mantendrá en true
  Debido a que indicara que el robot esta haciendo los giros como se tiene planeado "Izquierda"
*/
bool giro = true;

/* Contador de vueltas "Pilares"
 tecnicamente en la pista hay 6 pilares
 con lo cual cada vuelta son 6 pilares
*/
int contador = 0;

// Saber color de los pilares
// 1 = Rojo, 2 = Verde
int colorPilar = 0;

// Speed values

/// Variar en Base a que tan bien da el giro, para mejorar el tipo de cada vuelta
int velocidad = 165;          // Speed value
int velocidadRetroceso = 195; // Backward speed value
int velocidadGiro = 170;      // Turn speed value

// Servo Object

Servo myServo;

// Pixy2 Object
Pixy2 pixy;
int color;

// Rango de detección para cada color
// limite de 0 a 319 es por coordenadas
const int rangoRojoMin = 150;   // Valor mínimo de X para detección de rojo
const int rangoRojoMax = 200;  // Valor máximo de X para detección de rojo
const int rangoVerdeMin = 150; // Valor mínimo de X para detección de verde
const int rangoVerdeMax = 200; // Valor máximo de X para detección de verde

// Movement Functions
void moveForward()
{                    // Avanzar hacia adelante
  myServo.write(90); // Vuelve el servomotor a la posición inicial
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, velocidad); // Controla la velocidad del motor con el valor fijo establecido
}

void turnRight()
{                     // Giro hacia la derecha
  myServo.write(125); // (Regular el valor de giro)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, velocidadGiro); // Controla la velocidad del motor con el valor fijo establecido
}

void turnLeft()
{                    // Giro hacia la izquierda
  myServo.write(45); // (Regular el valor de giro)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, velocidadGiro); // Controla la velocidad del motor con el valor fijo establecido
}

// Usado como un funcion para indicar como sera el movimiento del Giro
/// Izquierda = true, Derecha = false
void Girar(bool giro)
{
  if (giro)
  {
    turnLeft();
  }
  else
  {
    turnRight();
  }
}

/*
Funcion para contener la logica de deteccion de colores

*/
int detectColor()
{
  int i;
  pixy.ccc.getBlocks();
  int colorDet = 0;
  bool rojoDetectado = false;
  bool verdeDetectado = false;

  if (pixy.ccc.numBlocks)
  {
    for (i = 0; i < pixy.ccc.numBlocks; i++)
    {
      color = pixy.ccc.blocks[i].m_signature;

      int xPos = pixy.ccc.blocks[i].m_x; // Coordenada X del bloque detectado

      if (color == 1 && xPos >= rangoRojoMin && xPos <= rangoRojoMax)
      { // Color rojo (firma 1) en el rango especificado
        rojoDetectado = true;
        Serial.print("Rojo detectado en X: ");
        Serial.println(xPos);
        colorDet = 1;
      }
      else if (color == 2 && xPos >= rangoVerdeMin && xPos <= rangoVerdeMax)
      { // Color verde (firma 2) en el rango especificado
        verdeDetectado = true;
        Serial.print("Verde detectado en X: ");
        Serial.println(xPos);
        colorDet = 2;
      }
    }
  }
  // Retornar el numero del color detectado
  // 0 = No se detecta ningun color
  // 1 = Rojo
  // 2 = Verde

  return colorDet;
}
void moveBack()
{                     // Retroceder a la derecha
  myServo.write(115); // Vuelve el servomotor a la posición inicial
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, velocidadRetroceso); // Aumenta la velocidad del motor para retroceder
}

void stop()
{ // deneter el motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0); // Detiene el motor
}

long getUltrasonicDistance()
{
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  //delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  //delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;
  // Imprimir la distancia en el monitor serial
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Retornar la distancia en centímetros
  return distance;
}

void setup()
{
  // Motor Pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  // Ultrasonic Sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  // Servo
  myServo.attach(SERVO_PIN);
  // Servo initial position
  myServo.write(90);

  // Serial Communication
  Serial.begin(9600);
  // Pixy2
  pixy.init();
}

void loop()
{
  long distance = getUltrasonicDistance();
  if (distance < 35)
  { // si la distancia delantera es menor a 35cm
    stop();
    delay(1000); // Espera 1 segundo
    colorPilar = detectColor();
    if (colorPilar == 1)
    {                // Si el color detectado es rojo
      contador += 1; // Aumenta el contador Pilares
      turnRight();
      delay(1000); // Espera 1 segundo
      stop();      // Detiene después de girar
      delay(500);  // Espera medio segundo
    }
    else if (colorPilar == 2)
    {                // Si el color detectado es verde
      contador += 1; // Aumenta el contador Pilares
      if (contador == 12)
      {
        giro = false; // Cambia el sentido de giro
        // TODO: HACER EL GIRO DE 180° PARA CAMBIAR DE SENTIDO
      }
      else
      {
        turnLeft();
        delay(1000); // Espera 1 segundo
        stop();      // Detiene después de girar
        delay(500);  // Espera medio segundo
      }
    }
    else
    { // Si no se detecta ningún color
      stop();
      delay(500); // Espera 1 segundo
      moveBack();
      delay(1570); // Retrocede por 1.5 segundos
      stop();      // Detiene después de retroceder
      delay(500);  // espera medio segundo

      /*
      Se Girara hasta que el sensor ultrasonico detecte una distancia mayor a "x" cm.
      La idea es posicionarlo para que siga avanzando hacia adelante
      evitando colisionar con la "Pared"
      */
      while (distance < 55) // Ajustar en caso de colisionar con un objeto por que la distancia sea muy amplia

      {
        Girar(giro);
      }
    }
  }
  else
  { // Si no hay obstáculo
    moveForward();
  }
  // Esperar 250 ms antes de la siguiente medición
  delay(100);
}
