Engineering materials
====

This repository contains engineering materials of a self-driven vehicle's model participating in the WRO Future Engineers competition in the season 2023.
En este repositorio se recopila la informacion desarrollada durante la participacion de nuestro equipo en la WRO 2023. 

## Content

* `t-photos` contains 2 photos of the team (an official one and one funny photo with all team members) Contiene dos fotos del equipo de estudiantes, que somos: Miguel, Samuel y Miguelangel.
* `v-photos` contains 6 photos of the vehicle (from every side, from top and bottom) Esta seccion contiene fotos del prototipo en diferentes vistas.
* `video` contains the video.md file with the link to a video where driving demonstration exists. En esta seccion presentamos un video de los dias de prueba y funcionamiento del prototipo. 
* `schemes` contains one or several schematic diagrams in form of JPEG, PNG or PDF of the electromechanical components illustrating all the elements (electronic components and motors) used in the vehicle and how they connect to each other. En esta seccion presentamos los esquemas electricos y mecanicos de armado y funcionamiento del prototipo. En la parte mecanica, el prototipo cuenta con un servomotor para la dirección, que es controlado por la señal de los sensores ultrasonicos. Para el avance contamos con otro motor conectado mediante engranajes y un eje, a las dos ruedas traseras. En el esquema electrico presentamos las conecciones de la placa arduino uno, la placa de control del motor y cada uno de los sensores. La alimentacion se da a traves de una bateria de 9 voltios 650 mAh recargable. Adicional esta el archivo de coneccion de la camara que nos sirve para la visualizacion de los obstaculos y la deteccion de color es a traves de los sensores de color.
* `src` contains code of control software for all components which were programmed to participate in the competition. Aqui puede encontrar la codificacion principal de funcionamiento y tambien la codificacion de la camara ov7670 sin fifo.
  
## Introduction

Hello! We are Teachsquad2, composed of Miguel Sánchez, Oliver Alfonso, Carlos Yauge.  We represent the category of Future Engineers. This team is an oli bot 
With a board based on Arduino Mega and a controller, Osooyo incorporates 2 servomotors, 2 ultrasonic motors, 1 pyxsi camera. We design the robot to avoid and overcome obstacles on the track. We use the ultrasonic sensor and a camera for the robot to detect distance and colors, allowing turns (red = right, green = left).
