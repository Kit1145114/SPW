#pragma once
#include "PNetworkLogic.h"

class NetManager : public IGameObject{
public:
	NetManager();
	~NetManager();

	/// <summary>
	/// NewGOした後、次のフレームまでに実行してください
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

