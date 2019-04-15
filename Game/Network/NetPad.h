#pragma once
#include "..\tkEngine\Input\tkPad.h"
#include "PEventListener.h"
#include "PNetworkLogic.h"

class NetPad {
public:
	NetPad() {};
	~NetPad() {};

private:
	bool m_press[enButtonNum] = {};
	bool m_trigger[enButtonNum] = {};
};

class NetPadManager : public PhotonLib::PEventListener , public IGameObject{
public:
	static const int CONNECT_PAD_MAX = 4;		//接続可能なパッドの最大数。

	static NetPadManager& manager() {
		return st_manager;
	}

	NetPadManager() = default;
	~NetPadManager() {
		delete network;
	}

	PhotonLib::PNetworkLogic* getNetwork() {
		return network;
	}

	const NetPad& getPad(int num) {
		return pads[num];
	}

	void Init(PhotonLib::PNetworkLogic* network_) {
		if (!isInited) {
			network = network_;
			network->addEventListener(this);
		}
	}

	bool isInited() {
		return network != nullptr;
	}

	//イベントを受け取る関数。PEventListenerからのオーバーライド。
	void onPhotonEvent(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent) override;

private:
	static NetPadManager st_manager;
	PhotonLib::PNetworkLogic* network = nullptr;
	NetPad pads[CONNECT_PAD_MAX] = {};
};

const NetPad& NPad(int num) {
	return NetPadManager::manager().getPad(num);
}
