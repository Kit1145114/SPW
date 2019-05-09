#include "stdafx.h"
#include "Camera.h"
#include "Game.h"
#include "Network/NetManager.h"

Camera::Camera()
{
}


Camera::~Camera()
{
}

bool Camera::Start() {
	//�J�����̃j�A�N���b�v
	MainCamera().SetUp(CVector3::AxisZ);
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(100000.0f);

	//�����̃v���C���[�ԍ����擾�Bphoton�ł�0����łȂ�1����n�܂邽�߃}�C�i�X�P����B
	int myNum = NetManager::getLocalNum();
	m_player = Game::GetInstance()->m_player[myNum];

	return true;
}

void Camera::TOP() {
	//�J����
	if (Pad(0).IsPress(enButtonUp)) {
		up += -100.0f;
	}else
	if (Pad(0).IsPress(enButtonDown)) {
		up += 100.0f;
	}

	if (up > MaxCamera) {
		up = MaxCamera;
	} else if (MinCamera > up) {
		up = MinCamera;
	}
}

void Camera::Move() {
	//�Y�[�����A�E�g

}

void Camera::Update() {
	TOP();
	//Move();
	//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	CVector3 pos = m_player->GetPosition();
	MainCamera().SetTarget(pos);
	pos.y += up;
	MainCamera().SetPosition(pos);
	//�J�����̍X�V�B
	MainCamera().Update();
}

