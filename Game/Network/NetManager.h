#pragma once
#include "NetPad.h"
#include "PNetworkLogic.h"
#include "PEventListener.h"

namespace PhotonLib {
	class PNetworkLogic;
}

class NetManager : public IGameObject,
	public PhotonLib::PEventListener,
	public PhotonLib::PJoinListener,
	public PhotonLib::PLeaveListener{
public:
	static const int CONNECT_PAD_MAX = 4;		//接続可能なパッドの最大数。

	NetManager();
	~NetManager();

	/// <summary>
	/// NewGOした後、実行してください。
	/// </summary>
	/// <param name="appID">photonのappID(ホームページから取得)</param>
	/// <param name="version">バージョン(自由に決めていい)</param>
	void Init(ExitGames::Common::JString appID, ExitGames::Common::JString version);

	void PreUpdate() override;

	/// <summary>
	/// photon側から呼ばれる関数。自分で呼ばない。
	/// </summary>
	void onPhotonEvent
	(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent) override;

	/// <summary>
	/// photon側から呼ばれる関数。自分で呼ばない。
	/// </summary>
	/// <param name="playerNr"></param>
	void onLeave(int playerNr) override;

	/// <summary>
	/// photon側から呼ばれる関数。自分で呼ばない。
	/// </summary>
	/// <param name="playerNr"></param>
	void onJoin(int playerNr) override;

	/*********スタティック関数*********/

	static void resetPadWait();

	/// <summary>
	/// マネージャーを削除。ゲーム終了時以外呼ばない。
	/// </summary>
	static void deleteManager() {
		 delete st_manager;
	}

	static nByte getLocalNum() {
		return st_manager->toPadNumber(st_manager->network->getLocalPlayerNum());
	}

	/// <summary>
	/// ネットワークを取得
	/// </summary>
	/// <returns></returns>
	static PhotonLib::PNetworkLogic* getNet() {
		return st_manager->network;
	}

	/// <summary>
	/// パッドを取得
	/// </summary>
	/// <param name="num">パッドの番号(0～3)</param>
	/// <returns></returns>
	static const NetPad& getPad(int num) {
		return st_manager->pads[num];
	}

	static bool setWaitRandInit() {
		return st_manager->initRandSeed = false;
	}

	static bool isRandInit() {
		return st_manager->initRandSeed;
	}

	/// <summary>
	/// ネットマネージャーがInit済みならtrue
	/// </summary>
	/// <returns></returns>
	static bool isInited() {
		if (st_manager == nullptr)return false;
		if (st_manager->network == nullptr)return false;
		return true;
	}

	//デバッグの時使ってた。また使うかもしれなくもない。
	void PostRender(CRenderContext& rc);

private:
	char toPadNumber(int playerNr);

	static NetManager* st_manager;//自分を入れておくスタティック変数

	PhotonLib::PNetworkLogic* network = nullptr;
	NetPad pads[CONNECT_PAD_MAX] = {NetPad(0),NetPad(1),NetPad(2),NetPad(3) };

	static constexpr nByte NON_PAD = 255;
	nByte pNumbers[CONNECT_PAD_MAX] = { NON_PAD, NON_PAD, NON_PAD, NON_PAD };
	bool padInited = false;

	bool initRandSeed = false;

	CFont font;
	unsigned int wait = 0;
};

