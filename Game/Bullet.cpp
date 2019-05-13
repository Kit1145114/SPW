#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
	DeleteGO(m_skinModelRender);
}

bool Bullet::Start()
{
	m_game = FindGO<Game>("Game");
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	if (PB == 0)
	{
		m_skinModelRender->Init(L"modelData/Bulet.cmo");
	}
	else if (PB == 1)
	{
		m_skinModelRender->Init(L"modelData/Bullet2.cmo");
	}
	else if (PB == 2)
	{
		m_skinModelRender->Init(L"modelData/Bullet3.cmo");
	}
	else if (PB == 3)
	{
		m_skinModelRender->Init(L"modelData/Bullet4.cmo");
	}
	m_scale = { 5.0f,5.0f,5.0f };
	m_skinModelRender->SetScale(m_scale);
	return true;
}

void Bullet::Update()
{
	m_position += m_moveSpeed;
	m_position.y = 100.0f;
	m_skinModelRender->SetPosition(m_position);

	m_timer++;
	if (m_timer == Limit)
	{
		Death();
	}
}

int Bullet::GetPB()
{
	switch (PB)
	{
		case 0:
			return 0;
			break;
		case 1:
			return 1;
			break;
		case 2:
			return 2;
			break;
		case 3:
			return 3;
			break;
	}
}

void Bullet::Death()
{
	DeleteGO(this);
	m_game->SetKazu(-1);
}