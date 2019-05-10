#include "stdafx.h"
#include "NetManager.h"
#include "Common-cpp/inc/ValueObject.h"

NetManager* NetManager::st_manager = nullptr;

using namespace PhotonLib;
using namespace ExitGames;

NetManager::NetManager() {
	//2�d�ɍ��ꂽ��Â��ق���j��
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
	//�l�b�g���[�N��new����B
	delete network;
	network = new PNetworkLogic(appID, version);
	network->addEventListener(this);
	network->addJoinListener(this);
	network->addLeaveListener(this);
}

void NetManager::PreUpdate() {
	if (network->getState() == PNetworkLogic::DISCONNECT) {//�ؒf��Ԃł͉������Ȃ�
		return;
	}

	if (!network->isError()) {//�G���[�������ꍇ

		network->Update();

		if (!network->isRoomIn()) {//��������
			network->joinOrCreateRoom("Room", 4);//�����܂ŉ��x�Ă�ł������d�l
			return;
		}

		if (!padInited) {//�p�b�h�ƃv���C���[�̕R�Â���������܂őҋ@
			if (network->getLocalPlayer().getIsMasterClient()) {
				padInited = true;//�}�X�^�[�N���C�A���g�ɂ͕K�v�Ȃ�
			} else {
				return;
			}
		}

		//�p�b�h�X�V
		int localNum = toPadNumber(network->getLocalPlayerNum());//�v���C���[�ԍ����p�b�h�ԍ��ɕς���

		if (localNum == -1) {
			return;
		}

		pads[localNum].SetFromCPad(Pad(0));//�o�b�t�@�Ƀp�b�h�����L�^
		pads[localNum].sendState(*network);//photon�Ńp�b�h���𑗐M

		while (true) {
			//�����̃p�b�h���͂̓��O�ɍ��킹��wait��0�ɂȂ�܂Œx��������
			if (wait == 0) {
				//bool next = true;
				//for (int num = 0; num < CONNECT_PAD_MAX; num++) {//�S���̃o�b�t�@�ɏ�񂪂���ꍇ�����X�V����
				//	if (pNumbers[num] != NON_PAD && !pads[num].hasNext()) {
				//		next = false;
				//		break;
				//	}
				//}
				//if (next == false) {//�����ꍇ�t���[�����~�߂Ď�M��҂�
				//	network->Update();
				//	continue;
				//}
				for (int num = 0; num < CONNECT_PAD_MAX; num++) {//�p�b�h�����X�V����
					if (pNumbers[num] != NON_PAD) {
						pads[num].nextFlame();
					}
				}
			} else {
				wait--;
			}
			break;
		}
	} else {//�G���[���o�����ߐؒf
		network->disconnect();
		return;
	}
}

void NetManager::onPhotonEvent(int playerNr, nByte eventCode, const ExitGames::Common::Object & eventContent) {
	switch (eventCode) {
		//�p�b�h���󂯎��
	case 0: {
		nByte pNum = toPadNumber(playerNr);
		if (pNum == NON_PAD) {
			return;
		}
		using namespace ExitGames::Common;
		nByte* arrayP = ValueObject<nByte*>(eventContent).getDataCopy();
		pads[pNum].SetFromArray(arrayP);//��M�����p�b�h�����o�b�t�@�ɋL�^
	}break;

		//�v���C���[�ԍ��ƃp�b�h�ԍ��̕R�Â��󂯎��
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

	//�����łȂ��ꍇ�A�X�V����B�}�X�^�[�͎������X�V����
	if (!me || master){
		for (int i = 0; i < CONNECT_PAD_MAX; i++) {
			if (pNumbers[i] == NON_PAD) {
				pNumbers[i] = playerNr;
				break;
			}
		}
	}

	//�}�X�^�[�������łȂ��ꍇ��������������
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
