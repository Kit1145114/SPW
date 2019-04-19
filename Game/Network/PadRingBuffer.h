#pragma once
#include "Common-cpp/inc/defines.h"

struct PadData {
	float m_lStickX = 0.0f;		//!<���X�e�B�b�N��X���̓��͗ʁB
	float m_lStickY = 0.0f;		//!<���X�e�B�b�N��Y���̓��͗ʁB
	float m_rStickX = 0.0f;		//!<�E�X�e�B�b�N��X���̓��͗ʁB
	float m_rStickY = 0.0f;		//!<�E�X�e�B�b�N��Y���̓��͗ʁB
	bool m_press[enButtonNum] = {};
	bool m_trigger[enButtonNum] = {};
	//nByte flameNum = 255;
};

class PadRingBuffer {
public:
	PadRingBuffer() :buffer{} {};
	~PadRingBuffer() {};

	bool hasNext();

	void nextData();

	void pushFromCPad(const CPad& pad/*, nByte flameNum*/);

	void pushFromArray(nByte * array/*, nByte flameNum*/);

	const PadData* getPad() const{
		return start;
	}

private:
	static constexpr int NUM = 60;
	PadData buffer[NUM] = {};
	const PadData* const arrayEnd = buffer+ NUM;
	PadData* start = buffer;
	PadData* end = buffer+1;
};

