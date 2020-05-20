#ifndef COMMANDBUFFER
#define COMMANDBUFFER

// Command sent to microcontroller
struct Command {
	int type;
	int data;
};

// Types of defined commands
enum CommandType {
    UNDEFINED,
    STOP,
    CONTRACT_HAND,
    EXTEND_HAND,
    LIST_BUFFER
};

// Buffer that keeps track of a specified number of incoming commands
class CommandBuffer {
public:
	CommandBuffer(int size, bool prioritizeNew = true);
	~CommandBuffer();

	Command* get(int index) const;
	Command* peek() const;
	Command* pop();
	void push(int type, int data = 0);
	void clear();
	int size() const;
	bool isEmpty() const;
	Command* list() const;

private:
	Command* commandList;
	int start;
	int end;
	int currentSize;
	int maxSize;
	bool prioritizeNew;

	int incrementIndex(int index, int amount = 1) const;
};

#endif
