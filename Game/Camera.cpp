#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}
bool Camera::Start() {

	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(10000.0f);
	return true;
}

void Camera::Update() {

	//�����_���v�Z
	CVector3 target = { 0.0f,0.0f,0.0f };

	//���_���v�Z����B
	CVector3 pos = target + m_CameraPos;
	//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	MainCamera().SetTarget(target);
	MainCamera().SetPosition(pos);
	//�J�����̍X�V�B
	MainCamera().Update();

}