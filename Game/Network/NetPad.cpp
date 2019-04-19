#include "stdafx.h"
#include "NetPad.h"
#include "PNetworkLogic.h"
#include <string.h>

void NetPad::SetFromCPad(const CPad & pad/*, nByte flame*/) {
	buff.pushFromCPad(pad/*, flame*/);
	updated = true;
}

void NetPad::SetFromArray(nByte * array/*, nByte flame*/) {
	buff.pushFromArray(array/*, flame*/);
	updated = true;
}

void NetPad::sendState(PhotonLib::PNetworkLogic & network/*, nByte flame*/) {
	nByte array[2+16/*+1*/] = {};
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

	/**(nByte*) fp = flame;*/

	network.raiseEvent(true, array, 2+16/*+1*/, 0, 0);
}
