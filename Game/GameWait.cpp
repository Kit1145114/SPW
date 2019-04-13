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
	NetMessage = L"Connecting...";
	return true;
}

void GameWait::Update() {
	if (disco) {
		return;
	}

	if (network->isError()) {
		return;
	}

	network->Update();
	flame++;

	if (flame == 500) {
		flame = 500;
	}

	if (network->isError()) {
		NetMessage = L"Error";
		network->disconnect();
		disco = true;
		return;
	}

	if (network->isConnecting()) {
		NetMessage = L"Connect!";
		network->joinOrCreateRoom("Room", 4);
	} else {
		return;
	}

	if (network->isRoomIn()) {
		NetMessage = L"Room In!";
	}
}

void GameWait::PostRender(CRenderContext & rc) {
	font.Begin(rc);
	wchar_t txt[256];
	swprintf(txt, L"%d", flame);
	font.Draw(txt, { 0,100 });
	font.Draw(NetMessage, { 0,0 });
	font.End(rc);
}
