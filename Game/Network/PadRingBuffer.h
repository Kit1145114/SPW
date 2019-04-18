#pragma once
#include "NetPad.h"

class PadRingBuffer {
public:
	PadRingBuffer() :buffer{} {};
	~PadRingBuffer() {};

	void moveStart();
	
	void moveEnd();

	const NetPad::PadData* getStart() const{
		return start;
	}

	NetPad::PadData* getEnd() {
		return end;
	}

	bool isFull() {
		return !empty && start == end;
	}

	bool isEmpty() {
		return empty;
	}

private:
	NetPad::PadData buffer[NUM] = {};
	const NetPad::PadData* const arrayEnd = buffer+ NUM;
	NetPad::PadData* start = buffer;
	NetPad::PadData* end = buffer;
	bool empty = true;
};


template<int NUM>
inline void PadRingBuffer<NUM>::moveStart() {
	start++;
	if (start == arrayEnd) {
		start = buffer;
	}
	if (start == end) {
		empty = true;
	}
}

template<int NUM>
inline void PadRingBuffer<NUM>::moveEnd() {
	if (start == end && !empty) {
		return;
	}
	empty = false;
	end++;
	if (end == arrayEnd) {
		end = buffer;
	}
}

