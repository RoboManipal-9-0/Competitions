# About
This readme describes the various aspects of the codes being used for RoboCon 2020.

## Code Details

Platforms used: Arduino
Discontinued platforms: Raspberry Pi

## File-wise Details

### Try Robot (TR)

#### botPS2Control
The main movement code that implements movement control with a PS2 controller and inertial measurement unit (IMU)-based PID control.

##### Macros defined:
- int no_wheels = 4; >> The number of wheels on the bot.
- int angles_degrees[] = {45, 135, 225, 315}; >> Specifies the angles (measured counterclockwise) at which the wheels are placed with respect to the horizontal axis (X-axis). Used for calculation of movement vectors.
- int PWM_pins[] = {9, 8, 7, 6}; >> The pin numbers at which the wheel motor PWM pins are connected.
- int DIR_pins[] = {52, 50, 48, 46}; >> The pin numbers at which the wheel motor direction pins are connected.
- bool reverseDIRs[] = {false, false, false, false}; >> A per-wheel direction reverse that allows for an easy fix in case the motor wires get reversed.
- \#define IMUSerial Serial1 >> The Serial port at which the IMU is connected.
- \#define PS2Serial Serial3 >> The Serial port at which the PS2 Shield is connected.
- \#define kick 10 >> The pin at which the relay to control the kicking mechanism actuation is connected.

#### placingMechanism
Controls a motor to place the received ball onto the Try Spot from the body of the TR.

##### Macros defined:
- bool DEBUGGERS_ON = true; >> Toggles additional Debug print statements that could help in diagnosing a problem.
- int pwmPin = 7; >> The pin at which the motor PWM input is connected on the Arduino.
- int dirPin = 5; >> The pin at which the motor direction input is connected on the Arduino.

#### wallAlignment
A library-less code that uses ultrasonic sensors to align the TR with the wall/fence of the arena.

##### Macros defined:
- \#define NO_OF_WHEELS 4 >> The number of wheels on the bot.
- \#define DEBUGGERS_ON false >> Toggles additional Debug print statements that could help in diagnosing a problem.
- int PWM[] = {3,4,6,5}; >> The pin numbers at which the wheel motor PWM pins are connected.
- int DIR[] = {8,9,11,10}; >> The pin numbers at which the wheel motor direction pins are connected.
- int trigPin[2] = {28,24}; >> The pin numbers at which the ultrasonic sensors' trigger pins are connected.
- int echoPin[2] = {30,26}; >> The pin numbers at which the ultrasonic sensors' echo pins are connected.

#### Discontinued codes
Codes that were being used at some point but are no longer maintained due to change of game plan / impracticality.

### Pass Robot (PR)

#### pickingAndThrowingTest
Code for combined testing of all of the mechanisms of the PR. Allows the bot to pick up the ball, place it onto the throwing mechanism and throw it.

##### Macros defined:
- \#define rhinoSerial Serial1 >> The Serial port at which the Rhino motor is connected.
- \#define servoPin 9 >> The pin number at which the servo motor which controls the gripping action is connected.
- \#define relayPin 10 >> The pin number at which the relay which controls the mechanism actuation is connected.
- \#define holdingDelay 200 >> The amount of time to wait in milliseconds (ms) after issuing a command to the holding/gripping servo.
- \#define rhinoDelay 4000 >> The amount of time to wait in milliseconds (ms) after issuing a command to the rhino motor.
- \#define mechDelay 2000 >> The amount of time to wait in milliseconds (ms) after issuing a command to the relay which is controlling the mechanism.