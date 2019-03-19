#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
	DeleteGO(m_skinModelRender);
	if (m_player_Rtype2 != nullptr) {
		DeleteGO(m_player_Rtype2);
	}
}

bool Player::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Senkan.cmo");
	m_CharaCon.Init(100.0f, 100.0f, m_position);
	m_game = FindGO<Game>("Game");
	m_enemy = FindGO<Enemy>("Enemy");
	return true;
}

void Player::Update()
{
	Move();			//プレイヤーの操作
	PBullet();		//プレイヤーの射撃操作
	Pevolution();	//プレイヤーの形態
	Hantei();
	Rotation();
}
//プレイヤーの操作
void Player::Move()
{
	m_moveSpeed.x = Pad(0).GetLStickXF()* + 2.5f;
	m_moveSpeed.z = Pad(0).GetLStickYF()* + 2.5f;
	m_position = m_CharaCon.Execute(/*5.0f,*/ m_moveSpeed,14.0f);
	m_skinModelRender->SetPosition(m_position);
}
//プレイヤーの球
void Player::PBullet()
{
	m_timer++;
	if ( m_timer > 30) {
		m_Short++;
		m_timer = 0;
	}
	if (m_Short > 0) {
		if (Pad(0).IsPress(/*enButtonRB1*/enButtonA) == true) {
			m_bullet = NewGO<Bullet>(0, "PlayerBullet");
			m_bullet->SetPosition(m_position);
			m_bullet->SetMoveSpeed(10.0f);
			
			m_Short--;
			ShortCount = 1;
			p_timer = 0;
		}
		else if (Pad(0).IsPress(enButtonA) == false) {
			p_timer++;
			if (p_timer == 90)
			{
				ShortCount = 0;
				p_timer = 0;
			}
		}
	}
}
//プレイヤーの進化用
void Player::Pevolution()
{
	if (Pad(0).IsTrigger(enButtonB) && Ver == 0)
	{
		Ver = 1;
		m_game->Pver = 1;
		//m_game->m_player = nullptr;
		//DeleteGO(this);
	}
	memory_position = m_position;
}
//プレイヤーの死亡判定
void Player::Hantei()
{	
	if (m_game->m_enemy != nullptr) {
		CVector3 diff = m_enemy->GetPosition() - m_position;
		if (diff.Length() < 250.0f) {
			m_game->GameMode = 1;
		}
	}
}
//プレイヤーの回転処理。
void Player::Rotation()
{
	float Rot = atan2(m_moveSpeed.x, m_moveSpeed.z);
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY, Rot);
	m_skinModelRender->SetRotation(qRot);
}

