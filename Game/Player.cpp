#include "stdafx.h"
#include "Player.h"
#include "Network/NPad.h"

Player::Player()
{
}

Player::~Player()
{
	DeleteGO(m_skinModelRender);

	//if (S_Rtype2 != nullptr) {
	//	DeleteGO(S_Rtype2);
	//}
	if (d_hako != nullptr)
	{
		DeleteGO(d_hako);
	}
}

bool Player::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Senkan.cmo");
	m_scale = { 3.0f,3.0f,3.0f };
	m_skinModelRender->SetScale(m_scale);
	m_CharaCon.Init(300.0f, 300.0f, m_position);
	m_game = FindGO<Game>("Game");
	//m_enemy = FindGO<Enemy>("Enemy");
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
	PBullet2();
	Pevolution();	//プレイヤーの形態
	Hantei();
	Rotation();
	Respawn();
	S_Hantei();
	PlS_Hantei();
	//HakoHantei();
	B_Hantei();
	//P_Hantei();
	Houdai();
	MutekiTimes();
	HP();
	StarPop();
	memory_position = m_position;
}
//プレイヤーの操作
void Player::Move()
{
	if (DeathCount == false) {
		if (Muteki == false) {
			m_moveSpeed.x = NPad(PadNum).GetLStickXF()* +8.0f;
			m_moveSpeed.z = NPad(PadNum).GetLStickYF()* +8.0f;
			m_position = m_CharaCon.Execute(/*5.0f,*/ m_moveSpeed, 12.0f);
			m_skinModelRender->SetPosition(m_position);
		}
		else if(Muteki == true)
		{
			m_moveSpeed.x = Pad(PadNum).GetLStickXF()* +10.0f;
			m_moveSpeed.z = Pad(PadNum).GetLStickYF()* +10.0f;
			m_position = m_CharaCon.Execute(/*5.0f,*/ m_moveSpeed, 12.0f);
			m_skinModelRender->SetPosition(m_position);
		}
		//デバック用の進化
		//if(NPad(1).IsPress(enButtonB))
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
				if (NPad(PadNum).IsPress(enButtonRB2) == true) {
					m_bullet = NewGO<Bullet>(0, "PlayerBullet");
					m_bullet->SetPB(PadNum);
					//m_game->SetPBInit(true);
					m_bullet->SetPosition(m_position);
					m_bullet->SetPositionXZ(HoukouX, HoukouZ);
					m_bullet->SetMoveSpeedZ(SpeedX, SpeedZ);
					m_Short--;
					ShortCount = true;
					m_game->SetKazu(3);
					p_timer = 0;
				}
				else {
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
	if(DeathCount == false)
		if (Ver == 1)
		{
			m_timer++;  // =GameTime().GetFrameDeltaTime;
			p_timer++;
			if (m_timer > 15) {
				m_Short++;
				m_timer = 0;
			}
			if (m_Short > 0)
			{
				if (NPad(PadNum).IsPress(enButtonRB2) == true) {
					m_bullet = NewGO<Bullet>(0, "PlayerBullet");
					m_bullet->SetPB(PadNum);
					m_bullet->SetPosition(m_position);
					m_bullet->SetPositionXZ(HoukouX, HoukouZ);
					m_bullet->SetMoveSpeedZ(SpeedX, SpeedZ);

					m_bullet = NewGO<Bullet>(0, "PlayerBullet");
					m_bullet->SetPB(PadNum);
					m_bullet->SetPositionXZ(HoukouX, HoukouZ);
					m_bullet->SetPositionX(50.0f);
					m_bullet->SetPosition(m_position);
					m_bullet->SetMoveSpeedZ(SpeedX, SpeedZ);

					m_bullet = NewGO<Bullet>(0, "PlayerBullet");
					m_bullet->SetPB(PadNum);
					m_bullet->SetPositionXZ(HoukouX, HoukouZ);
					m_bullet->SetPositionX(-100.0f);
					m_bullet->SetPosition(m_position);
					m_bullet->SetMoveSpeedZ(SpeedX, SpeedZ);
					m_Short--;

					ShortCount = true;
					m_game->SetKazu(3);
					p_timer = 0;
				}
				else {
					if (p_timer == 98)
					{
						ShortCount = false;
						p_timer = 0;
					}
				}
			}
		}
}
//プレイヤーの進化用
void Player::Pevolution()
{
	if (StarCount == 5 && m_mode == 0)
	{
		m_skinModelRender->Init(L"modelData/SenkanType2.cmo");
		//S_Rtype2 = NewGO<Senkan_Rtype_2>(0,"Senkan_RType_2");
		Ver = 1;
		m_Short = 0;
		m_mode = 1;
	}
}
//プレイヤーのモブ判定
void Player::Hantei()
{
	if (Muteki == false) {
		for (int i = 0; i < s_kazu->GetKazu(); i++) {
			if (m_game->m_enemy != nullptr) {
				CVector3 diff = m_enemy->GetPosition() - m_player[i]->m_position;
				if (diff.Length() < 250.0f) {
					m_player[i]->Death();
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
	Alive = false;
	switch (PadNum)
	{
	case 0:
		Pl1->SetDeath(true);
		break;
	case 1:
		Pl2->SetDeath(true);
		break;
	case 2:
		Pl3->SetDeath(true);
		break;
	case 3:
		Pl4->SetDeath(true);
		break;
	}
	if (CountExplosion == false) {
		CountExplosion = true;
		//エフェクトを作成。
		prefab::CEffect* effect;
		effect = NewGO<prefab::CEffect>(0);
		//エフェクトを再生。
		effect->Play(L"effect/explosion2.efk");
		effect->SetPosition(this->m_position);
	}

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
				m_skinModelRender->SetPosition(m_position);
				m_CharaCon.SetPosition(m_position);
				d_timer = 0;
				DeathCount = false;
				Muteki = true;
				Alive = true;
				CountExplosion = false;
				PlHP = MaxHP;
			}
			else if (Ver == 1)
			{
				m_skinModelRender->Init(L"modelData/SenkanType2.cmo");
				m_skinModelRender->SetPosition(m_position);
				m_CharaCon.SetPosition(m_position);
				d_timer = 0;
				DeathCount = false;
				Muteki = true;
				Alive = true;
				PlHP = MaxHP;
			}
		}
	}
}
//プレイヤーの撃つ方向の設定。
void Player::Houdai()
{
	if (Ver == 0) {
		HoukouX = Pad(PadNum).GetRStickXF() * 75.0f;
		HoukouZ = Pad(PadNum).GetRStickYF() * 75.0f;
		SpeedX = Pad(PadNum).GetRStickXF() * 150.0f;
		SpeedZ = Pad(PadNum).GetRStickYF() * 150.0f;
		if (Pad(PadNum).GetRStickXF() == 0.0 && Pad(PadNum).GetRStickYF() == 0.0)
		{
			HoukouX = 0.0f;
			HoukouZ = 150.0f;
			SpeedX = 0.0f;
			SpeedZ = 15.0f;
		}
	}
	else if (Ver == 1)
	{
		HoukouX = NPad(PadNum).GetRStickXF() * 150.0f;
		HoukouZ = NPad(PadNum).GetRStickYF() * 150.0f;
		SpeedX = NPad(PadNum).GetRStickXF() * 100.0f;
		SpeedZ = NPad(PadNum).GetRStickYF() * 100.0f;
		if (NPad(PadNum).GetRStickXF() == 0.0 && NPad(PadNum).GetRStickYF() == 0.0)
		{
			HoukouX = 0.0f;
			HoukouZ = 150.0f;
			SpeedX = 0.0f;
			SpeedZ = 15.0f;
		}
	}
}
//☆の当たり判定。
void Player::S_Hantei()
{
	if (m_game->GetS_Init() == false)
	{

	}
	else if (m_game->GetS_Init() == true) {
		QueryGOs<Star>("Star", [&](Star* star)->bool{
			CVector3 Kyori = star->GetPosition() - m_position;
			if (Kyori.Length() < 250.0f) {
				StarCount++;
				m_game->SetStarCount(-1);
				star->Death();
			}
			return true;
		});
	}
}
//プレイヤーの落とした☆の当たり判定。
void Player::PlS_Hantei()
{
	if (DeathCount == false) {
		if (m_game->GetPlS_Init() == false)
		{

		}
		else if (m_game->GetPlS_Init() == true)
		{
			QueryGOs<PlayerStar>("PlayerStar", [&](PlayerStar* plstar)->bool {
				CVector3 Len = plstar->GetPosition() - m_position;
				if (Len.Length() < 400.0f)
				{
					StarCount += plstar->GetStarCount();
					m_game->AddPlStarCount(1);
					plstar->Death();
				}
				return true;
			});
		}
	}
}
//プレイヤー同士の球の判定
void Player::B_Hantei()
{
	if (m_game->GetPBInit() == true) {
		if (Muteki == false) {
			QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b) ->bool {
				CVector3 kyori = b->GetPosition() - m_position;
				if (b->GetPB() != PadNum && kyori.Length() < 150.0f)
				{
					b->Death();
					PlHP -= Damage;
				}
				else if (b->GetPB() == PadNum)
				{

				}
				return true;
			});
		}
		
	}
	else
	{

	}
}
//プレイヤー同士の当たり判定（※調整中。）
void Player::P_Hantei()
{
	if (DeathCount == false)
	{
		if (Muteki == false) {
			if (PadNum > 0)
			{
				CVector3 Kyori = m_position - m_position;
				if (Kyori.Length() < 30.0f)
				{
					Death();
				}
			}
		}
		else if (Muteki == true) {

		}
	}
}
//無敵時間の調整。
void Player::MutekiTimes()
{
	if (Muteki == true)
	{
		MutekiTime++;
		if (MutekiTime == 180)
		{
			Muteki = false;
			MutekiTime = 0;
		}
	}
	else
	{

	}
}
//死んだ後のHP調整等。
void Player::HP()
{
	if (PlHP <= 0)
	{
		PlHP = 0;
		Death();
	}
}

void Player::StarPop()
{
	if (Alive == false && Plstar == nullptr)
	{
		if (StarCount > 1) {
			PopStar = StarCount / 2;
			StarCount -= PopStar;
			Plstar = NewGO<PlayerStar>(0, "PlayerStar");
			Plstar->SetPosition(m_position);
			Plstar->SetStarCount(PopStar);
			m_game->AddPlStarCount(1);
			Alive = true;
		}
	}
	else
	{
		PopStar = 0;
	}
}