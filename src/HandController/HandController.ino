#include <CommandConfig.h>
#include <Command.h>
#include <CommandController.h>
#include <Servo.h>

#define SERVO 22
#define MOTOR_OFF 85

CommandController commandController;
Servo motor;

char commandChars[MAX_CHARACTERS_IN_BUFFER];

void setup() { 
    Serial.begin (115200);
    motor.attach(SERVO);
    motor.write(MOTOR_OFF);
    delay(2000);
}

void loop() {
    const unsigned long currentTime = millis();
    
    // Check for available bytes
    const int availableBytes = Serial.available();
    if (availableBytes) {
        printTime(currentTime);
        Serial.print("Reading ");
        Serial.print(availableBytes);
        Serial.print(" bytes...");

        // Read bytes from serial
        for (int i = 0; i < min(availableBytes, MAX_CHARACTERS_IN_BUFFER); ++i) {
            commandChars[i] = Serial.read();
        }

        Serial.println(" DONE");

        printTime(currentTime);
        Serial.print("Decoding chars...");
        commandController.addChars(currentTime, commandChars, availableBytes);
        Serial.println(" DONE");
    }

    const Command* next = commandController.next(currentTime);

    // Execute all ADMIN commands in buffer
    while(next != nullptr && next->type() == CommandTypeEnum::ADMIN) {
        printTime(currentTime);
        Serial.print("Executing ADMIN command -- ");
        printCommand(next);
        Serial.println();
        executeAdminCommand(next->action(), next->data());
        next = commandController.next(currentTime);
    }

    // Execute movement command (just one)
    if (next != nullptr) {
        printTime(currentTime);
        Serial.print("Executing MOVE command -- ");
        printCommand(next);
        Serial.println();
        executeMovementCommand(next->type(), next->action(), next->data());
    }
    
    delay(50);
}

// Maps desired action to provided command
void executeAdminCommand(const CommandActionEnum action, const int data) {
    switch(action) {
        case CommandActionEnum::SET_MOVEMENT_COMMAND_TIMER:
            commandController.setMovementCommandDuration(data);
            break;
        case CommandActionEnum::SET_CHAR_BUFFER_CLEAR_TIMER:
            commandController.setCharBufferClearTimeout(data);
            break;
        default:
            return;
    }
}

void executeMovementCommand(const CommandTypeEnum type, const CommandActionEnum action, const int data) {
    switch(type) {
        case CommandTypeEnum::FINGER_ALL:
            switch(action) {
                case CommandActionEnum::CONTRACT:
                    moveFinger(min(-1, -data));
                    break;
                case CommandActionEnum::EXTEND:
                    moveFinger(max(1, data));
                    break;
                case CommandActionEnum::STOP:
                default:
                    moveFinger(0);
            }
            break;
    }
}

void printTime(const unsigned long currentTime) {
    Serial.print("[");
    Serial.print(currentTime);
    Serial.print("]:\t\t");
}

// Returns string representation of a command object
void printCommand(const Command* command) {
    switch (command->action()) {
        case CommandActionEnum::SET_MOVEMENT_COMMAND_TIMER:
            Serial.print("SET_COMMAND_TIMER ");
            break;
        case CommandActionEnum::SET_CHAR_BUFFER_CLEAR_TIMER:
            Serial.print("SET_CHAR_TIMER ");
            break;
        case CommandActionEnum::CONTRACT:
            Serial.print("CONTRACT ");
            break;
        case CommandActionEnum::EXTEND:
            Serial.print("EXTEND ");
            break;
        case CommandActionEnum::STOP:
            Serial.print("STOP ");
            break;
        default:
            Serial.print("UNDEFINED ");
    }
    Serial.print(command->data());
}

// Rotate motor at specified speed (positive = clockwise)
void moveFinger(float speed) {
    motor.write(MOTOR_OFF + speed);
}
