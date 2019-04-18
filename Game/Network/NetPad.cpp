#include "stdafx.h"
#include "NetPad.h"
#include "PNetworkLogic.h"
#include <string.h>

void NetPad::SetFromCPad(const CPad & pad) {
	if (buff.isFull()) {
		return;
	}
	PadData* push = buff.getEnd();
	for (int i = 0; i < enButtonNum; i++) {
		bool press = pad.IsPress((EnButton)i);
		push->m_trigger[i] = !push->m_press[i] && press;
		push->m_press[i] = press;
		push->m_lStickX = pad.GetLStickXF();
		push->m_lStickY = pad.GetLStickYF();
		push->m_rStickX = pad.GetRStickXF();
		push->m_rStickY = pad.GetRStickYF();
	}
	buff.moveEnd();
	updated = true;
}

void NetPad::SetFromArray(nByte * array) {
	if (buff.isFull()) {
		return;
	}
	PadData* push = buff.getEnd();
	for (int b = 0; b < enButtonNum; b++) {
		bool press = array[b / 8] & (1 << b % 8);
		push->m_trigger[b] = !push->m_press[b] && press;
		push->m_press[b] = press;
	}
	nByte* ap = array + 2;
	std::memcpy(&push->m_lStickX, ap, 4);
	ap += 4;			  
	std::memcpy(&push->m_lStickY, ap, 4);
	ap += 4;			  
	std::memcpy(&push->m_rStickX, ap, 4);
	ap += 4;			  
	std::memcpy(&push->m_rStickY, ap, 4);
	buff.moveEnd();
	updated = true;
}

void NetPad::sendState(PhotonLib::PNetworkLogic & network) {
	nByte array[2+16] = {};
	for (int b = 0; b < enButtonNum; b++) {
		if (Pad(0).IsPress((EnButton)b)) {
			array[b / 8] |= (1 << b % 8);
		}
	}
	
	nByte* ap = array + 2;
	*(float*)ap = Pad(0).GetLStickXF();
	ap += 4;
	*(float*)ap = Pad(0).GetLStickYF();
	ap += 4;
	*(float*)ap = Pad(0).GetRStickXF();
	ap += 4;
	*(float*)ap = Pad(0).GetRStickYF();

	network.raiseEvent(true, array, 18, 0, 0);
}
