# Robotarm

Robotic arm controlled by a game controller.

The current code in main.ino supports a 3+1 DOF robot with a linear gripper. Stepper driver code communicates with DRV8825 stepper motor controllers. Servos are using the Arduino Servo library.

## Main components:
- Arduino Driver code (this repository)
    - MotorDriver
    - StepperDriver
    - ServoDriver
- Control program that interfaces with Serial USB
    - https://github.com/brht0/arduinojoystick
