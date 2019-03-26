#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}

Player::~Player()
{
	DeleteGO(m_skinModelRender);

	if (S_Rtype2 != nullptr) {
		DeleteGO(S_Rtype2);
	}
	if (d_hako != nullptr)
	{
		DeleteGO(d_hako);
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
	Respawn();
	//HakoHantei();
	memory_position = m_position;
}
//プレイヤーの操作
void Player::Move()
{
	if (DeathCount == false) {
		m_moveSpeed.x = Pad(PadNum).GetLStickXF()* +2.5f;
		m_moveSpeed.z = Pad(PadNum).GetLStickYF()* +2.5f;
		m_position = m_CharaCon.Execute(/*5.0f,*/ m_moveSpeed, 14.0f);
		m_skinModelRender->SetPosition(m_position);
		//デバック用の進化
		//if(Pad(0).IsPress(enButtonB))
		//{
		//	Ver = 1;
		//}
	}
}
//プレイヤーの球(第一形態）
void Player::PBullet()
{
		if (DeathCount == false) {
			if (Ver == 0) {
				m_timer++;
				p_timer++;
				if (m_timer > 30) {
					m_Short++;
					m_timer = 0;
				}
				if (m_Short > 0) {
					if (Pad(PadNum).IsPress(enButtonRB2/*enButtonA*/) == true) {
						m_bullet = NewGO<Bullet>(0, "PlayerBullet");
						m_bullet->SetPosition(m_position);
						m_bullet->SetMoveSpeedZ(10.0f);
						m_Short--;
						ShortCount = true;
						p_timer = 0;
					}
					else if (Pad(PadNum).IsPress(enButtonRB2/*enButtonA*/) == false) {
						if (p_timer == 98)
						{
							ShortCount = false;
							p_timer = 0;
						}
					}
				}
			}
		}
	}
//プレイヤーの球（第二形態）
void Player::PBullet2()
{
	if (Ver == 1 && m_mode == 1)
	{
		ShortCount = false;
		m_mode = 0;
	}
	//m_timer++;
	//p_timer++;
	//if (m_timer > 25) {
	//	m_Short++;
	//	m_timer = 0;
	//}
	////球が一発以上
	//if (m_Short > 0) {
	//	//ABUTTONが押されたとき
	//	if (Pad(0).IsPress(enButtonRB2/*enButtonA*/) == true) {
	//		//一つ目
	//		m_bullet = NewGO<Bullet>(0, "Player_RType2Bullet1");
	//		m_bullet->SetPosition(m_position);
	//		m_bullet->SetMoveSpeedZ(15.0f);

	//		//二つ目
	//		m_bullet = NewGO<Bullet>(0, "Player_RType2Bullet2");
	//		CVector3 pos = m_position;
	//		pos.x += 50.0f;
	//		m_bullet->SetPosition(pos);
	//		m_bullet->SetMoveSpeedZ(15.0f);

	//		//三つ目
	//		m_bullet = NewGO<Bullet>(0, "Player_RType2Bullet3");
	//		pos.x -= 100.0f;
	//		m_bullet->SetPosition(pos);
	//		m_bullet->SetMoveSpeedZ(15.0f);

	//		m_Short--;
	//		ShortCount = true;
	//		p_timer = 0;
	//	}
	//}
	//else if (Pad(0).IsPress(enButtonRB2/*enButtonA*/) == false) {
	//	if (p_timer == 98)
	//	{
	//		ShortCount = false;
	//		p_timer = 0;
	//	}
	//}
}
//プレイヤーの進化用
void Player::Pevolution()

{
	if (StarCount==1 && S_Rtype2 == nullptr)
	{
		S_Rtype2 = NewGO<Senkan_Rtype_2>(0, "Senkan_RType_2");
		m_skinModelRender->Init(L"modelData/SenkanType2.cmo");
		Ver = 1;
		m_mode = 1;
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
//プレイヤーの箱との判定
void Player::HakoHantei()
{
	CVector3 Kyori = m_position - d_hako->GetPosition();
	if (Kyori.Length() < 150.0f)
	{
		Ver = 1;
		d_hako->Death();
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
//プレイヤーの死亡処理。
void Player::Death()
{
	m_skinModelRender->Init(L"modelData/Hako.cmo");
	memory_position = m_position;
	ShortCount = false;
	DeathCount = true;
}
//プレイヤーのリスポーン処理。
void Player::Respawn()
{
	if (DeathCount == true)
	{
		d_timer++;
		if (d_timer == 180)
		{
			if (Ver == 0) {
				m_skinModelRender->Init(L"modelData/Senkan.cmo");
				m_position.z = -500.0f;
				m_skinModelRender->SetPosition(m_position);
				m_CharaCon.SetPosition(m_position);
				d_timer = 0;
				DeathCount = false;
			}
			else if (Ver == 2)
			{
				m_skinModelRender->Init(L"modelData/SenkanType2.cmo");
				m_position.x = -500.0f;
				m_skinModelRender->SetPosition(m_position);
				m_CharaCon.SetPosition(m_position);
				d_timer = 0;
				DeathCount = false;
			}
		}
	}
}
//プレイヤーの撃つ方向の設定。
void Player::Houdai()
{
	b_moveSpeed.x = Pad(0).GetLStickXF()* +10.0f;
	b_moveSpeed.z = Pad(0).GetLStickYF()* +10.0f;
}