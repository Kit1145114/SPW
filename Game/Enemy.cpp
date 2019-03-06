#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
	DeleteGO(m_skinModelRender);
}

bool Enemy::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Enemy.cmo");
	m_CharaCon.Init(30.0f, 100.0f, m_position);
	return true;
}

void Enemy::Update()
{
	m_position.z += 100.0f;
	m_skinModelRender->SetPosition(m_position);
}
