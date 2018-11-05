# Test Codes -

Kindly download the necessary libraries from [here](https://github.com/RoboManipal-9-0/Libraries/).

### 1. Bluetooth Base :
 Bluetooth Test Code for the Base.
#### Pre-requisites:
Download the Controller App from [here](https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller&hl=en_IN).
Ensure that the HC-05 Module is Mounted on the Base.
#### How to Use:

1. Connect to the Module HC-05-23102018 in the App after pairing it up with your Device  (PSWD:1234).
2. Set the PWM of the Base from the Bar Adjacent to the Setting Icon.
3. Use the Top Left Most Button (Next to the Connection Indicator Dot) to Rotate in Anti-Clockwise Direction.
4. Use the Next Button to Rotate in Clockwise Direction.
5. Use Directional Arrows for Moving in the Directions Indicated in the App.

### 2. JoystickApp_APK :

APK File for the App that has been prepared for using in the Competition.
For Test Code Refer [bluetoothapp](#7. bluetoothapp)

### 3. ~~Loading Mechanism~~ : (Mechanism Discared)

Test Code Prepared to test the Mechanism that was prepared as of 4th November.

### 4. ManualBot_PS2_Bluetooth :
#### Pre-requisites:
Same Requirements as PS2_base and Bluetooth_base.

#### How to Use:
Set the PS2Mode true or false depending upon the Testing -
- PS2Mode True implies -> it will work on PS2 Controller.
- PS2Mode False implies -> it will work on Bluetooth.

### 5. ~~PS2_base~~ : (Outdated)

#### Pre-requisites:
PS2 Shield and Controller with the Baud Rate Correctly Set on the Hardware.

#### How to Use:
1.Connect The Controller to the Receiver Module by Switching it on and Pressing the Start Button on the Controller after which the LED on the Controller an Receiver should stop blinking.<br>
2.Use Right Joystick to Move the Base in the Required Direction.

### 6. THM :
Code prepared for Testing the Pneumatic Piston used in the Throwing Mechanism.

#### Pre-requisites:
Two Pneumatic Solenoid Valves (24V) connected to the Piston Mounted under the Throwing Mechanism along with the respective wiring using relays to Trigger the Solenoids with an Arduino.

Note: The DIRECT_SOLENOID_PIN goes to the solenoid that is connected to the Piston using the Extend Flow Port. The SECONDARY_SOLENOID_PIN goes to the solenoid which connects the Source of Air to the Retract Flow Port.

#### How to Use:
1. Define the Respective Pins in the code to which the respective Solenoids are connected on the Relay Board.

### 7. bluetoothapp :
Code for testing of the Manual Bot Base with the prepared [Bluetooth App](#2. JoystickApp_APK )

#### Pre-requisites:
The App downloaded and installed from [here](https://minhaskamal.github.io/DownGit/#/home?url=https://github.com/RoboManipal-9-0/Competitions/tree/ABU-Robocon-2019/RoboCon2019/TestCodes/JoystickApp_APK/APK_file).
Ensure that the Bluetooth Module HC-05 is mounted on the Bot.
Include the getData Library from [here](#https://minhaskamal.github.io/DownGit/#/home?url=https://github.com/RoboManipal-9-0/Competitions/tree/ABU-Robocon-2019/RoboCon2019/TestCodes/getData).

#### How to Use:

1. Connect to the Module HC-05-23102018 in the App after pairing it up with your Device  (PSWD:1234).
2. Open the App, Select Show Paired Devices and Connect to HC-05-23102018.
3. Use the Joystick to Control the Bot.

### 8. getData :

This is the Library required to map the Values received from the App to Usable format.
Download the Library from [here](#https://minhaskamal.github.io/DownGit/#/home?url=https://github.com/RoboManipal-9-0/Competitions/tree/ABU-Robocon-2019/RoboCon2019/TestCodes/getData).
