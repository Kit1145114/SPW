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
	m_game = FindGO<Game>("Game");
	s_kazu = FindGO<SansenKazu>("SansenKazu");
	PadNum = s_kazu->GetKazu();
	switch (PadNum)
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
	m_game = FindGO<Game>("Game");
	Pl_Hantei();
	Move();
	m_skinModelRender->SetPosition(m_position);
}
//エネミーの死亡判定。
void Enemy::Pl_Hantei()
{
	for(int i = 0; i < PadNum; i++)
	if (m_player[i]->GetVer() == 0) {
		if (m_game->GetPBInit() == true/*m_player[i]->GetShortCount() == true && m_player[i]->GetDeathCount() == false*/)
		{
			m_bullet = FindGO<Bullet>("PlayerBullet");
			CVector3 diff = m_bullet->GetPosition() - m_position;
			if (diff.Length() < 200.0f)
			{
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
}
//エネミーの回転処理。
void Enemy::Rotation()
{
	float Rot = atan2(m_moveSpeed.x, m_moveSpeed.z);
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY, Rot);
	m_skinModelRender->SetRotation(qRot);
}