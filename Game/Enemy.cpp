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
	Pl_Hantei();
	Pl_RHantei();
}
//エネミーの死亡判定。
void Enemy::Pl_Hantei()
{
	if (m_player->GetVer() == 0) {
		if (m_player->GetShortCount() == true && m_player->GetDeathCount() == false)
		{
			m_bullet = FindGO<Bullet>("PlayerBullet");
			CVector3 diff = m_bullet->GetPosition() - m_position;
			if (diff.Length() < 150.0f)
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
	if (m_player->GetVer() == 1) {
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
	if (Kyori.Length() < 200.0f)
	{

	}
}
//エネミーの回転処理。
void Enemy::Rotation()
{
	float Rot = atan2(m_moveSpeed.x, m_moveSpeed.z);
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY, Rot);
	m_skinModelRender->SetRotation(qRot);
}