#include "stdafx.h"
#include "GameWait.h"
#include "NetPad.h"
#include "Game.h"

using namespace PhotonLib;

GameWait::GameWait() {
	if (NetPadManager::manager().isInited()) {
		network = NetPadManager::manager().getNetwork();
		roomIn = true;
	} else {
		network = new PNetworkLogic(appID, version);
	}
}

GameWait::~GameWait() {
	delete network;
}

bool GameWait::Start() {
	if (!roomIn) {
		network->connect();
	}
	return true;
}

void GameWait::Update() {

	if (!network->isError()) {

		network->Update();

		if (!roomIn) {//入室処理
			network->joinOrCreateRoom("Room", 4);
			if (network->isRoomIn()) {
				roomIn = true;
			}
			return;
		}

		//入室完了後の処理
		if (!NetPadManager::manager().isInited()) {//パッドマネージャーを初期化
			NetPadManager::manager().Init(network);
		}

		if (Pad(0).IsTrigger(enButtonA)) {//Aボタンで開始
			DeleteGO(this);
			NewGO<Game>(0, "Game");
		}

	}else {//エラーが出たため切断
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
