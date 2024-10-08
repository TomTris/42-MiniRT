# 42 MiniRT
![Language](https://img.shields.io/static/v1?label=language&message=c&color=blue) ![Licence](https://img.shields.io/badge/license-MIT-green) ![Score](https://42-project-badge.glitch.me/users/rpinto-r/project/minirt) 

## 🪧 Overview
### Description
This project is an introduction to the beautiful world of Raytracing.
Once completed you will be able to render simple Computer-Generated-Images and you
will never be afraid of implementing mathematical formulas again.
Our first raytracer handle the followings:
* Ambient, diffuse and specular lightning (Phong effect)
* Multiple lights colors and intensity
* Reflection
* The followings primitive objects : Planes, Spheres, Cylinders, Cones
* Multi-threading (in Bonus for faster rendering)
* Texture map and bump map on objects

### Contributors
- **Obrittne** (oBritt)
- **Qdo** (TomTris)

### Goal
The goal of the program is to generate images using the Raytracing protocol. Those computer-generated images will each represent a scene, as seen from a specific angle and position, defined by simple geometric objects, and each with its own lighting system.

## Structure of this README.MD
- Preview
  - Bonus
  - Mandatory
  - Mandatory additional
- Getting started
- Usage


## 📷 Preview
### Bonus
![./minirt_bonus scenes/bonus/atom.rt](https://drive.google.com/uc?export=view&id=1Q2Y1CFVlxLS4pUqKBOcRAyxJvtyolX4V)
![./minirt_bonus scenes/bonus/bubbles.rt](https://drive.google.com/uc?export=view&id=1dJrZdKWVq6pYWc0kHlsOoV0BdErg-XUE)
![./minirt_bonus scenes/bonus/chess.rt](https://drive.google.com/uc?export=view&id=1YWDYpv8Cmd8zNHOiemdJ0Sv2etC1SGCu)
![./minirt_bonus scenes/bonus/colored_snowman.rt](https://drive.google.com/uc?export=view&id=1EtKlNb4ilAX1gAqCLGhMDbq23HXc56PH)
![./minirt_bonus scenes/bonus/colored_spheres.rt](https://drive.google.com/uc?export=view&id=1bOoyPRNxI0dU13gelHXoK7ELRJOR6iWR)
![./minirt_bonus scenes/bonus/stickman_with_hat.rt](https://drive.google.com/uc?export=view&id=1DUYyikOEL1_ka36UrkLIaIqPi5rWxXYd)

### Mandatory
![./minirt scenes/subject/camera.rt](https://drive.google.com/uc?export=view&id=1Tz_Zy7qMirxUuaF8kQi0weH_LV9Gh5Fz)
![./minirt scenes/subject/cylinder.rt](https://drive.google.com/uc?export=view&id=1rzwu_F_-AuTtT2XNQqRs_9ttXTpOwCbO)
![./minirt scenes/subject/plain.rt](https://drive.google.com/uc?export=view&id=1COW8bO7zENiiLcSPKgpNprqwEWLn0Enp)
![./minirt scenes/subject/shadow.rt](https://drive.google.com/uc?export=view&id=1V4hnK_pmf64-1h8P41L3-L0oxbyJgtSj)
![./minirt scenes/subject/sphere.rt](https://drive.google.com/uc?export=view&id=1Qqoh8e7fKaUP73VJl9lgvZJF0udzd2q3)

#### Mandatory additional
![./minirt scenes/mandatory/octagon.rt](https://drive.google.com/uc?export=view&id=1329Wg77J2HrDB0B6Q5mL7jmXgeRr8EhG)
![./minirt scenes/mandatory/scene.rt](https://drive.google.com/uc?export=view&id=1iZcWMprg9AdaBPlzkHx0B6WOpPa5VVPS)

```
More than that?
||||
||||
||||
||||
||||
||||
\||/
 \/
```
## 🚀 Getting Started

### Installation
1. Clone the project.
```
git clone https://github.com/TomTris/42-MiniRT
cd 42-minirt
```
then, you can ```make``` or ```make bonus``` to have minirt for mandatory part and minirt_bonus for bonus part.

## 🕹 Usage
1. Run the MiniRT with a [scenes](scenes/).
```
./minirt scenes/mandatory/snowman.rt
```
or
```
./minirt_bonus scenes/bonus/stickman.rt
```

minirt_bonus can call all scenes.

2. Press key `ESC` to quit 

## Task
en.subject.pdf file.

Score 125/125.
