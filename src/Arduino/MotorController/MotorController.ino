#include <Servo.h>
#include "CommandSelector.h"
#include "Command.h"

#define SERVO 22
#define MOTOR_OFF 85

const int BUFFER_SIZE = 10;
const char COMMAND_ID = '#';
const char REPLY_LOG_ID = '$';
const char REPLY_RESPONSE_ID = '#';
const int COMMAND_LENGTH = 4;

struct Timer {
    unsigned long startTime;
    int duration;

    Timer(const int duration) {
        this->set(duration);
    }

    bool isDone() const {
        return millis() - this->startTime >= this->duration;
    }

    bool set(const int duration) {
        this->duration = duration;
    }

    bool start() {
        this->startTime = millis();
    }
};

Servo motor;

// Command format: #CCCCDDDDDDD, where C is the command and D is integer data
SelectionOptions options(BUFFER_SIZE);
CommandSelector commandSelector(options);

Timer timerFingerMovement = Timer(2000);
const Command defaultCommand = Command(STOP);

void setup() { 
    Serial.begin (9600);
    motor.attach(SERVO);
    motor.write(MOTOR_OFF);
}

void loop() {
    String commandString = readCommandFromSerial();

    // Handle incoming command
    if (commandString != "") {
        Serial.print(REPLY_LOG_ID);
        Serial.print("Received Serial command: ");
        Serial.print(commandString);
        
        const Command* command = parseCommand(commandString);
        if (command == nullptr) {
            Serial.print(REPLY_LOG_ID);
            Serial.print("Unable to parse command: ");
            Serial.print(commandString);
        } else {
            Serial.print(REPLY_LOG_ID);
            Serial.print("Successfully parsed command: ");
            Serial.println(toString(command));

            // Administrative/information-seeking commands get executed immediately
            if (command->type() == LIST_BUFFER) {
                executeCommand(*command);
            }
            // Motion-related commands get buffered
            else {
                commandSelector.add(*command);
            }
        }
    }

    // Execute commands from buffer
    if (timerFingerMovement.isDone()) {
        const Command* command = commandSelector.next();
        if (command != nullptr) {
            executeCommand(*command);
            
            Serial.print(REPLY_LOG_ID);
            Serial.print("Executed command: ");
            Serial.println(toString(command));

            timerFingerMovement.start();
        } else {
            executeCommand(defaultCommand);
            timerFingerMovement.start();
        }
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
const Command* parseCommand(const String &command) {
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

// Returns command to execute, or nullptr if no command in buffer. Also returns
// nullptr if new command is the same as the previous one.
const Command* selectCommand() {
    if (timerFingerMovement.isDone()) {
        timerFingerMovement.start();
        
        // If no more commands in buffer, revert to default behaviour
        if (commandSelector.isEmpty()) {
            return new Command(defaultCommand);
        } 
        // Otherwise, select and return next command from buffer if it is different from current one
        else {
            return new Command(*commandSelector.next());
        }
    }

    return nullptr;
}

void executeCommand(const Command& command) {
    const int bufferSize = commandSelector.size();
    
    switch(command.type()) {
        case LIST_BUFFER:
            Serial.print(REPLY_RESPONSE_ID);
            for (int i = 0; i < BUFFER_SIZE; ++i) {
                Serial.print((i < bufferSize ? toString(commandSelector.get(i)) : "[]"));
            }
            Serial.println();
            break;
        case EXTEND_HAND:
            break;
        case CONTRACT_HAND:
            moveFinger(min(-1, -command.nData()));
            break;
        case STOP:
        default:
            moveFinger(0);
    }
}

String toString(const Command* command) {
    if (command == nullptr) {
        return "none";
    }
    
    return String("[type=" + String(command->type()) + " nData=" + String(command->nData()) + "]");
}


// Rotate motor at specified speed (positive = clockwise)
void moveFinger(float speed) {
    // if not reached maximums
    motor.write(MOTOR_OFF + speed);
}
