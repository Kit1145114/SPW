#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

bool Bullet::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Bulet.cmo");
	return true;
}

void Bullet::Update()
{
	m_position += m_moveSpeed;

	m_skinModelRender->SetPosition(m_position);
	m_timer++;
	if (m_timer == 100)
	{
		DeleteGO(this);
	}
}