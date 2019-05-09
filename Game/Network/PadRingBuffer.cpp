#include "stdafx.h"
#include "PadRingBuffer.h"

void PadRingBuffer::clearBuffer() {
	if (end == buffer) {
		start = const_cast<PadData*>(arrayEnd) - 1;
	} else {
		start = end - 1;
	}
	size = 0;
}

bool PadRingBuffer::hasNext() const{
	const PadData* local_start = start;
	local_start++;
	if (local_start == arrayEnd) {
		local_start = buffer;
	}

	//次のデータがある場合だけtrue
	if (local_start != end) {
		return true;
	} else {
		return false;
	}
}

void PadRingBuffer::nextData() {
	PadData* local_start = start;
	local_start++;
	if (local_start == arrayEnd) {
		local_start = buffer;
	}
	//次のデータがある場合だけ更新する
	if (local_start != end) {
		start = local_start; size--;
	} else {
		//次のデータがないときは今のデータをトリガだけ消して使いまわす
		for (int i = 0; i < enButtonNum; i++) {
			start->setTrigger(i, false);
		}
	}
}

void PadRingBuffer::pushFromCPad(const CPad & pad) {
	if (start == end) {
		return;
	}

	const PadData* before;
	if (end == buffer) {
		before = arrayEnd - 1;
	} else {
		before = end - 1;
	}

	for (int i = 0; i < enButtonNum; i++) {
		bool press = pad.IsPress((EnButton)i);
		end->setTrigger(i, !before->getPress(i) && press);
		end->setPress(i, press);
	}
	end->m_lStickX = pad.GetLStickXF();
	end->m_lStickY = pad.GetLStickYF();
	end->m_rStickX = pad.GetRStickXF();
	end->m_rStickY = pad.GetRStickYF();

	end++; size++;

	if (end == arrayEnd) {
		end = buffer;
	}
}

void PadRingBuffer::pushFromArray(nByte * array) {
	if (start == end) {
		return;
	}
	const PadData* before;
	if (end == buffer) {
		before = arrayEnd - 1;
	} else {
		before = end - 1;
	}

	for (int b = 0; b < enButtonNum; b++) {
		bool press = array[b / 8] & (1 << b % 8);
		end->setTrigger(b, !before->getPress(b) && press);
		end->setPress(b, press);
	}
	float* fp = (float*)(array + 2);
	end->m_lStickX = *fp;
	fp++;
	end->m_lStickY = *fp;
	fp++;
	end->m_rStickX = *fp;
	fp++;
	end->m_rStickY = *fp;
	fp++;

	end++; size++;
	if (end == arrayEnd) {
		end = buffer;
	}
}

void PadData::setPress(int button, bool press) {
	if (press) {
		buttons |= ( 1 << button);
	} else {
		buttons &= ~(1 << button);
	}
}

bool PadData::getPress(int button) const{
	return buttons & (1 << button);
}
