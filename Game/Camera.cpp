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

	//�����̃v���C���[�ԍ����擾�B
	int myNum
#ifdef UseNetwork
		= NetManager::getLocalNum();
#else
		= 0;
#endif
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
	//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	float cameraUp = 0.0f;
#ifdef UseNetwork
	CVector3 pos = m_player->GetPosition();
	cameraUp = up;
#else
	CVector3 pos;
	if (Game::GetInstance()->GetSansenKazu() == 1) {
		pos = m_player->GetPosition();
		cameraUp = up;
	} else {
		int count = 0;
		for (Player* player : Game::GetInstance()->m_player) {
			if (player != nullptr) {
				pos += player->GetPosition();
				count++;
			}
		}
		pos /= count;
		for (Player* player : Game::GetInstance()->m_player) {
			if (player != nullptr) {
				float f = (pos - player->GetPosition()).Length();
				if (cameraUp < f) {
					cameraUp = f;
				}
			}
		}
		cameraUp *= 1.9f;
	}
#endif
	MainCamera().SetTarget(pos);
	pos.y += cameraUp;
	MainCamera().SetPosition(pos);
	//�J�����̍X�V�B
	MainCamera().Update();
}

