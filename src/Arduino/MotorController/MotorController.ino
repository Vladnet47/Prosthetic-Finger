#include <Servo.h>
#include "CommandBuffer.h"

#define SERVO 22
#define MOTOR_OFF 85

// Command format: #CCCCDDDDDDD, where C is the command and D is integer data
const char commandId = '#';
const int commandLength = 4;

Servo motor;

CommandBuffer buffer(5, false);

void setup() { 
    Serial.begin (9600);
    motor.attach(SERVO);
    motor.write(MOTOR_OFF);
}

void loop() {
    String commandString = readCommandFromSerial();
    
    if (commandString != "") {
        Serial.print("Received Serial command: ");
        Serial.print(commandString);
        
        Command* command = parseCommand(commandString);

        if (command->type == UNDEFINED) {
            Serial.print("Unable to parse command: ");
            Serial.print(commandString);
        } else {
            Serial.print("Successfully inserted command: type=");
            Serial.print(command->type);
            Serial.print(" data=");
            Serial.println(command->data);
            insertCommandIntoBuffer(command);
        }

        delete command;
    }
}

String readCommandFromSerial() {
    if (Serial.available()) {
        return Serial.readString();
    }

    return "";
}

// Parses command from string of format:
// #CCCCDD, where C is the command (CONT, EXTD, etc) and D is the optional data (integer)
// Returns command object of type UNDEFINED if unable to parse command
Command* parseCommand(String &command) {
    Command* result = new Command{ UNDEFINED, 0 };
    
    // Verify that the string is in correct format
    int length = command.length();
    if (length <= commandLength || command.charAt(0) != commandId) {
        return result;
    }

    // Extract numerical data if available
    int dataIndex = commandLength + 1;
    if (length > dataIndex) {
        result->data = (int) command.substring(dataIndex).toInt();
    }

    // Parse command type from string
    String commandType = command.substring(1, dataIndex);
    if (commandType.equals("STOP")) {
        result->type = STOP;
    } 
    else if (commandType.equals("CONT")) {
        result->type = CONTRACT_HAND;
    }
    else if (commandType.equals("EXTD")) {
        result->type = EXTEND_HAND;
    }
    else if (commandType.equals("PRNT")) {
        result->type = LIST_BUFFER;
    }

    return result;
}

void insertCommandIntoBuffer(Command* command) {
    if (command->type == UNDEFINED) {
        return;
    }

    buffer.push(command->type, command->data);
}



// Rotate motor at specified speed (positive = clockwise)
void moveFinger(float speed) {
    // if not reached maximums
    motor.write(MOTOR_OFF + speed);
}
