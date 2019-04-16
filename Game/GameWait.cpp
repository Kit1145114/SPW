#include "stdafx.h"
#include "GameWait.h"
#include "Game.h"
#include "Network\NetPad.h"
#include "Network\NetManager.h"

using namespace PhotonLib;

GameWait::GameWait() {
	if (!NetManager::isInited()) {
		NewGO<NetManager>(0)->Init(appID, version);
	}
}

GameWait::~GameWait() {
}

void GameWait::Update() {
	if (!NetManager::getNet()->isRoomIn())return;

	if (NetManager::getNet()->getLocalPlayer().getIsMasterClient() && Pad(0).IsTrigger(enButtonA)) {
		NewGO<Game>(0, "Game");
		DeleteGO(this);
	}
}

void GameWait::PostRender(CRenderContext & rc) {
	font.Begin(rc);
	const wchar_t* message;
	switch (NetManager::getNet()->getState()) {
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
