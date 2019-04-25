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

		//パッド更新
		int localNum = network->getLocalPlayerNum() - 1;//photonのナンバーは0でなく1から始まるため1減らす
		pads[localNum].SetFromCPad(Pad(0));//バッファにパッド情報を記録
		pads[localNum].sendState(*network);//photonでパッド情報を送信

		while (true) {
			//自分のパッド入力はラグに合わせてwaitが0になるまで遅延させる
			if (wait == 0) {
				bool next = true;
				for (int num : network->getPlayersNum()) {//全員のバッファに情報がある場合だけ更新する
					if (!pads[num - 1].hasNext()) {
						next = false;
					}
				}
				if (next == false) {//無い場合フレームを止めて受信を待つ
					network->Update();
					continue;
				}
				for (int num : network->getPlayersNum()) {//パッド情報を更新する
					pads[num - 1].nextFlame();
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
	using namespace ExitGames::Common;
	nByte* arrayP = ValueObject<nByte*>(eventContent).getDataCopy();
	pads[playerNr - 1].SetFromArray(arrayP);//受信したパッド情報をバッファに記録
}

void NetManager::resetPadWait() {
	int ping = st_manager->network->GetRoundTripTime();
	st_manager->wait = ping / 2 / (GameTime().GetFrameDeltaTime()*1000);
	for (NetPad& pad : st_manager->pads) {
		pad.clearBuffer();
	}
}

//void NetManager::PostRender(CRenderContext & rc) {
//	font.Begin(rc);
//	float height = 300;
//	for (NetPad p : pads) {
//		wchar_t c[10];
//		swprintf(c, L"%d", p.sssss());
//		font.Draw(c, { -300.0f, height });
//		height -= 200;
//	}
//	font.End(rc);
//}
