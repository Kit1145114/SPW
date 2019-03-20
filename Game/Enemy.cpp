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
	m_player = FindGO<Player>("Player");
	m_game = FindGO<Game>("Game");
	return true;
}

void Enemy::Update()
{
	m_skinModelRender->SetPosition(m_position);
	Hantei();
}
//エネミーの死亡判定。
void Enemy::Hantei()
{
	if (m_player->ShortCount == true)
	{
		m_bullet = FindGO<Bullet>("PlayerBullet");
		CVector3 diff = m_bullet->GetPosition() - m_position;
		if (diff.Length() < 150.0f)
		{
			m_game->m_enemy = nullptr;
			Death();
		}
	}
	//if (m_game->m_player_Rtype2 != nullptr) {
		//m_playerR2 = FindGO<Player_RType2>("Player_Rtype2");
		//if (m_playerR2->ShortCount == true)
		//{
		//	m_bullet = FindGO<Bullet>("Player_RType2Bullet");
		//	CVector3 pr2 = m_bullet->GetPosition() - m_position;
		//	if (pr2.Length() < 150.0f)
		//	{
		//		m_game->m_enemy = nullptr;
		//		DeleteGO(this);
		//	}
		//}
	//}
}

void Enemy::Death()
{
	DeleteGO(this);
}