#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}


bool Player::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_CharaCon.Init(30.0f, 100.0f, m_position);
	return true;
}

void Player::Update()
{
	Move();
}

void Player::Move()
{

	m_position.x += Pad(0).GetLStickXF() * 5.0f;
	m_position.z += Pad(0).GetLStickYF() * 5.0f;

	m_skinModelRender->SetPosition(m_position);
}