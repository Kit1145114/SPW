#include "stdafx.h"
#include "GameWait.h"
#include "PNetworkLogic.h"

using namespace PhotonLib;

GameWait::GameWait() {}

GameWait::~GameWait() {
	delete network;
}

void GameWait::Init(PNetworkLogic * network_) {
	if (network_ != nullptr) {
		network = network_;
	} else {
		network = new PNetworkLogic(appID, version);
	}
	inited = true;
}

bool GameWait::Start() {
	if (!inited) {
		//NewGO‚µ‚½ŒãAInitŠÖ”‚ðŽÀs‚µ‚Ä‚­‚¾‚³‚¢B
		return false;
	}
	network->connect();
	return true;
}

void GameWait::Update() {

	if (!network->isError()) {

		network->Update();

		if (!roomIn) {//“üŽºˆ—
			network->joinOrCreateRoom("Room", 4);
			if (network->isRoomIn()) {
				roomIn = true;
			}
			return;
		}

		if (Pad(0).IsTrigger(enButtonA)) {
			network->disconnect();
		}

	}else {
		network->disconnect();
		return;
	}
}

void GameWait::PostRender(CRenderContext & rc) {
	font.Begin(rc);
	const wchar_t* message;
	switch (network->getState()) {
	case PNetworkLogic::DISCONNECT:
		message = L"Disconnected";
		break;
	case PNetworkLogic::TRY_CONNECT:
		message = L"Connecting...";
		break;
	case PNetworkLogic::CONNECT:
		message = L"Connected";
		break;
	case PNetworkLogic::TRY_ROOMIN:
		message = L"Going to room...";
		break;
	case PNetworkLogic::ROOMIN:
		message = L"now in Room";
		break;
	}

	font.Draw(message, { 0,0 });
	font.End(rc);
}
