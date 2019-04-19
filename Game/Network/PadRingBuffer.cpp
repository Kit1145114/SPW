#include "stdafx.h"
#include "PadRingBuffer.h"

bool PadRingBuffer::hasNext() {
	PadData* local_start = start;
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
		start = local_start;
	} else {
		//次のデータがないときは今のデータをトリガだけ消して使いまわす
		for (int i = 0; i < enButtonNum; i++) {
			start->m_trigger[enButtonNum] = false;
		}
	}
}

void PadRingBuffer::pushFromCPad(const CPad & pad/*, nByte flameNum*/) {
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
		end->m_trigger[i] = !before->m_press[i] && press;
		end->m_press[i] = press;
	}
	end->m_lStickX = pad.GetLStickXF();
	end->m_lStickY = pad.GetLStickYF();
	end->m_rStickX = pad.GetRStickXF();
	end->m_rStickY = pad.GetRStickYF();
	/*end->flameNum = flameNum;*/

	end++;

	if (end == arrayEnd) {
		end = buffer;
	}
}

void PadRingBuffer::pushFromArray(nByte * array/*, nByte flameNum*/) {
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
		end->m_trigger[b] = !before->m_press[b] && press;
		end->m_press[b] = press;
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

	/**(nByte*)fp = flameNum;*/

	end++;
	if (end == arrayEnd) {
		end = buffer;
	}
}