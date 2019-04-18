#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
	m_position.z = 300.0f;
}


Enemy::~Enemy()
{
	DeleteGO(m_skinModelRender);
}

bool Enemy::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Enemy.cmo");
	m_CharaCon.Init(100.0f, 15.0f, m_position);
	
	return true;
}

void Enemy::Update()
{
	m_player = FindGO<Player>("Player");
	m_game = FindGO<Game>("Game");
	Pl_Hantei();
	Move();
	m_skinModelRender->SetPosition(m_position);
}
//エネミーの死亡判定。
void Enemy::Pl_Hantei()
{
	if (m_player->GetVer() == 0) {
		if (m_player->GetShortCount() == true && m_player->GetDeathCount() == false)
		{
			m_bullet = FindGO<Bullet>("PlayerBullet");
			CVector3 diff = m_bullet->GetPosition() - m_position;
			if (diff.Length() < 200.0f)
			{
				//m_star = NewGO<Star>(0, "Star");
				//m_star->Pop(m_position);
				m_game->m_enemy = nullptr;
				Death();
			}
		}
	}
}
//エネミーの削除。
void Enemy::Death()
{
	DeleteGO(this);
}
//エネミーの挙動。
void Enemy::Move()
{
	CVector3 Kyori = m_player->GetPosition() - m_position;
	if (Kyori.Length() < 1000.0f)
	{
		m_moveSpeed += Kyori;
	}
	m_position += m_moveSpeed;
}
//エネミーの回転処理。
void Enemy::Rotation()
{
	float Rot = atan2(m_moveSpeed.x, m_moveSpeed.z);
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY, Rot);
	m_skinModelRender->SetRotation(qRot);
}