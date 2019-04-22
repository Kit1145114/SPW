#include "stdafx.h"
#include "NetPad.h"
#include "PNetworkLogic.h"
#include <string.h>

void NetPad::SetFromCPad(const CPad & pad) {
	buff.pushFromCPad(pad);
}

void NetPad::SetFromArray(nByte * array) {
	buff.pushFromArray(array);
}

void NetPad::sendState(PhotonLib::PNetworkLogic & network) {
	nByte array[2+16] = {};
	for (int b = 0; b < enButtonNum; b++) {
		if (Pad(0).IsPress((EnButton)b)) {
			array[b / 8] |= (1 << b % 8);
		}
	}
	
	float* fp = (float*)(array + 2);
	*fp = Pad(0).GetLStickXF();
	fp++;
	*fp = Pad(0).GetLStickYF();
	fp++;
	*fp = Pad(0).GetRStickXF();
	fp++;
	*fp = Pad(0).GetRStickYF();

	network.raiseEvent(true, array, 2+16, 0, 0);
}
