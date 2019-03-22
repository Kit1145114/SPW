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
	if (S_Rtype2 != nullptr) {
		DeleteGO(S_Rtype2);
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
	PBullet2();
	Pevolution();	//プレイヤーの形態
	Hantei();
	Rotation();
}
//プレイヤーの操作
void Player::Move()
{
	if (DeathCount == false) {
		m_moveSpeed.x = Pad(0).GetLStickXF()* +2.5f;
		m_moveSpeed.z = Pad(0).GetLStickYF()* +2.5f;
		m_position = m_CharaCon.Execute(/*5.0f,*/ m_moveSpeed, 14.0f);
		m_skinModelRender->SetPosition(m_position);
		//if(Pad(0).IsPress(enButtonB))
		//{
		//	Ver = 1;
		//}
	}
}
//プレイヤーの球(第一形態）
void Player::PBullet()
{
	if (Ver == 0) {
		m_timer++;
		p_timer++;
		if (m_timer > 30) {
			m_Short++;
			m_timer = 0;
		}
		if (m_Short > 0) {
			if (Pad(0).IsPress(enButtonRB2/*enButtonA*/) == true) {
				m_bullet = NewGO<Bullet>(0, "PlayerBullet");
				m_bullet->SetPosition(m_position);
				m_bullet->SetMoveSpeedZ(10.0f);
				m_Short--;
				ShortCount = true;
				p_timer = 0;
			}
			else if (Pad(0).IsPress(enButtonRB2/*enButtonA*/) == false) {
				if (p_timer == 99)
				{
					ShortCount = false;
					p_timer = 0;
				}
			}
		}
	}
}
//プレイヤーの球（第二形態）
void Player::PBullet2()
{
	if (Ver == 1)
	{
		S_Rtype2 = NewGO<Senkan_Rtype_2>(0,"Senkan_RType_2");
	}
}
//プレイヤーの進化用
void Player::Pevolution()

{
	if (Ver == 1)
	{
		Ver = 2;
		m_skinModelRender->Init(L"modelData/SenkanType2.cmo");
		//m_player_Rtype2 = NewGO<Player_RType2>(0, "Player_RType2");
		//m_game->m_player = nullptr;
	}
}
//プレイヤーの死亡判定
void Player::Hantei()
{	
	if (m_game->m_enemy != nullptr) {
		CVector3 diff = m_enemy->GetPosition() - m_position;
		if (diff.Length() < 250.0f) {
			Death();
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
//プレイヤーの死亡処理。（今はまだ未使用）
void Player::Death()
{
	m_skinModelRender->Init(L"modelData/Star.cmo");
	DeathCount = true;
}