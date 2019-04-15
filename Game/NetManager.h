#pragma once
#include "PNetworkLogic.h"

class NetManager : public IGameObject{
public:
	NetManager();
	~NetManager();

	/// <summary>
	/// NewGO������A���̃t���[���܂łɎ��s���Ă�������
	/// </summary>
	void Init(ExitGames::Common::JString appID, ExitGames::Common::JString version);

	void Update() override;

	void connect();
	
	PhotonLib::PNetworkLogic& getNet() {
		return network;
	}

private:
	PhotonLib::PNetworkLogic network;
};

