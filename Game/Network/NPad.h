#pragma once
#include "NetManager.h"
#include "NetPad.h"

#define UseNetwork

#ifdef UseNetwork
const inline NetPad& NPad(int num) {
	return NetManager::getPad(num);
}
#else
inline CPad& NPad(int num) {
	return Pad(num);
}
#endif