#include "stdafx.h"
#include "NetManager.h"
#include "Common-cpp/inc/ValueObject.h"

NetManager* NetManager::st_manager = nullptr;

using namespace PhotonLib;
using namespace ExitGames;

NetManager::NetManager() {
	//2重に作られたら古いほうを破棄
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
	//ネットワークをnewする。
	delete network;
	network = new PNetworkLogic(appID, version);
	network->addEventListener(this);
	network->addJoinListener(this);
	network->addLeaveListener(this);
}

void NetManager::PreUpdate() {
	if (network->getState() == PNetworkLogic::DISCONNECT) {//切断状態では何もしない
		return;
	}

	if (!network->isError()) {//エラーが無い場合

		network->Update();

		if (!network->isRoomIn()) {//入室処理
			network->joinOrCreateRoom("Room", 4);//入室まで何度呼んでもいい仕様
			return;
		}

		if (!padInited) {//パッドとプレイヤーの紐づけが贈られるまで待機
			if (network->getLocalPlayer().getIsMasterClient()) {
				padInited = true;//マスタークライアントには必要ない
			} else {
				return;
			}
		}

		//パッド更新
		int localNum = toPadNumber(network->getLocalPlayerNum());//プレイヤー番号をパッド番号に変える

		if (localNum == -1) {
			return;
		}

		pads[localNum].SetFromCPad(Pad(0));//バッファにパッド情報を記録
		pads[localNum].sendState(*network);//photonでパッド情報を送信

		while (true) {
			//自分のパッド入力はラグに合わせてwaitが0になるまで遅延させる
			if (wait == 0) {
				//bool next = true;
				//for (int num = 0; num < CONNECT_PAD_MAX; num++) {//全員のバッファに情報がある場合だけ更新する
				//	if (pNumbers[num] != NON_PAD && !pads[num].hasNext()) {
				//		next = false;
				//		break;
				//	}
				//}
				//if (next == false) {//無い場合フレームを止めて受信を待つ
				//	network->Update();
				//	continue;
				//}
				for (int num = 0; num < CONNECT_PAD_MAX; num++) {//パッド情報を更新する
					if (pNumbers[num] != NON_PAD) {
						pads[num].nextFlame();
					}
				}
			} else {
				wait--;
			}
			break;
		}
	} else {//エラーが出たため切断
		network->disconnect();
		return;
	}
}

void NetManager::onPhotonEvent(int playerNr, nByte eventCode, const ExitGames::Common::Object & eventContent) {
	switch (eventCode) {
		//パッド情報受け取り
	case 0: {
		nByte pNum = toPadNumber(playerNr);
		if (pNum == NON_PAD) {
			return;
		}
		using namespace ExitGames::Common;
		nByte* arrayP = ValueObject<nByte*>(eventContent).getDataCopy();
		pads[pNum].SetFromArray(arrayP);//受信したパッド情報をバッファに記録
	}break;

		//プレイヤー番号とパッド番号の紐づけ受け取り
	case 4: if(!padInited){
		using namespace ExitGames::Common;
		nByte* array = ValueObject<nByte*>(eventContent).getDataCopy();
		for (int i = 0; i < CONNECT_PAD_MAX; i++) {
			pNumbers[i] = array[i];
		}
		padInited = true;
	}break;
	}
}

void NetManager::onLeave(int playerNr) {
	pNumbers[toPadNumber(playerNr)] = NON_PAD;
}

void NetManager::onJoin(int playerNr) {
	bool master = network->getLocalPlayer().getIsMasterClient();
	bool me = (playerNr == network->getLocalPlayerNum());

	//自分でない場合、更新する。マスターは自分も更新する
	if (!me || master){
		for (int i = 0; i < CONNECT_PAD_MAX; i++) {
			if (pNumbers[i] == NON_PAD) {
				pNumbers[i] = playerNr;
				break;
			}
		}
	}

	//マスターかつ自分でない場合だけ情報を教える
	if (!me && master) {
		ExitGames::LoadBalancing::RaiseEventOptions option;
		option.setTargetPlayers(&playerNr, 1);
		network->raiseEvent(true, pNumbers, CONNECT_PAD_MAX, 4, option);
	}
}

void NetManager::resetPadWait() {
	int ping = st_manager->network->GetRoundTripTime();
	st_manager->wait = ping / (GameTime().GetFrameDeltaTime()*1000);
	for (NetPad& pad : st_manager->pads) {
		pad.clearBuffer();
	}
}

void NetManager::PostRender(CRenderContext & rc) {
	font.Begin(rc);
	float height = 300;
	for (NetPad p : pads) {
		wchar_t c[10];
		swprintf(c, L"%d", p.getBuffSize());
		font.Draw(c, { -300.0f, height });
		height -= 200;
	}
	wchar_t c[10];
	swprintf(c, L"%d", NetManager::getNet()->GetRoundTripTime());
	font.Draw(c, { 300.0f, 0});
	font.End(rc);
}

char NetManager::toPadNumber(int playerNr) {
	for (char i = 0; i < CONNECT_PAD_MAX; i++) {
		if (pNumbers[i] == playerNr) {
			return i;
		}
	}
	return -1;
}
