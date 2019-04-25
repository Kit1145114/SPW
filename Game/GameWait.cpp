#include "stdafx.h"
#include "GameWait.h"
#include "Network\NetPad.h"
#include "Network\NetManager.h"
#include "Game.h"
#include "SansenKazu.h"

using namespace PhotonLib;
namespace C = ExitGames::Common;
namespace L = ExitGames::LoadBalancing;

static C::JString readyKey = "r";

GameWait::GameWait() {
	if (!NetManager::isInited()) {
		NewGO<NetManager>(0)->Init(appID, version);
	}
}

GameWait::~GameWait() {
}

bool GameWait::Start() {
	NetManager::getNet()->connect();
	NetManager::getNet()->getLocalPlayer().addCustomProperty(readyKey, false);
	return true;
}

void GameWait::Update() {
	PNetworkLogic* network = NetManager::getNet();

	if (!network->isRoomIn())return;

	if (Pad(0).IsTrigger(enButtonA)) {
		read = !read;
		network->getLocalPlayer().addCustomProperty(readyKey, read);
	}

	bool start = true;
	C::JVector<L::Player*> players = NetManager::getNet()->getJoinedRoom().getPlayers();
	for (int i = 0; i < players.getSize(); i++) {
		bool ready = C::ValueObject<bool>(players[i]->getCustomProperties().getValue(readyKey)).getDataCopy();
		if (!ready) {
			start = false;
			break;
		}
	}

	if (start) {
		SansenKazu* sansenkazu = NewGO<SansenKazu>(0, "SansenKazu");
		sansenkazu->DeathCount(true);
		sansenkazu->SetKazu(network->getPlayersNum().size());
		NewGO<Game>(0, "Game");
		NetManager::resetPadWait();
		DeleteGO(this);
	}
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
		if (NetManager::getNet()->getErrorCode() != 0) {
			font.Draw(NetManager::getNet()->getErrorMessage().cstr(), { 0, -100 });
		}
	} else {
		C::JVector<L::Player*> players = NetManager::getNet()->getJoinedRoom().getPlayers();
		float height = 100.0f;
		for (int i = 0; i < players.getSize(); i++) {
			wchar_t str[10];
			swprintf(str, L"player%d", players[i]->getNumber());
			font.Draw(str, { 0, height});

			bool ready = C::ValueObject<bool>(players[i]->getCustomProperties().getValue(readyKey)).getDataCopy();

			if (ready) {
				font.Draw(L"ready", { 400, height });
			}

			height -= 50;
		}
	}
	font.End(rc);
}
