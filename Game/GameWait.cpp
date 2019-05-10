#include "stdafx.h"
#include "GameWait.h"
#include "Network\NetPad.h"
#include "Network\NetManager.h"
#include "Game.h"

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
	DeleteGO(m_spriteRender);
}

bool GameWait::Start() {
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/SankaMulti.dds", 1280.0f, 720.0f);
	NetManager::getNet()->connect();
	NetManager::getNet()->getLocalPlayer().addCustomProperty(readyKey, false);
	NetManager::setWaitRandInit();
	return true;
}

void GameWait::Update() {
	PNetworkLogic* network = NetManager::getNet();

	if (!network->isRoomIn())return;

	if (!allStart) {

		if (Pad(0).IsTrigger(enButtonA)) {
			read = !read;
			network->getLocalPlayer().addCustomProperty(readyKey, read);
		}

		C::JVector<L::Player*> players = NetManager::getNet()->getJoinedRoom().getPlayers();
		for (int i = 0; i < players.getSize(); i++) {
			bool ready = C::ValueObject<bool>(players[i]->getCustomProperties().getValue(readyKey)).getDataCopy();
			if (!ready) {
				return;
			}
		}
	}

	allStart = true;
	if (network->getLocalPlayer().getIsMasterClient()) {
		network->raiseEvent(true, (int64)time(NULL), 3);
	} else if (!NetManager::isRandInit()) {
		return;
	}
	NewGO<Game>(0, "Game")->SetSanSenkazu(network->getPlayersNum().size());
	DeleteGO(this);
}

void GameWait::PostRender(CRenderContext & rc) {
	font.Begin(rc);
	const wchar_t* message = L"";
	PNetworkLogic::ConnectState state = NetManager::getNet()->getState();
	switch (state) {
	case PNetworkLogic::DISCONNECT:
		message = L"disconnected";
		break;
	case PNetworkLogic::TRY_CONNECT:
		message = L"connecting...";
		break;
	case PNetworkLogic::CONNECT:
		message = L"connected";
		break;
	case PNetworkLogic::TRY_ROOMIN:
		message = L"going to room...";
		break;
	}
	if (state != PNetworkLogic::ROOMIN) {
		font.Draw(message, { 0,0 }, { 0, 0, 0 , 1 });
		if (NetManager::getNet()->getErrorCode() != 0) {
			font.Draw(NetManager::getNet()->getErrorMessage().cstr(), { 0, -100 }, { 0, 0, 0 , 1 });
		}
	} else {
		C::JVector<L::Player*> players = NetManager::getNet()->getJoinedRoom().getPlayers();
		float height = 100.0f;
		for (int i = 0; i < players.getSize(); i++) {
			wchar_t str[10];
			swprintf(str, L"player%d", players[i]->getNumber());
			font.Draw(str, { -100, height }, { 0, 0, 0 , 1 }, 0.0f, 1.0f, { 0.0f, 0.5f });

			bool ready = C::ValueObject<bool>(players[i]->getCustomProperties().getValue(readyKey)).getDataCopy();

			if (ready) {
				font.Draw(L"ready", { 400, height }, { 0, 0, 0 , 1 });
			}

			height -= 50;
		}
	}
	font.End(rc);
}
