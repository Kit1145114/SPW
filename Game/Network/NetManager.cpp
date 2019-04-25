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

		//�p�b�h�X�V
		int localNum = network->getLocalPlayerNum() - 1;//photon�̃i���o�[��0�łȂ�1����n�܂邽��1���炷
		pads[localNum].SetFromCPad(Pad(0));//�o�b�t�@�Ƀp�b�h�����L�^
		pads[localNum].sendState(*network);//photon�Ńp�b�h���𑗐M

		while (true) {
			//�����̃p�b�h���͂̓��O�ɍ��킹��wait��0�ɂȂ�܂Œx��������
			if (wait == 0) {
				bool next = true;
				for (int num : network->getPlayersNum()) {//�S���̃o�b�t�@�ɏ�񂪂���ꍇ�����X�V����
					if (!pads[num - 1].hasNext()) {
						next = false;
					}
				}
				if (next == false) {//�����ꍇ�t���[�����~�߂Ď�M��҂�
					network->Update();
					continue;
				}
				for (int num : network->getPlayersNum()) {//�p�b�h�����X�V����
					pads[num - 1].nextFlame();
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
	using namespace ExitGames::Common;
	nByte* arrayP = ValueObject<nByte*>(eventContent).getDataCopy();
	pads[playerNr - 1].SetFromArray(arrayP);//��M�����p�b�h�����o�b�t�@�ɋL�^
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
