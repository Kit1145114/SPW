#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

bool Camera::Start() {
	//�v���C���[�̌���
	m_player = FindGO<Player>("Player");
	m_game = FindGO<Game>("Game");
	//�J�����̃j�A�N���b�v
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(10000.0f);

	return true;
}
void Camera::TOP() {

	m_CameraPos = m_player->memoryPosition();
	m_CameraPos.y += st_kyori;
	
	target = m_player->memoryPosition() - m_CameraPos;

	//�p�b�h�̓��͂��g���ăJ��������
	//float x = Pad(0).GetRStickXF();
	//float y = Pad(0).GetRStickYF();

	MainCamera().SetUp(CVector3::AxisZ);
}
void Camera::Move() {
	//�Y�[�����A�E�g
	if (st_kyori>200.0) {
		//��
		if (Pad(0).GetRStickYF() > 0.0) {
			st_kyori -= 10.0f;
		}
	}
	if (st_kyori<8000.0) {
		//��O
		if (Pad(0).GetRStickYF() < 0.0) {
			st_kyori += 10.0f;
		}
	}
}
void Camera::Update() {
	TOP();
	Move();
	//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	MainCamera().SetTarget(m_player->memoryPosition());
	MainCamera().SetPosition(m_CameraPos);
	//�J�����̍X�V�B
	MainCamera().Update();
}

