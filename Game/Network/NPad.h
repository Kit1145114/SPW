#pragma once
#include "NetManager.h"
#include "NetPad.h"

const inline NetPad& NPad(int num) {
	return NetManager::getPad(num);
}