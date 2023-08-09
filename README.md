Engineering materials
====

This repository contains engineering materials of a self-driven vehicle's model participating in the WRO Future Engineers competition in the season 2022.

## Content

* `t-photos` contains 2 photos of the team (an official one and one funny photo with all team members)
* `v-photos` contains 6 photos of the vehicle (from every side, from top and bottom)
* `video` contains the video.md file with the link to a video where driving demonstration exists
* `schemes` contains one or several schematic diagrams in form of JPEG, PNG or PDF of the electromechanical components illustrating all the elements (electronic components and motors) used in the vehicle and how they connect to each other.
* `src` contains code of control software for all components which were programmed to participate in the competition
* `models` is for the files for models used by 3D printers, laser cutting machines and CNC machines to produce the vehicle elements. If there is nothing to add to this location, the directory can be removed.
* `other` is for other files which can be used to understand how to prepare the vehicle for the competition. It may include documentation how to connect to a SBC/SBM and upload files there, datasets, hardware specifications, communication protocols descriptions etc. If there is nothing to add to this location, the directory can be removed.

## Introduction

Hello! We are Teachsquad, composed of Miguel Sánchez, Samuel Sánchez, and myself, Miguelangel Moreno. We represent the Future Engineers category. Our robot is an Osoyoo Racer kit with dimensions of 25x5 cm. It's equipped with an Arduino Uno-based board and incorporates 2 servo motors, 1 IR sensor, 2 color sensors, 1 ultrasonic sensor, and a 9V battery. We designed the robot to avoid and surpass obstacles on the track. We used the ultrasonic sensor and color sensors for the robot to detect distance and colors, enabling turns (red = right, green = left).
