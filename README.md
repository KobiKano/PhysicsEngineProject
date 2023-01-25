# PhysicsEngineProject
[![License](https://img.shields.io/badge/License-EPL_2.0-red.svg)](https://opensource.org/licenses/EPL-2.0)
<img alt="GitHub contributors" src="https://img.shields.io/github/contributors/KobiKano/PhysicsEngineProject?color=green">
<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/KobiKano/PhysicsEngineProject?color=blue">

## This Project was used to help familiarize myself with graphics programming in C++ and openGL
### Features:
- Physics world is seperated as own library so that it can be used without openGL
- Sphere objects are icospheres so that vertex distribution is even
- Full camera support to rotate and zoom into scene

## Demos
### There are three demos within this project
#### Demo 1 : Ball drop collisions
![Demo1](https://github.com/KobiKano/PhysicsEngineProject/blob/master/Demo1.gif)
#### Demo 2 : Ball rolling down slope
![Demo1](https://github.com/KobiKano/PhysicsEngineProject/blob/master/Demo2.gif)
#### Demo 3 : Rotational motion
![Demo1](https://github.com/KobiKano/PhysicsEngineProject/blob/master/Demo3.gif)

## Possible Future additions/revisions:
- There is a known problem with object collisions sometimes not working as intended, this is likely due to the simulation being real-time and objects passing completely through another during a timestep
- Add multithreading to completely seperate physics world from rendering world
- Add proper lighting to scene
- Add support for object rotation for both spheres and cubes
- Possibly refine both rendering system and physics engine to create personalized game-engine

#### Personal Contact: tthiagarajan@wisc.edu
