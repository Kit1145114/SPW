#pragma once
#include "Common-cpp/inc/defines.h"

class PadData {
public:
	float m_lStickX = 0.0f;		//!<���X�e�B�b�N��X���̓��͗ʁB
	float m_lStickY = 0.0f;		//!<���X�e�B�b�N��Y���̓��͗ʁB
	float m_rStickX = 0.0f;		//!<�E�X�e�B�b�N��X���̓��͗ʁB
	float m_rStickY = 0.0f;		//!<�E�X�e�B�b�N��Y���̓��͗ʁB

	void setPress(int button, bool press);
	bool getPress(int button) const;
	void setTrigger(int button, bool press) {
		setPress(button + enButtonNum, press);
	}
	bool getTrigger(int button) const{
		return getPress(button + enButtonNum);
	}
private:
	int32_t buttons = 0;
};

class PadRingBuffer {
public:
	PadRingBuffer() :buffer{} {};
	~PadRingBuffer() {};

	void clearBuffer();

	bool hasNext() const;

	void nextData();

	void pushFromCPad(const CPad& pad);

	void pushFromArray(nByte * array);

	const PadData* getPad() const{
		return start;
	}
	unsigned int size = 0;
private:
	static constexpr int NUM = 30;
	PadData buffer[NUM] = {};
	const PadData* const arrayEnd = buffer+ NUM;
	PadData* start = buffer;
	PadData* end = buffer+1;
};

