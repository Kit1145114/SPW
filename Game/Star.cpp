#include "stdafx.h"
#include "Star.h"
#include"Game.h"

Star::Star()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	/*p_Cpointlit = NewGO < prefab::CPointLight >(0);
	p_Cpointlit->SetAttn({ 8000, 1, 0 });
	p_Cpointlit->SetColor({ 70.0f, 70.0f, 70.0f });*/
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
//��ɍs�������B
void Star::Update()
{
	Rotation();
	Push();
	time += GameTime().GetFrameDeltaTime();
	if (time > Limit)
	{
		time = time0;		//���Ԃō폜�B
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
	m_scale *= 1.2;
	//���̑傫���ɂ���ă|�C���g��ς���B
	if (m_scale.x< StarScale/2) {
		StarPoint = 1;
	}
	else if (m_scale.x < StarScale) {
		StarPoint = 2;
	}
	else  {
		StarPoint = 3;
	}

	m_position.y += 30.0f;
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
};
//���z�̑傫���ɍ��킹�ā��̑傫�������߂�B
void Star::SunPop(CVector3 position, CVector3 scale)
{
	m_position = position;
	m_position.y += 30.0f;
	m_scale = scale;
	Limit = 15.0f;
	m_skinModelRender->Init(L"modelData/PlayerStar.cmo");
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
	float SpeedY = 2.0f;
	angle += SpeedY;
	m_rotation.SetRotationDeg(CVector3::AxisY, angle);
	m_skinModelRender->SetRotation(m_rotation);
}
//���̎��S
void Star::Death()
{
	DeleteGO(this);
}

