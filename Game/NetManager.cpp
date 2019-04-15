#include "stdafx.h"
#include "NetManager.h"


NetManager::NetManager() {
}


NetManager::~NetManager() {
}

void NetManager::Init(PNetworkLogic * network_) {
	if (network_ != nullptr) {
		network = network_;
	} else {
		network = new PNetworkLogic(appID, version);
	}
	inited = true;
}
