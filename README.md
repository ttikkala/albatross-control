# glider-control
This is a project to create an autonomous model rocket glider. The repository currently contains the first version of a custom PID library which will be used to control the flight surfaces of the glider.

TODO: Add visuals

## What are rocket gliders?

Rocket gliders are vehicles which launch as rockets and come down as gliders, as demonstrated for example in [this picture from ...](). 

The goal for this project is to build a **model scale rocket glider** that after launching can **autonomously recover** by gliding to the desired location. (Back to the launch pad would be very cool but due to safety concerns will probably not be the desired direction.)

## Contents of this repository

This repo currently houses the beginnings of a PID library built from scratch in C++. It will be used on an Arduino Nano to control the flight surfaces (elevators, ailerons, possibly rudder) of the glider.

## PID control loop

The PID library consists of three parts: a PID loop itself, a finite impulse response (FIR) filter, and a ring buffer data structure. 

The PID loop calculates the control response of a flight surface to the state of the system (TODO: add more complete explanation). The derivative term of the loop may need signal filtering to reduce noise, as the it is prone to noise. This is why the FIR filter was added. The FIR filter utilises a ring buffer data structure.

## Glider design

TODO: Design description

## Plan for future work

The next steps in the project are:
- Integrate Adruino Nano, IMU, servo and code to test control of a single control surface based on IMU readings
- Build glider and test passive stability
- Incorporate electronics into glider
- Visualise glider position based on IMU readings to verify readings are correct
- Test flight: elevator control --> gain tuning
- Test flight: elevator & aileron control --> gain tuning
