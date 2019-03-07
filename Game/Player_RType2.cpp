#include "stdafx.h"
#include "Player_RType2.h"


Player_RType2::Player_RType2()
{
}


Player_RType2::~Player_RType2()
{
	DeleteGO(m_skinModelRender);
}

bool Player_RType2::Start()
{
		m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
		m_skinModelRender->Init(L"modelData/SenkanType2.cmo");
		m_CharaCon.Init(100.0f, 100.0f, m_position);
	return true;
}

void Player_RType2::Update()
{
	Move();			//プレイヤーの操作
	PBullet();		//プレイヤーの射撃操作	//プレイヤーの形態
}

void Player_RType2::Move()
{
	m_moveSpeed.x = Pad(0).GetLStickXF()* +2.5f;
	m_moveSpeed.z = Pad(0).GetLStickYF()* +2.5f;
	m_position = m_CharaCon.Execute(/*5.0f,*/ m_moveSpeed, 14.0f);
	m_skinModelRender->SetPosition(m_position);
}

void Player_RType2::PBullet()
{
	m_timer++;

	if (m_timer > 30) {
		m_Short++;
		m_timer = 0;
	}
	if (m_Short > 0) {
		if (Pad(0).IsPress(enButtonA)) {
			m_bullet = NewGO<Bullet>(0, "Player_RType2Bullet");
			m_bullet->m_position = m_position;
			m_bullet->m_position.y = 75.0f;
			m_bullet->m_position.x -= 10.0f;
			m_bullet->m_position.z += 75.0f;
			m_bullet->m_moveSpeed.z = 10.0f;

			m_bullet = NewGO<Bullet>(0, "Player_RType2Bullet2");
			m_bullet->m_position = m_position;
			m_bullet->m_position.y = 75.0f;
			m_bullet->m_position.x += 40.0f;
			m_bullet->m_position.z += 75.0f;
			m_bullet->m_moveSpeed.z = 10.0f;

			m_bullet = NewGO<Bullet>(0, "Player_RType2Bullet3");
			m_bullet->m_position = m_position;
			m_bullet->m_position.y = 75.0f;
			m_bullet->m_position.x -= 60.0f;
			m_bullet->m_position.z += 75.0f;
			m_bullet->m_moveSpeed.z = 10.0f;
			m_Short--;
		}
	}
}
