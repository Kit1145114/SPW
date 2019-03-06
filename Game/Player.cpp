#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
	DeleteGO(m_skinModelRender);
}


bool Player::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Senkan.cmo");
	m_CharaCon.Init(100.0f, 100.0f, m_position);
	return true;
}

void Player::Update()
{
	Move();
	PBullet();
}

void Player::Move()
{
	m_moveSpeed.x = Pad(0).GetLStickXF()* + 2.5f;
	m_moveSpeed.z = Pad(0).GetLStickYF()* + 2.5f;
	m_position = m_CharaCon.Execute(/*5.0f,*/ m_moveSpeed,14.0f);
	m_skinModelRender->SetPosition(m_position);
}

void Player::PBullet()
{
	m_timer++;

	if ( m_timer > 30) {
		m_Short++;
		m_timer = 0;
	}
	if (m_Short > 0) {
		if (Pad(0).IsPress(enButtonA)) {
			Bullet* bullet = NewGO<Bullet>(0, "PlayerBullet");
			bullet->m_position = m_position;
			bullet->m_position.y = 75.0f;
			bullet->m_position.x -= 10.0f;
			bullet->m_position.z += 75.0f;
			bullet->m_moveSpeed.z = 10.0f;
			m_Short--;
		}
	}
}