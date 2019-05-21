#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
	m_position.x = 2000.0f;
}


Enemy::~Enemy()
{
	DeleteGO(m_skinModelRender);
}

bool Enemy::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Enemy.cmo");
	//m_CharaCon.Init(100.0f, 15.0f, m_position);
	scale = { 9.0f,9.0f,9.0f };
	m_skinModelRender->SetScale(scale);
	m_skinModelRender->SetPosition(m_position);
	m_game = Game::GetInstance();
	switch (m_game->GetSansenKazu())
	{
	case 1:
		m_player[0] = FindGO<Player>("Player");
		break;
	case 2:
		m_player[0] = FindGO<Player>("Player");
		m_player[1] = FindGO<Player>("Player1");
		break;
	case 3:
		m_player[0] = FindGO<Player>("Player");
		m_player[1] = FindGO<Player>("Player1");
		m_player[2] = FindGO<Player>("Player2");
		break;
	case 4:
		m_player[0] = FindGO<Player>("Player");
		m_player[1] = FindGO<Player>("Player1");
		m_player[2] = FindGO<Player>("Player2");
		m_player[3] = FindGO<Player>("Player3");
		break;
	}
	return true;
}

void Enemy::Update()
{
	m_player[0] = FindGO<Player>("Player");
	Pl_BulletHantei();
	Move();
	Rotation();
	m_skinModelRender->SetPosition(m_position);
}
//プレイヤーの球との判定。
void Enemy::Pl_BulletHantei()
{
	float BulletHantei = 1200.0f;
	QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b) ->bool {
		CVector3 kyori = b->GetPosition() - m_position;
		if (kyori.Length() < BulletHantei)
		{
			Death();
		}
		return true;
	});
}
//エネミーの削除。
void Enemy::Death()
{
	DeleteGO(this);
}
//エネミーの挙動。
void Enemy::Move()
{
	if (m_position.x < m_player[0]->GetPosition().x)
	{
		m_moveSpeed.x += 50;
	}
	else 
	{
		m_moveSpeed.x -= 50;
	}
	if (m_position.z < m_player[0]->GetPosition().z)
	{
		m_moveSpeed.z += 50;
	}
	else
	{
		m_moveSpeed.z -= 50;
	}
	m_position = m_moveSpeed;
	m_skinModelRender->SetPosition(m_position);
}
//エネミーの回転処理。
void Enemy::Rotation()
{
	float Rot = atan2(m_moveSpeed.x, m_moveSpeed.z);
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY, Rot*100);
	m_skinModelRender->SetRotation(qRot);
	if (m_moveSpeed.x != 0.0f || m_moveSpeed.z != 0.0f)
	{
		m_rotation = qRot;
	}
	else if (m_moveSpeed.x == 0.0f && m_moveSpeed.z == 0.0f)
	{
		m_skinModelRender->SetRotation(m_rotation);
	}
}