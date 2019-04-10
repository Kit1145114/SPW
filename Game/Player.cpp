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
	s_kazu = FindGO<SansenKazu>("SansenKazu");
	switch (s_kazu->GetKazu())
	{
	case 1:
		Pl1 = FindGO<Draw_1P>("1P");
		break;
	case 2:
		Pl1 = FindGO<Draw_1P>("1P");
		Pl2 = FindGO<Draw_2P>("2P");
		break;
	case 3:
		Pl1 = FindGO<Draw_1P>("1P");
		Pl2 = FindGO<Draw_2P>("2P");
		Pl3 = FindGO<Draw_3P>("3P");
		break;
	case 4:
		Pl1 = FindGO<Draw_1P>("1P");
		Pl2 = FindGO<Draw_2P>("2P");
		Pl3 = FindGO<Draw_3P>("3P");
		Pl4 = FindGO<Draw_4P>("4P");
		break;
	}
	//Pl1 = FindGO<Draw_1P>("1P");
	//Pl2 = FindGO<Draw_2P>("2P");
	//Pl3 = FindGO<Draw_3P>("3P");
	//Pl4 = FindGO<Draw_4P>("4P");
	PadMaxKazu = s_kazu->GetKazu();
	switch (PadMaxKazu)
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

void Player::Update()
{
	Move();			//プレイヤーの操作
	PBullet();		//プレイヤーの射撃操作
//	PBullet2();
	Pevolution();	//プレイヤーの形態
	Hantei();
	Rotation();
	Respawn();
	//S_Hantei();
	//HakoHantei();
	B_Hantei();
	//P_Hantei();
	Houdai();
	memory_position = m_position;
}
//プレイヤーの操作
void Player::Move()
{
	if (DeathCount == false) {
		m_moveSpeed.x = Pad(PadNum).GetLStickXF()* +2.0f;
		m_moveSpeed.z = Pad(PadNum).GetLStickYF()* +2.0f;
		m_position = m_CharaCon.Execute(/*5.0f,*/ m_moveSpeed, 12.0f);
		m_skinModelRender->SetPosition(m_position);
		//デバック用の進化
		//if(Pad(1).IsPress(enButtonB))
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
			m_timer++;  // =GameTime().GetFrameDeltaTime;
			p_timer++;
			if (m_timer > 30) {
				m_Short++;
				m_timer = 0;
			}
			if (m_Short > 0) {
				if (Pad(PadNum).IsPress(enButtonRB2) == true) {
					m_bullet = NewGO<Bullet>(0, "PlayerBullet");
					//m_game->SetPBInit(true);
					m_bullet->SetPosition(m_position);
					m_bullet->SetPositionZ(HoukouX, HoukouZ);
					m_bullet->SetMoveSpeedZ(SpeedX, SpeedZ);
					m_Short--;
					ShortCount = true;
					m_game->SetKazu(1);
					p_timer = 0;
				}
				else if (Pad(PadNum).IsPress(enButtonRB2) == false) {
					if (p_timer == 98)
					{
						ShortCount = false;
						//m_game->SetPBInit(false);
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
	for (int i = 0; i < s_kazu->GetKazu(); i++) {
		if (m_game->m_enemy != nullptr) {
			CVector3 diff = m_enemy->GetPosition() - m_player[i]->m_position;
			if (diff.Length() < 250.0f) {
				m_player[i]->Death();
				/*m_game->SetDeathPl(i, true)*/;
				if (i == 0)
				{
					Pl1->SetDeath(true);
				}
				else if (i == 1)
				{
					Pl2->SetDeath(true);
				}
				else if (i == 2)
				{
					Pl3->SetDeath(true);
				}
				else if (i == 3)
				{
					Pl4->SetDeath(true);
				}
			}
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
	//Pl1->SetDeath(true);
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
			else if (Ver == 1)
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
	//b_moveSpeed.x = Pad(0).GetLStickXF()* +10.0f;
	//b_moveSpeed.z = Pad(0).GetLStickYF()* +10.0f;
	if (Pad(PadNum).GetRStickXF() == 0.0, Pad(PadNum).GetRStickYF() == 0.0)
	{
		HoukouX = 0.0f;
		HoukouZ = 150.0f;
		SpeedX = 0.0f;
		SpeedZ = 15.0f;
	}
	else if (Pad(PadNum).GetRStickXF() > 0.2)
	{
		HoukouX = 150.0f;
		HoukouZ = 0.0f;
		SpeedX = 15.0f;
		SpeedZ = 0.0f;
	}
	else if (Pad(PadNum).GetRStickXF() <= -0.2)
	{
		HoukouX = -150.0f;
		HoukouZ = 0.0f;
		SpeedX = -15.0f;
		SpeedZ = 0.0f;
	}
	else if (Pad(PadNum).GetRStickYF() >= 0.2)
	{
		HoukouX = 0.0f;
		HoukouZ = 150.0f;
		SpeedX = 0.0f;
		SpeedZ = 15.0f;
	}
	else if (Pad(PadNum).GetRStickYF() <= -0.2)
	{
		HoukouX = 0.0f;
		HoukouZ = -150.0f;
		SpeedX = 0.0f;
		SpeedZ = -15.0f;
	}
}
//未定
void Player::S_Hantei()
{
	for (int i = 0; i < s_kazu->GetKazu(); i++) {
		if (m_game->GetS_Init() == false)
		{
		}
		else if (m_game->GetS_Init() == true) {
			m_star = FindGO<Star>("Star");
			CVector3 diff = m_star->GetPosition() - m_player[i]->GetPosition();
			if (diff.Length() < 250.0f) {
				StarCount++;
				m_game->SetStarCount(-1);
				m_star->Death();
			}
		}
	}
}
//プレイヤー同士の球の判定
void Player::B_Hantei()
{
	for (int i = 0; i < s_kazu->GetKazu(); i++) {
		if (DeathCount == false)
		{
			if (PadNum > 0) {
				if (m_game->GetPBInit() == true) {
					m_bullet = FindGO<Bullet>("PlayerBullet");
					CVector3 kyori = m_bullet->GetPosition() - m_player[i]->m_position;
					if (kyori.Length() < 150.0f)
					{
						m_player[i]->Death();
						/*m_game->SetDeathPl(i, true);*/
						if (i == 0)
						{
							Pl1->SetDeath(true);
						}
						else if (i == 1)
						{
							Pl2->SetDeath(true);
						}
						else if (i == 2)
						{
							Pl3->SetDeath(true);
						}
						else if (i == 3)
						{
							Pl4->SetDeath(true);
						}
					}
				}
			}
			else if (m_game->GetPBInit() == false)
			{

			}
		}
		else if (DeathCount == true)
		{

		}
	}
}
//プレイヤー同士の当たり判定（※調整中。）
void Player::P_Hantei()
{
	if (DeathCount == false)
	{
		if (PadNum > 0)
		{
			CVector3 Kyori = m_position - m_position;
			if (Kyori.Length() < 30.0f)
			{
				Death();
			}
		}
	}
}