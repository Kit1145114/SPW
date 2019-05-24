#include "stdafx.h"
#include "Star.h"
#include"Game.h"

Star::Star()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	p_Cpointlit = NewGO < prefab::CPointLight >(0);
	p_Cpointlit->SetAttn({ 5000, 1, 0 });
	p_Cpointlit->SetColor({ 70.0f, 70.0f, 70.0f });
	m_skinModelRender->Init(L"modelData/star.cmo");
	m_scale = { 8.0f, 8.0, 8.0f };
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetEmissionColor({ 1.25, 1.25, 1.25 }); //�����̂����点��R�[�h�B
	m_game = Game::GetInstance();
}


Star::~Star()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(p_Cpointlit);
}



void Star::Update()
{
	Rotation();
	Push();
	m_timer++;
	if (m_timer == Limit)
	{
		m_timer = time0;		//���Ԃō폜�B
		Death();
	}
	if (p_Cpointlit != nullptr) {
		p_Cpointlit->SetPosition(m_position);
	}
}
//�f���̑傫���ɍ��킹�ā��̑傫�������߂�B
void Star::Pop(CVector3 position,CVector3 scale)
{
	m_position = position;
	m_scale = scale;
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
};
//�����o��������ꏊ�̐ݒ�B
void Star::Push()
{
	m_skinModelRender->SetPosition(m_position);
}
//���̉�]
void Star::Rotation()
{
	float SpeedY = 3.0f;
	angle += SpeedY;
	m_rotation.SetRotationDeg(CVector3::AxisY, angle);
	m_skinModelRender->SetRotation(m_rotation);
}
//���̎��S
void Star::Death()
{
	DeleteGO(this);
}

