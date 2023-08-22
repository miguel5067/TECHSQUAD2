#include <Servo.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

void Lento (){
  analogWrite(8,100);

}

void Avanzar (){
  analogWrite(8,160);

}
Servo servo_10;
void Estatico (){
  servo_10.write(100);

}
Servo servo_9;
void Recto (){
  servo_9.write(80);

}
void Retroceder (){
  analogWrite(8,255);

}
void Giro_Derecha (){
  servo_9.write(150);

}
void Detener (){
  analogWrite(7,0);

}
void Giro_Izquierda (){
  servo_9.write(50);

}
float getDistance(int trig,int echo){
    pinMode(trig,OUTPUT);
    digitalWrite(trig,LOW);
    delayMicroseconds(2);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    pinMode(echo, INPUT);
    return pulseIn(echo,HIGH,30000)/58.0;
}

void _delay(float seconds) {
  long endTime = millis() + seconds * 1000;
  while(millis() < endTime) _loop();
}

void setup() {
  pinMode(8,OUTPUT);
  servo_10.attach(10);
  servo_9.attach(9);
  pinMode(7,OUTPUT);

  // Giro Horario
  Avanzar();
  Recto();
  Estatico();
  while(1) {
      if((getDistance(3,2) < 30)  &&  (!((getDistance(0,1) < 30)))){
          Giro_Izquierda();

      }else{
          if((getDistance(3,2) < 30)  &&  (getDistance(0,1) < 30)){
              Giro_Derecha();

          }else{
              Avanzar();
              Recto();
              Estatico();

          }

      }

      _loop();
  }

}

void _loop() {
}

void loop() {
  _loop();
}