#include <Servo.h>
#include "Command.h"
#include "Timer.h"
#include "CommandSelector.h"
#include "CommandDecoder.h"

#define SERVO 22
#define MOTOR_OFF 85

CommandDecoder commandDecoder;
CommandSelector commandSelector;
Servo motor;
Timer movementTimer = Timer(300);
Timer decoderTimer = Timer(10000);
const Command defaultCommand = Command(CommandType::FINGER_ALL, CommandAction::STOP);

void setup() { 
    Serial.begin (9600);
    motor.attach(SERVO);
    motor.write(MOTOR_OFF);

    movementTimer.start(millis());
}

void loop() {
    const unsigned long currentTime = millis();
    
    // Empty command decoder buffer if timed out
    if (decoderTimer.isElapsed(currentTime)) {
        Serial.print("Timeout: clearing buffer...");
        commandDecoder.clear();
        decoderTimer.stop();
        Serial.println("done");
    }
    
    // Check for available bytes
    const int availableBytes = Serial.available();
    if (availableBytes) {
        Serial.print("Reading ");
        Serial.print(availableBytes);
        Serial.print(" bytes...");

        // Read bytes from serial
        char* bytes = new char[availableBytes];
        for (int i = 0; i < availableBytes; ++i) {
            bytes[i] = Serial.read();
        }

        Serial.println("done");

        Serial.print("Adding to decoder...");
        commandDecoder.addChars(bytes, availableBytes);
        Serial.println("done");

        // Start time when chars read
        decoderTimer.start(currentTime);
    }

    // Put decoded commands into command selector
    while (commandDecoder.hasNext()) {
        const Command* command = commandDecoder.next();

        if (command == nullptr || command->type() == CommandType::UNDEFINED || command->action() == CommandAction::UNDEFINED) {
            Serial.print("Unable to parse command: ");
        }
        else {
            Serial.print("Successfully parsed command: ");
            commandSelector.add(*command);
        }

        // Stop timer when command found
        decoderTimer.stop();
        
        printCommand(*command);
        Serial.println();
        delete command;
    }

    // Check for administrative commands
    if (commandSelector.hasNext(CommandType::ADMIN)) {
        const Command* command = commandSelector.next(CommandType::ADMIN);
        if (command != nullptr) {
            executeCommand(*command);
            delete command;
        }
    }

    // Check for next hand movement control command once the previous one is done executing
    if (movementTimer.isElapsed(currentTime)) {
        // Check for commands
        if (commandSelector.hasNext(CommandType::FINGER_ALL)) {
            const Command* command = commandSelector.next(CommandType::FINGER_ALL);
            if (command != nullptr) {
                executeCommand(*command);
                delete command;
            }
        }
        else {
            executeCommand(defaultCommand);
        }

        // Restart command execution timer
        movementTimer.start(currentTime);
    }

    //delay(50);
}

// Maps desired action to provided command
void executeCommand(const Command& command) {
    switch(command.action()) {
        case CommandAction::LIST_BUFFER:
            break;
        case CommandAction::EXTEND:
            moveFinger(max(1, command.nData()));
            break;
        case CommandAction::CONTRACT:
            moveFinger(min(-1, -command.nData()));
            break;
        case CommandAction::STOP:
        default:
            moveFinger(0);
    }
}

// Returns string representation of a command object
void printCommand(const Command& command) {
    Serial.print("[type=");
    if (command.type() == CommandType::UNDEFINED) {
        Serial.print("undef");
    }
    else {
        Serial.print((int) command.type());
    }
    Serial.print(" action=");
    if (command.action() == CommandAction::UNDEFINED) {
        Serial.print("undef");
    }
    else {
        Serial.print((int) command.action());
    }
    Serial.print(" data=");
    Serial.print(command.nData());
    Serial.print(" blobLength=");
    Serial.print(command.bLength());

    const char* blob = command.bData();
    if (blob != nullptr) {
        Serial.print(" blob=");
        for (int i = 0; i < command.bLength(); ++i) {
            Serial.print(blob[i]);
        }
    }

    Serial.print("]");
}

// Rotate motor at specified speed (positive = clockwise)
void moveFinger(float speed) {
    // if not reached maximums
    motor.write(MOTOR_OFF + speed);
}
