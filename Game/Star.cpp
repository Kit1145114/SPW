#include "stdafx.h"
#include "Star.h"


Star::Star()
{
}


Star::~Star()
{
	DeleteGO(m_skinModelRender);
}

bool Star::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/star.cmo");
	//m_CharaCon.Init(80.0f, 30.0f, m_position);
	m_player = FindGO<Player>("Player");
	m_game = FindGO<Game>("Game");
	m_scale = { 3.0f, 3.0, 3.0f };
	m_skinModelRender->SetScale(m_scale);
	return true;
}

void Star::Update()
{
	Hantei();
	Rotation();
	Push();
	m_timer++;
	if (m_timer == 300)
	{
		m_game->m_star = nullptr;
		DeleteGO(this);
		m_timer = 0;
	}
}
//™‚ÌŽæ“¾”»’èB
void Star::Hantei()
{
	if (m_game->m_player != nullptr)
	{
		CVector3 diff = m_player->GetPosition() - m_position;
		if (diff.Length() < 250.0f)
		{
			m_player->SetVer(1);
			//m_game->Pver = 1;
			m_game->m_star = nullptr;
			Death();
		}
	}
	else if (m_game->m_player == nullptr)
	{

	}
}

void Star::Push()
{
	m_skinModelRender->SetPosition(m_position);
}

void Star::Rotation()
{
	angle += 3.0f;
	m_rotation.SetRotationDeg(CVector3::AxisY, angle);
	m_rotation.SetRotationDeg(CVector3::AxisZ, angle);
	m_skinModelRender->SetRotation(m_rotation);
}

void Star::Death()
{
	DeleteGO(this);
}