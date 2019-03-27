#include "stdafx.h"
#include "Star.h"


Star::Star()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/star.cmo");
	m_scale = { 3.0f, 3.0, 3.0f };
	m_skinModelRender->SetScale(m_scale);
	m_player = FindGO<Player>("Player");
	m_game = FindGO<Game>("Game");
}


Star::~Star()
{
	DeleteGO(m_skinModelRender);
}

bool Star::Start()
{
	
	
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
	//if (m_game->m_player != nullptr)
	//{
	//	CVector3 diff = m_player->GetPosition() - m_position;
	//	if (diff.Length() < 250.0f)
	//	{
	//		m_player->SetStarCount(1);
	//		//m_game->Pver = 1;
	//		m_game->m_star = nullptr;
	//		Death();
	//	}
	//}
	//else if (m_game->m_player == nullptr)
	//{

	//}
}
void Star::Pop(CVector3 position)
{
	m_position = position;
	m_skinModelRender->SetPosition(m_position);
};
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

