#include <Servo.h>
#include "CommandSelector.h"
#include "Command.h"

#define SERVO 22
#define MOTOR_OFF 85

// Command format: #CCCCDDDDDDD, where C is the command and D is integer data
const int BUFFER_SIZE = 10;
const char COMMAND_ID = '#';
const int COMMAND_LENGTH = 4;

Servo motor;

SelectionOptions options(BUFFER_SIZE);
CommandSelector commandSelector(options);

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

        if (command == nullptr) {
            Serial.print("Unable to parse command: ");
            Serial.print(commandString);
        } else {
            Serial.print("Successfully inserted command: type=");
            Serial.print(command->type());
            Serial.print(" nData=");
            Serial.println(command->nData());
            
            commandSelector.add(command);
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
    // Verify that the string is in correct format
    int length = command.length();
    if (length <= COMMAND_LENGTH || command.charAt(0) != COMMAND_ID) {
        return nullptr;
    }

    int type = UNDEFINED;
    int numericData = 0;

    // Extract numerical data if available
    int dataIndex = COMMAND_LENGTH + 1;
    if (length > dataIndex) {
        numericData = (int) command.substring(dataIndex).toInt();
    }

    // Parse command type from string
    String commandType = command.substring(1, dataIndex);
    if (commandType.equals("STOP")) {
        type = STOP;
    } 
    else if (commandType.equals("CONT")) {
        type = CONTRACT_HAND;
    }
    else if (commandType.equals("EXTD")) {
        type = EXTEND_HAND;
    }
    else if (commandType.equals("PRNT")) {
        type = LIST_BUFFER;
    }

    return new Command(type, numericData);
}


// Rotate motor at specified speed (positive = clockwise)
void moveFinger(float speed) {
    // if not reached maximums
    motor.write(MOTOR_OFF + speed);
}
