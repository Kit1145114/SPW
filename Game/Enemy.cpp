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
	m_skinModelRender->SetPosition(m_position);
	Pl_Hantei();
	//Pl_RHantei();
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
//エネミーの死亡判定。
void Enemy::Pl_RHantei()
{
	//if (m_player->GetVer() == 1) {
		//S_RType2 = FindGO<Senkan_Rtype_2>("Senkan_RType_2");
		//if (S_RType2->GetShortCount() == true)
		//{
		//	m_bullet = FindGO<Bullet>("Player_RType2Bullet1");
		//	CVector3 diff2 = m_bullet->GetPosition() - m_position;
		//	if (diff2.Length() < 150.0f)
		//	{
		//		m_game->m_enemy = nullptr;
		//		Death();
		//	}
		//}
		//if (S_RType2->GetShortCount() == true)
		//{
		//	m_bullet = FindGO<Bullet>("Player_RType2Bullet2");
		//	CVector3 diff3 = m_bullet->GetPosition() - m_position;
		//	if (diff3.Length() < 150.0f)
		//	{
		//		m_game->m_enemy = nullptr;
		//		Death();
		//	}
		//}
		//if (S_RType2->GetShortCount() == true)
		//{
		//	m_bullet = FindGO<Bullet>("Player_RType2Bullet3");
		//	CVector3 diff4 = m_bullet->GetPosition() - m_position;
		//	if (diff4.Length() < 150.0f)
		//	{
		//		m_game->m_enemy = nullptr;
		//		Death();
		//	}
		//}
	//}
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