#include "stdafx.h"
#include "GameWait.h"
#include "Game.h"
#include "Network\NetPad.h"
#include "Network\NetManager.h"

using namespace PhotonLib;
using namespace ExitGames;

GameWait::GameWait() {
	if (!NetManager::isInited()) {
		NewGO<NetManager>(0)->Init(appID, version);
	}
}

GameWait::~GameWait() {
}

void GameWait::Update() {
	PNetworkLogic* network = NetManager::getNet();

	if (!network->isRoomIn())return;

	for (int num : network->getPlayersNum()) {
		if (NetManager::getPad(num-1).IsTrigger(enButtonA)) {
			ready[num - 1] = !ready[num - 1];
		}
	}

	if (Pad(0).IsTrigger(enButtonB)) {
		int i = 5;
	}

	/*bool start = true;
	Common::JVector<LoadBalancing::Player*> players = NetManager::getNet()->getJoinedRoom().getPlayers();
	for (int i = 0; i < players.getSize(); i++) {
		const Common::Object* prop = players[i]->getCustomProperties().getValue(0);
		if (prop == nullptr || !Common::ValueObject<bool>(prop).getDataCopy()) {
			start = false;
		}
	}*/

	/*if (start) {
		NewGO<Game>(0, "Game");
		DeleteGO(this);
	}*/
}

void GameWait::PostRender(CRenderContext & rc) {
	font.Begin(rc);
	const wchar_t* message = L"";
	PNetworkLogic::ConnectState state = NetManager::getNet()->getState();
	switch(state) {
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
	}
	if (state != PNetworkLogic::ROOMIN) {
		font.Draw(message, { 0,0 });
	} else {
		Common::JVector<LoadBalancing::Player*> players = NetManager::getNet()->getJoinedRoom().getPlayers();
		float height = 100.0f;
		for (int i = 0; i < players.getSize(); i++) {
			wchar_t str[10];
			swprintf(str, L"player%d", players[i]->getNumber());
			font.Draw(str, { 0, height});

			if (ready[players[i]->getNumber() - 1]) {
				font.Draw(L"ready", { 400, height });
			}

			height -= 50;
		}
	}
	font.End(rc);
}
