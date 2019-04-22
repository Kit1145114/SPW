#pragma once
#include "NetPad.h"
#include "PNetworkLogic.h"
#include "PEventListener.h"

namespace PhotonLib {
	class PNetworkLogic;
}

class NetManager : public IGameObject, public PhotonLib::PEventListener {
public:
	static const int CONNECT_PAD_MAX = 4;		//接続可能なパッドの最大数。

	NetManager();
	~NetManager();

	/// <summary>
	/// NewGOした後、実行してください
	/// </summary>
	void Init(ExitGames::Common::JString appID, ExitGames::Common::JString version);

	void PreUpdate() override;

	void onPhotonEvent
	(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent) override;

	/*********スタティック関数*********/
	static NetManager* manager() {
		return st_manager;
	}

	static PhotonLib::PNetworkLogic* getNet() {
		return st_manager->network;
	}

	static const NetPad& getPad(int num) {
		return st_manager->pads[num];
	}

	static bool isInited() {
		if (st_manager == nullptr)return false;
		if (st_manager->network == nullptr)return false;
		return true;
	}

	void PostRender(CRenderContext& rc);

private:
	static NetManager* st_manager;//自分を入れておくスタティック変数

	PhotonLib::PNetworkLogic* network = nullptr;
	NetPad pads[CONNECT_PAD_MAX] = {NetPad(0),NetPad(1),NetPad(2),NetPad(3) };
	CFont font;
	int wait = 20;
};

