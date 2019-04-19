#include "stdafx.h"
#include "NetManager.h"
#include "Common-cpp/inc/ValueObject.h"

NetManager* NetManager::st_manager = nullptr;

using namespace PhotonLib;
using namespace ExitGames;

NetManager::NetManager() {
	if (NetManager::st_manager != nullptr) {
		delete NetManager::st_manager;
	}
	NetManager::st_manager = this;
}


NetManager::~NetManager() {
	if (network != nullptr && network->isConnecting()) {
		network->disconnect();
	}
	delete network;
	NetManager::st_manager = nullptr;
}

void NetManager::Init(ExitGames::Common::JString appID, ExitGames::Common::JString version) {
	delete network;
	network = new PNetworkLogic(appID, version);
	network->connect();
	network->addEventListener(this);
}

void NetManager::PreUpdate() {
	if (network->getState() == PNetworkLogic::DISCONNECT) {
		return;
	}

	if (!network->isError()) {

		network->Update();

		if (!network->isRoomIn()) {//入室処理
			network->joinOrCreateRoom("Room", 4);
			return;
		}

		//パッド更新
		int localNum = network->getLocalPlayerNum() - 1;
		pads[localNum].SetFromCPad(Pad(0));
		pads[localNum].sendState(*network);
		bool next = true;
		for (int num : network->getPlayersNum()) {
			if (!pads[num - 1].hasNext()) {
				next = false;
				break;
			}
		}
		if (next) {
			for (int num : network->getPlayersNum()) {
				pads[num - 1].nextFlame();
			}
		}
			
		if (flameNum == 255) {
			flameNum = 0;
		} else {
			flameNum++;
		}

	} else {//エラーが出たため切断
		network->disconnect();
		return;
	}
}

void NetManager::onPhotonEvent(int playerNr, nByte eventCode, const ExitGames::Common::Object & eventContent) {
	using namespace ExitGames::Common;
	nByte* arrayP = ValueObject<nByte*>(eventContent).getDataCopy();
	pads[playerNr - 1].SetFromArray(arrayP);
}
