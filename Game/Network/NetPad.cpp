#include "stdafx.h"
#include "NetPad.h"
#include "PNetworkLogic.h"
#include <string.h>

void NetPad::SetFromCPad(const CPad & pad) {
	for (int i = 0; i < enButtonNum; i++) {
		bool press = pad.IsPress((EnButton)i);
		m_trigger[i] = !m_press[i] && press;
		m_press[i] = press;
		m_lStickX = pad.GetLStickXF();
		m_lStickY = pad.GetLStickYF();
		m_rStickX = pad.GetRStickXF();
		m_rStickY = pad.GetRStickYF();
	}
	updated = true;
}

void NetPad::SetFromArray(nByte * array) {
	for (int bit = 0; bit < enButtonNum; bit++) {
		m_press[bit] = array[bit / 8] & (1 << bit % 8);
	}
	nByte* ap = array + 2;
	std::memcpy(&m_lStickX, ap, 4);
	ap += 4;			  
	std::memcpy(&m_lStickY, ap, 4);
	ap += 4;			  
	std::memcpy(&m_rStickX, ap, 4);
	ap += 4;			  
	std::memcpy(&m_rStickY, ap, 4);
	updated = true;
}

void NetPad::sendState(PhotonLib::PNetworkLogic & network) {
	nByte array[18];
	for (int bit = 0; bit < enButtonNum; bit++) {
		array[bit / 8] |= (1 << bit % 8);
	}
	
	nByte* ap = array + 2;
	std::memcpy(ap, &m_lStickX, 4);
	ap += 4;
	std::memcpy(ap, &m_lStickY, 4);
	ap += 4;
	std::memcpy(ap, &m_rStickX, 4);
	ap += 4;
	std::memcpy(ap, &m_rStickY, 4);

	network.raiseEvent(true, array, 18, 0, 0);
}
