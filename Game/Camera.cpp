#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}
bool Camera::Start() {

	m_CameraPos.Set(0.0f, 50.0f, 300.0f);
	m_player = FindGO<Player>("Player");

	//�J�����̃j�A�N���b�v
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(10000.0f);
	return true;
}
void Camera::TOP() {

	target = m_player->m_position - m_CameraPos;

	//�p�b�h�̓��͂��g���ăJ��������
	//float x = Pad(0).GetRStickXF();
	//float y = Pad(0).GetRStickYF();

	MainCamera().GetForward();




}
void Camera::Update() {

	TOP();
	//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	MainCamera().SetTarget(target);
	MainCamera().SetPosition(pos);
	//�J�����̍X�V�B
	MainCamera().Update();

}

