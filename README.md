# GBGame
This project is the source code for our handheld gaming device called GBGame. It features a few mini-games interacting with different sensors. It also connects to wifi and lets you put up challenges on the web that other players can go and respond to and compete for the best score. 
There are also online high-score boards that save the top 5 scores for each game. 

## About the code base
The program is built on the Arduino/Mbed OS framework and uses Mbed RTOS features.
The program is based around our system of 'states' which could be described as small applications
or games/menus running on the device. 

All states are handled by the stateHandler. The stateHandler is responsible for stopping all threads running in the previously running state and launching the new state initializing its threads.  

### Getting Started
The project is based on an Arduino Nano RP2040 connect board, and you can find the schematics of the hardware build here: https://www.figma.com/board/exiw9wgnHgAbENhK7Swpkf/Kunskapsbank?node-id=0-1&t=veI6WtQ6J8sapXFR-0

<img width="2335" alt="Kunskapsbank" src="https://github.com/JohnForslundGebka/gbgame/assets/149797907/3af19813-14b6-4f68-b277-3c46e931bb5b">


#### Prerequisites
All necessary libraries are included in the repo, and you should use platformIO to build the program.

