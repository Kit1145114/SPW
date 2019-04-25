#pragma once
#include "NetPad.h"
#include "PNetworkLogic.h"
#include "PEventListener.h"

namespace PhotonLib {
	class PNetworkLogic;
}

class NetManager : public IGameObject, public PhotonLib::PEventListener {
public:
	static const int CONNECT_PAD_MAX = 4;		//�ڑ��\�ȃp�b�h�̍ő吔�B

	NetManager();
	~NetManager();

	/// <summary>
	/// NewGO������A���s���Ă��������B
	/// </summary>
	/// <param name="appID">photon��appID(�z�[���y�[�W����擾)</param>
	/// <param name="version">�o�[�W����(���R�Ɍ��߂Ă���)</param>
	void Init(ExitGames::Common::JString appID, ExitGames::Common::JString version);

	void PreUpdate() override;

	/// <summary>
	/// photon������Ă΂��֐��B�����ŌĂ΂Ȃ��B
	/// </summary>
	/// <param name="playerNr">�v���C���[�ԍ�</param>
	/// <param name="eventCode">�C�x���g�R�[�h</param>
	/// <param name="eventContent">�f�[�^</param>
	void onPhotonEvent
	(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent) override;

	/*********�X�^�e�B�b�N�֐�*********/

	static void resetPadWait();

	/// <summary>
	/// �}�l�[�W���[���폜�B�Q�[���I�����ȊO�Ă΂Ȃ��B
	/// </summary>
	static void deleteManager() {
		 delete st_manager;
	}

	/// <summary>
	/// �l�b�g���[�N���擾
	/// </summary>
	/// <returns></returns>
	static PhotonLib::PNetworkLogic* getNet() {
		return st_manager->network;
	}

	/// <summary>
	/// �p�b�h���擾
	/// </summary>
	/// <param name="num">�p�b�h�̔ԍ�(0�`3)</param>
	/// <returns></returns>
	static const NetPad& getPad(int num) {
		return st_manager->pads[num];
	}

	/// <summary>
	/// �l�b�g�}�l�[�W���[��Init�ς݂Ȃ�true
	/// </summary>
	/// <returns></returns>
	static bool isInited() {
		if (st_manager == nullptr)return false;
		if (st_manager->network == nullptr)return false;
		return true;
	}

	//�f�o�b�O�̎��g���Ă��B�܂��g����������Ȃ����Ȃ��B
	//void PostRender(CRenderContext& rc);

private:
	static NetManager* st_manager;//���������Ă����X�^�e�B�b�N�ϐ�

	PhotonLib::PNetworkLogic* network = nullptr;
	NetPad pads[CONNECT_PAD_MAX] = {NetPad(0),NetPad(1),NetPad(2),NetPad(3) };

	CFont font;
	unsigned int wait = 20;
};

