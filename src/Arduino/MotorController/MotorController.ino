#include <Servo.h>
#include 

#define SERVO 22
#define MOTOR_OFF 85

Servo motor;
String command;

void setup() { 
    Serial.begin (9600);
    motor.attach(SERVO);
    motor.write(MOTOR_OFF);
}

void loop() {
    while (Serial.available()) {
        command = Serial.readString();
        Serial.print("Received command: ");
        Serial.println(command);
        
        switch(command) {
            case "#STOP":
                moveFinger(0);
                break;
            case "#CONT":
                moveFinger(-2);
                break;
            case "#EXTD":
                moveFinger(2);
                break;
        }
    }
}

// Rotate motor at specified speed (positive = clockwise)
void moveFinger(float speed) {
    // if not reached maximums
    motor.write(MOTOR_OFF + (direction ? -speed : speed));
}
