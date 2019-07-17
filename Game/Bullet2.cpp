#include "stdafx.h"
#include "Bullet2.h"


Bullet2::Bullet2()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Special Bullet.cmo");
	m_skinModelRender->SetScale(m_scale);
}


Bullet2::~Bullet2()
{
	DeleteGO(m_skinModelRender);
}

void Bullet2::Update()
{
	timer += GameTime().GetFrameDeltaTime();
	if (timer > Limit)
	{
		Death();
	}
}

void Bullet2::Death()
{
	DeleteGO(this);
}