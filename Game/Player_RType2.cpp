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
	m_CharaCon.Init(100.0f, 80.0f, m_position);
	m_game = FindGO<Game>("Game");
	if (m_game->m_enemy != nullptr){
		m_enemy = FindGO<Enemy>("Enemy");
}
	return true;
}

void Player_RType2::Update()
{
	Move();			//プレイヤーの操作
	PBullet();		//プレイヤーの射撃操作	//プレイヤーの形態
	//PHantei();
	Rotation();
}
//プレイヤーの操作
void Player_RType2::Move()
{
	m_moveSpeed.x = Pad(0).GetLStickXF()* +2.5f;
	m_moveSpeed.z = Pad(0).GetLStickYF()* +2.5f;
	m_position = m_CharaCon.Execute(/*5.0f,*/ m_moveSpeed, 14.0f);
	m_skinModelRender->SetPosition(m_position);
}
//プレイヤーの球
void Player_RType2::PBullet()
{
	m_timer++;

	if (m_timer > 30) {
		m_Short++;
		m_timer = 0;
	}
	//球が一発以上
	if (m_Short > 0) {
		//ABUTTONが押されたとき
		if (Pad(0).IsPress(enButtonRB1/*enButtonA*/)) {
			//一つ目
			m_bullet = NewGO<Bullet>(0, "Player_RType2Bullet");
			m_bullet->SetPosition(m_position);
			m_bullet->SetMoveSpeedZ(10.0f,0.0f);
			
			//二つ目
			m_bullet = NewGO<Bullet>(0, "Player_RType2Bullet");
			CVector3 pos = m_position;
			pos.x += 50.0f;
			m_bullet->SetPosition(pos);
			m_bullet->SetMoveSpeedZ(10.0f,0.0f);
			
			//三つ目
			m_bullet = NewGO<Bullet>(0, "Player_RType2Bullet");
			pos.x -= 100.0f;
			m_bullet->SetPosition(pos);
			m_bullet->SetMoveSpeedZ(10.0f,0.0f);
			m_Short--;
			p_timer = 0;
		}
	}
	else if (Pad(0).IsPress(enButtonRB1/*enButtonA*/) == false) {
		p_timer++;
		if (p_timer == 80)
		{
			ShortCount = false;
			p_timer = 0;
		}
	}
}
//プレイヤーの当たり判定
void Player_RType2::PHantei()
{
	CVector3 diff = m_enemy->GetPosition() - m_position;
	if (diff.Length() < 250.0f) {

	}
}
//プレイヤーの回転処理
void Player_RType2::Rotation()
{
	float Rot = atan2(m_moveSpeed.x, m_moveSpeed.z);
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY, Rot);
	m_skinModelRender->SetRotation(qRot);
}

void Player_RType2::Death()
{
	m_skinModelRender->Init(L"modelData/Hako.cmo");
	DeathCount = true;
}