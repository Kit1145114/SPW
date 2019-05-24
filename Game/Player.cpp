#include "stdafx.h"
#include "Player.h"
#include "Network/NPad.h"
#include "Sinka_Bar.h"

Player::Player()
{
	draw_Pl = NewGO<Draw_Player>(0);
	draw_S = NewGO<Draw_Skazu>(0);
	r_ring = NewGO<RadarRing>(0);
	//bar = NewGO<Sinka_Bar>(0);
}

void Player::OnDestroy()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(draw_Pl);
	DeleteGO(draw_S);
	DeleteGO(r_ring);
}

bool Player::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Senkan.cmo");
	m_scale = { 9.6f,9.6f,9.6f };
	m_skinModelRender->SetScale(m_scale);
	//m_CharaCon.Init(800.0f, 300.0f, m_position);
	m_game = Game::GetInstance();
	camera = FindGO<Camera>("Camera");
	switch (m_game->GetSansenKazu())
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
	Upper();
	Move();			//プレイヤーの操作
	PBullet();		//プレイヤーの射撃操作
	PBullet2();
	PBullet3();
	Pevolution();	//プレイヤーの形態
	//Hantei();
	Rotation();
	Respawn();
	S_Hantei();
	//PlS_Hantei();
	B_Hantei();
	Houdai();
	MutekiTimes();
	HP();
	StarPos();
	//Playerwarp();
	memory_position = m_position;
	draw_S->SetKazu(StarCount);
	draw_S->SetBulletKazu(m_Short);
	//bar->AddStarCount(StarCount);
}
//プレイヤーの操作
void Player::Move()
{
	if (DeathCount == false) {
		if (Muteki == false) {
			if (Ver == 0) {
				m_moveSpeed.x = NPad(PadNum).GetLStickXF()* +SyokiSpped;
				m_moveSpeed.z = NPad(PadNum).GetLStickYF()* +SyokiSpped;
				m_position += (m_moveSpeed*12.0f);
				m_skinModelRender->SetPosition(m_position);
			}
			else if (Ver == 1)
			{
				m_moveSpeed.x = NPad(PadNum).GetLStickXF()* +(SyokiSpped-0.75f);
				m_moveSpeed.z = NPad(PadNum).GetLStickYF()* +(SyokiSpped - 0.75f);
				m_position += (m_moveSpeed*12.0f);
				m_skinModelRender->SetPosition(m_position);
			}
			else if (Ver == 2) {
				m_moveSpeed.x = NPad(PadNum).GetLStickXF()* (SyokiSpped - 1.5f);
				m_moveSpeed.z = NPad(PadNum).GetLStickYF()* (SyokiSpped - 1.5f);
				m_position += (m_moveSpeed*12.0f);
				m_skinModelRender->SetPosition(m_position);
			}
				if (m_moveSpeed.x != 0.0f || m_moveSpeed.z != 0.0f) {
				memoryHX = m_moveSpeed.x;
				memoryHZ = m_moveSpeed.z;
				memorySX = m_moveSpeed.x;
				memorySZ = m_moveSpeed.z;
			}
			else if (NPad(PadNum).GetLStickXF() == 0.0 && NPad(PadNum).GetLStickYF() == 0.0
					&& NPad(PadNum).GetRStickXF() == 0.0 && NPad(PadNum).GetRStickYF() == 0.0) {
				HoukouX = memoryHX * 10.0f;
				HoukouZ = memoryHZ * 10.0f;
				SpeedX = memorySX  * 10.0f;
				SpeedZ = memorySZ  * 10.0f;
			}
		}
		else if (Muteki == true)
		{
			m_moveSpeed.x = NPad(PadNum).GetLStickXF()* +13.0f;
			m_moveSpeed.z = NPad(PadNum).GetLStickYF()* +13.0f;
			m_position += (m_moveSpeed*12.0f);
			m_skinModelRender->SetPosition(m_position);
		}
		//これを変更したら、Assets/shader/model.fxのPSMainBGも変更する。
		const float xLimit = 45302.23f;
		const float zLimit = 25041.139f;
		if (m_position.x > xLimit) {
			m_position.x = xLimit;
		} else if (m_position.x < -xLimit) {
			m_position.x = -xLimit;
		}
		if (m_position.z > zLimit) {
			m_position.z = zLimit;
		} else if (m_position.z < -zLimit) {
			m_position.z = -zLimit;
		}
		m_CharaCon.SetPosition(m_position);
	}
}
//プレイヤーの球(第一形態）
void Player::PBullet()
{
	if (Ver == 0) {
		m_timer++;  // =GameTime().GetFrameDeltaTime;
		p_timer++;
		if (m_timer > SeiseiVer_1) {
			if (m_Short < MaxSeiseiVer_1) {
				m_Short++;
				m_timer = Timer0;
			}
			else
			{
				m_Short = MaxSeiseiVer_1;
				m_timer = Timer0;
			}
		}
		if (Ver == 0) {
			if (DeathCount == false) {
				if (m_Short > 0) {
					if (NPad(PadNum).IsPress(enButtonRB2) == true) {
						m_bullet = NewGO<Bullet>(0, "PlayerBullet");
						m_bullet->SetPBnum(PadNum);
						m_bullet->SetPosition(m_position);
						m_bullet->SetPositionXZ(HoukouX, HoukouZ);
						//プレイヤーの速度の単位をm/frameに変更する。
						m_bullet->SetMoveSpeedZ(SpeedX + GetmoveSpeedFrame().x, SpeedZ + GetmoveSpeedFrame().z);
						m_Short--;
						Sound(1);//効果音
						ShortCount = true;
						m_game->SetKazu(1);
						p_timer = Timer0;
					}
					else {
						if (p_timer == 98)
						{
							ShortCount = false;
							p_timer = Timer0;
						}
					}
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
		m_timer++;  // =GameTime().GetFrameDeltaTime;
		p_timer++;
		if (m_timer > SeiseiVer_2) {
			if (m_Short < MaxSeiseiVer_2) {
				m_Short++;
				m_timer = Timer0;
			}
			else {
				m_Short = MaxSeiseiVer_2;
				m_timer = Timer0;
			}
		}
		if(Ver == 1){
			if (DeathCount == false)
				if (m_Short > 0)
				{
					if (NPad(PadNum).IsPress(enButtonRB2) == true) {
						m_bullet = NewGO<Bullet>(0, "PlayerBullet");
						m_bullet->SetPBnum(PadNum);
						m_bullet->SetPosition(m_position);
						m_bullet->SetPositionXZ(HoukouX, HoukouZ);
						m_bullet->SetMoveSpeedZ(SpeedX + GetmoveSpeedFrame().x, SpeedZ + GetmoveSpeedFrame().z);

						m_bullet = NewGO<Bullet>(0, "PlayerBullet");
						m_bullet->SetPBnum(PadNum);
						m_bullet->SetPositionXZ(HoukouX, HoukouZ);
						m_bullet->SetPositionX(50.0f);
						m_bullet->SetPosition(m_position);
						m_bullet->SetMoveSpeedZ(SpeedX + GetmoveSpeedFrame().x, SpeedZ + GetmoveSpeedFrame().z);

						m_bullet = NewGO<Bullet>(0, "PlayerBullet");
						m_bullet->SetPBnum(PadNum);
						m_bullet->SetPositionXZ(HoukouX, HoukouZ);
						m_bullet->SetPositionX(-100.0f);
						m_bullet->SetPosition(m_position);
						m_bullet->SetMoveSpeedZ(SpeedX + GetmoveSpeedFrame().x, SpeedZ + GetmoveSpeedFrame().z);
						m_Short--;
						Sound(1);//効果音
						ShortCount = true;
						m_game->SetKazu(3);
						p_timer = Timer0;
					}
					else {
						if (p_timer == 98)
						{
							ShortCount = false;
							p_timer = Timer0;
						}
					}
				}
		}
	}
}
//プレイヤーの球（最終形態）
void Player::PBullet3()
{
	if (Ver == 2)
	{
		m_timer++;  // =GameTime().GetFrameDeltaTime;
		p_timer++;
		if (m_timer > SeiseiVer_3) {
			if (m_Short < MaxSeiseiVer_3) {
				m_Short++;
				m_timer = Timer0;
			}
			else
			{
				m_Short = MaxSeiseiVer_3;
				m_timer = Timer0;
			}
		}
		if(Ver == 2){
			if (DeathCount == false)
				if (m_Short > 0)
				{
					if (NPad(PadNum).IsPress(enButtonRB2) == true) {
						m_bullet = NewGO<Bullet>(0, "PlayerBullet");
						m_bullet->SetPBnum(PadNum);
						m_bullet->SetPosition(m_position);
						m_bullet->SetPositionXZ(HoukouX, HoukouZ);
						m_bullet->SetMoveSpeedZ(SpeedX + GetmoveSpeedFrame().x, SpeedZ + GetmoveSpeedFrame().z);

						m_bullet = NewGO<Bullet>(0, "PlayerBullet");
						m_bullet->SetPBnum(PadNum);
						m_bullet->SetPositionXZ(HoukouX, HoukouZ);
						m_bullet->SetPositionX(50.0f);
						m_bullet->SetPosition(m_position);
						m_bullet->SetMoveSpeedZ(SpeedX + GetmoveSpeedFrame().x, SpeedZ + GetmoveSpeedFrame().z);

						m_bullet = NewGO<Bullet>(0, "PlayerBullet");
						m_bullet->SetPBnum(PadNum);
						m_bullet->SetPositionXZ(HoukouX, HoukouZ);
						m_bullet->SetPositionX(-100.0f);
						m_bullet->SetPosition(m_position);
						m_bullet->SetMoveSpeedZ(SpeedX + GetmoveSpeedFrame().x, SpeedZ + GetmoveSpeedFrame().z);

						m_Short--;
						Sound(1);//効果音
						ShortCount = true;
						m_game->SetKazu(3);
						p_timer = Timer0;
					}
					else {
						if (p_timer == 98)
						{
							ShortCount = false;
							p_timer = Timer0;
						}
					}
				}
		}
	}
}
//プレイヤーの進化用
void Player::Pevolution()
{
	if (StarCount >= 5 && m_mode == 0 && StarCount <= 9 && m_mode == 0)
	{
		m_skinModelRender->Init(L"modelData/SenkanType2.cmo");
		m_scale = { 9.0f,9.0f,9.0f };
		m_skinModelRender->SetScale(m_scale);
		camera->SetPos(7000.0f);
		prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
		effect->Play(L"effect/explosion1.efk");
		effect->SetPosition(m_position);
		Ver = 1;
		m_Short = 0;
		m_mode = 1;
		Sound(2);//効果音
	}
	if (StarCount >= 10 && m_mode == 1|| StarCount >= 10 && Ver == 0)
	{
		m_skinModelRender->Init(L"modelData/SenkanType3.cmo");
		m_scale = { 10.0f,10.0f,10.0f };
		m_skinModelRender->SetScale(m_scale);
		camera->SetPos(9000.0f);
		Ver = 2;
		m_Short = 0;
		m_mode = 2;
		Sound(2);//効果音
	}
}
//プレイヤーのモブ判定
//void Player::Hantei()
//{
//	if (Muteki == false) {
//		if (Game::GetInstance()->m_enemy != nullptr) {
//			CVector3 diff = Game::GetInstance()->GetPosition() - m_position;
//			if (diff.Length() < 250.0f) {
//				Death();
//				draw_Pl->SetDeath(true);
//			}
//		}
//	}
//}
//プレイヤーの回転処理。
void Player::Rotation()
{
	float Rot = atan2(m_moveSpeed.x, m_moveSpeed.z);
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY, Rot);
	m_skinModelRender->SetRotation(qRot);
	if (m_moveSpeed.x != 0.0f || m_moveSpeed.z != 0.0f)
	{
		m_rotation = qRot;
	}
	else if (m_moveSpeed.x == 0.0f && m_moveSpeed.z == 0.0f)
	{
		m_skinModelRender->SetRotation(m_rotation);
	}
}
//プレイヤーの死亡処理。
void Player::Death()
{
	//m_skinModelRender->Init(L"modelData/PlayerStar.cmo");
	m_skinModelRender->SetActiveFlag(false);
	memory_position = m_position;
	ShortCount = false;
	DeathCount = true;
	Alive = false;
	Muteki = true;
	draw_Pl->SetDeath(true);
	if (CountExplosion == false) {
		CountExplosion = true;
		////エフェクトを作成。
		//prefab::CEffect* effect;
		//effect = NewGO<prefab::CEffect>(0);
		////エフェクトを再生。
		//effect->Play(L"effect/explosion2.efk");
		//effect->SetPosition(this->m_position);
		//効果音
		Sound(0);
	}

}
//プレイヤーのリスポーン処理。
void Player::Respawn()
{
	m_skinModelRender->SetActiveFlag(true);
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
				//Muteki = true;
				CountExplosion = false;
				PlHP = MaxHP;
				if (StarCount > 1 && Alive == false)
				{
					StarPop();
				}
				else if(StarCount < 1 && Alive == false)
				{
					Alive = true;
				}
			}
			else if (Ver == 1)
			{
				m_skinModelRender->Init(L"modelData/SenkanType2.cmo");
				m_skinModelRender->SetPosition(m_position);
				m_CharaCon.SetPosition(m_position);
				d_timer = 0;
				DeathCount = false;
				//Muteki = true;
				PlHP = MaxHP;
				if (StarCount > 1 && Alive == false)
				{
					StarPop();
				}
				else if (StarCount < 1 && Alive == false)
				{
					Alive = true;
				}
			}
			else if (Ver == 2)
			{
				m_skinModelRender->Init(L"modelData/SenkanType3.cmo");
				m_skinModelRender->SetPosition(m_position);
				m_CharaCon.SetPosition(m_position);
				d_timer = 0;
				DeathCount = false;
				//Muteki = true;
				PlHP = MaxHP;
				if (StarCount > 1 && Alive == false)
				{
					StarPop();
				}
				else if (StarCount < 1 && Alive == false)
				{
					Alive = true;
				}
			}
		}
	}
}
//プレイヤーの撃つ方向の設定。
void Player::Houdai()
{
	if (Ver == 0) {
		HoukouX = NPad(PadNum).GetRStickXF() * 75.0f;
		HoukouZ = NPad(PadNum).GetRStickYF() * 75.0f;
		SpeedX = NPad(PadNum).GetRStickXF() * 50.0f;
		SpeedZ = NPad(PadNum).GetRStickYF() * 50.0f;
	}
	else if (Ver == 1)
	{
		HoukouX = NPad(PadNum).GetRStickXF() * 150.0f;
		HoukouZ = NPad(PadNum).GetRStickYF() * 150.0f;
		SpeedX = NPad(PadNum).GetRStickXF() * 100.0f;
		SpeedZ = NPad(PadNum).GetRStickYF() * 100.0f;
		if (NPad(PadNum).GetRStickXF() == 0.0 && NPad(PadNum).GetRStickYF() == 0.0)
		{
			HoukouX = memoryHX;
			HoukouZ = memoryHZ;
			SpeedX = memorySX;
			SpeedZ = memorySZ;
		}
	}
	else if (Ver == 2)
	{
		HoukouX = NPad(PadNum).GetRStickXF() * 150.0f;
		HoukouZ = NPad(PadNum).GetRStickYF() * 150.0f;
		SpeedX = NPad(PadNum).GetRStickXF() * 200.0f;
		SpeedZ = NPad(PadNum).GetRStickYF() * 200.0f;
		if (NPad(PadNum).GetRStickXF() == 0.0 && NPad(PadNum).GetRStickYF() == 0.0)
		{
			HoukouX = memoryHX;
			HoukouZ = memoryHZ;
			SpeedX = memorySX;
			SpeedZ = memorySZ;
		}
	}
}
//☆の当たり判定。
void Player::S_Hantei()
{
	QueryGOs<Star>("Star", [&](Star* star)->bool {
		CVector3 Kyori = star->GetPosition() - m_position;
		if (Kyori.Length() < StarHantei) {
			StarCount++;
			//draw_S->AddKazu(1);
			m_game->SetStarCount(-1);
			star->Death();
			if (StarCount > 20)
			{
				MaxSeiseiVer_3++;
			}
		}
		return true;
	});
}
//プレイヤーの落とした☆の当たり判定。
//void Player::PlS_Hantei()
//{
//	if (DeathCount == false) {
//			QueryGOs<PlayerStar>("PlayerStar", [&](PlayerStar* plstar)->bool {
//				CVector3 Len = plstar->GetPosition() - m_position;
//				if (Len.Length() < StarHantei)
//				{
//					StarCount += plstar->GetStarCount();
//					draw_S->SetKazu(StarCount);
//					Game::GetInstance()->AddPlStarCount(-1);
//					plstar->Death();
//				}
//				return true;
//			});
//		}
//}
//プレイヤー同士の球の判定
void Player::B_Hantei()
{
	if (Muteki == false) {
		QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b) ->bool {
			CVector3 kyori = b->GetPosition() - m_position;
			if (b->GetPB() != PadNum && kyori.Length() < BulletHantei)
			{
				PlHP -= Damage;
				b->Death();
				if (b->GetPB() == 0 && DeathCount == false)
				{
					LABulletNum = 0;
				}
				else if (b->GetPB() == 1 && DeathCount == false)
				{
					LABulletNum = 1;
				}
				else if (b->GetPB() == 2 && DeathCount == false)
				{
					LABulletNum = 2;
				}
				else if (b->GetPB() == 3 && DeathCount == false)
				{
					LABulletNum = 3;
				}
				//else if (b->GetPB() == PadNum && DeathCount == false)
				//{
				//	LABulletNum = 10;
				//}
			}
				else if (b->GetPB() == PadNum || DeathCount == true)
				{

				}
			return true;
		});		
	}
	else
	{

	}
}
//無敵時間の調整。キングクリムゾンッッッッ！！！
void Player::MutekiTimes()
{
	if (Muteki == true)
	{
		MutekiTime++;
		
		const int blinkInterval = 3;//点滅の間隔
		/*blinkIntervalが2の場合

		MutekiTime  　　　　　0  1  2  3  4  5  6  7  8  9  10 11 12 13
		MutekiTime / 2  　　　0  0  1  1  2  2  3  3  4  4  5  5  6  6
		(MutekiTime / 2) % 2  0  0  1  1  0  0  1  1  0  0  1  1  0  0

		3の場合

		MutekiTime  　　　　　0  1  2  3  4  5  6  7  8  9  10 11 12 13
		MutekiTime / 3  　　　0  0  0  1  1  1  2  2  2  3  3  3  4  4
		(MutekiTime / 3) % 2  0  0  0  1  1  1  0  0  0  1  1  1  0  0
		*/

		if ((MutekiTime / blinkInterval) % 2 == 0) {
			m_skinModelRender->SetActiveFlag(false);
		} else {
			m_skinModelRender->SetActiveFlag(true);
		}

		if (MutekiTime >= 360) {
			m_skinModelRender->SetActiveFlag(true);
			Muteki = false;
			MutekiTime = 0;
		}

		/*if (MutekiTime >= 180)
		{
			m_skinModelRender->SetActiveFlag(false);
		}
		if (MutekiTime >= 210 && MutekiTime <= 240)
		{
			m_skinModelRender->SetActiveFlag(true);
		}
		if (MutekiTime >= 241 && MutekiTime <= 270)
		{
			m_skinModelRender->SetActiveFlag(false);
		}
		if (MutekiTime >= 271 && MutekiTime <= 360)
		{
			m_skinModelRender->SetActiveFlag(true);
			Muteki = false;
			MutekiTime = 0;
		}*/
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
//プレイヤーの持つ☆を落とす。
void Player::StarPop()
{
	if (LABulletNum == PadNum)
	{
	PopStar = StarCount / 2;
	StarCount -= PopStar;
	Alive = true;
	Sound(3);
	LABulletNum = syoki;
	}
	else if (LABulletNum == 0)//1P
	{
		PopStar = StarCount / 2;
		StarCount -= PopStar;
		Plstar = NewGO<PlayerStar>(0, "PlayerStar");
		Plstar->Pop(PadNum, LABulletNum);//プレイヤーからプレイヤーへ。
		m_player[LABulletNum]->SetStarCount(PopStar);
		Sound(3);
		Alive = true;
		LABulletNum = syoki;
	}
	else if (LABulletNum == 1)//2P
	{
		PopStar = StarCount / 2;
		StarCount -= PopStar;
		m_player[LABulletNum]->SetStarCount(PopStar);
		Plstar = NewGO<PlayerStar>(0, "PlayerStar");
		Plstar->Pop(PadNum, LABulletNum);//プレイヤーからプレイヤーへ。
		Alive = true;
		Sound(3);
		LABulletNum = syoki;
	}
	else if (LABulletNum == 2)//3P
	{
		PopStar = StarCount / 2;
		StarCount -= PopStar;
		m_player[LABulletNum]->SetStarCount(PopStar);
		Plstar = NewGO<PlayerStar>(0, "PlayerStar");
		Plstar->Pop(PadNum, LABulletNum);//プレイヤーからプレイヤーへ。
		Alive = true;
		Sound(3);
		LABulletNum = syoki;
	}
	else if (LABulletNum == 3)//4P
	{
		PopStar = StarCount / 2;
		StarCount -= PopStar;
		m_player[LABulletNum]->SetStarCount(PopStar);
		Plstar = NewGO<PlayerStar>(0, "PlayerStar");
		Plstar->Pop(PadNum, LABulletNum);//プレイヤーからプレイヤーへ。
		Alive = true;
		Sound(3);
		LABulletNum = syoki;
	}
	else//それ以外
	{
		PopStar = StarCount / 2;
		StarCount -= PopStar;
		Sound(3);
		LABulletNum = syoki;
	}
}
//プレイヤーの番号で、○P、☆の数、球の数の場所を決める。
void Player::SetPadNum(int num)
{
	PadNum = num;
	switch (PadNum)
	{
	case 0:
		r_ring->SetPlayerRadar(L"modelData/Ring1P.cmo",this);
		draw_Pl->SetPlayerPicture(L"sprite/1P.dds");
		draw_Pl->SetPosition(-450.0f, -330.0f);
		//プレイヤーの☆の場所
		draw_S->SetS_kazuPosition(-468.0f, -269.0f);
		draw_S->SetStar(L"sprite/Star.dds");
		draw_S->SetS_position(-480.0f, -279.0f);
		//プレイヤーの弾の場所。
		draw_S->SetBullet(L"sprite/tama_red.dds");
		draw_S->SetB_kazuPosition(-370.0f,-325.0f);
		draw_S->SetBulletposition(-365.0f,-285.0f);
		draw_S->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
		//プレイヤーの進化ゲージの場所。
		//bar->SetbarPosition(300.0f, 0.0f);
		//bar->SetgeziPosition(0.0f, 0.0f);
		break;
	case 1:
		r_ring->SetPlayerRadar(L"modelData/Ring2P.cmo", this);
		draw_Pl->SetPlayerPicture(L"sprite/2P.dds");
		draw_Pl->SetPosition(-150.0f, -330.0f);
		//プレイヤーの☆の場所
		draw_S->SetS_kazuPosition(-168.0f, -269.0f);
		draw_S->SetStar(L"sprite/Star.dds");
		draw_S->SetS_position(-180.0f, -279.0f);
		//プレイヤーの弾の場所。
		draw_S->SetBullet(L"sprite/tama_bule.dds");
		draw_S->SetB_kazuPosition(-70.0f, -325.0f);
		draw_S->SetBulletposition(-65.0f, -285.0f);
		draw_S->SetColor(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 2:
		r_ring->SetPlayerRadar(L"modelData/Ring3P.cmo", this);
		draw_Pl->SetPlayerPicture(L"sprite/3P.dds");
		draw_Pl->SetPosition(150.0f, -330.0f);
		//プレイヤーの☆の場所
		draw_S->SetS_kazuPosition(135.0f, -269.0f);
		draw_S->SetStar(L"sprite/Star.dds");
		draw_S->SetS_position(120.0f, -279.f);
		//プレイヤーの弾の場所。
		draw_S->SetBullet(L"sprite/tama_green.dds");
		draw_S->SetB_kazuPosition(230.0f, -325.0f);
		draw_S->SetBulletposition(235.0f, -285.0f);
		draw_S->SetColor(0.1f, 1.0f, 0.0f, 1.0f);
		break;
	case 3:
		r_ring->SetPlayerRadar(L"modelData/Ring4P.cmo", this);
		draw_Pl->SetPlayerPicture(L"sprite/4P.dds");
		draw_Pl->SetPosition(450.0f, -330.0f);
		//プレイヤーの☆の場所
		draw_S->SetS_kazuPosition(428.0f, -269.0f);
		draw_S->SetStar(L"sprite/Star.dds");
		draw_S->SetS_position(420.0f, -279.0f);
		//プレイヤーの弾の場所。
		draw_S->SetBullet(L"sprite/tama_yellow.dds");
		draw_S->SetB_kazuPosition(530.0f, -325.0f);
		draw_S->SetBulletposition(535.0f, -285.0f);
		draw_S->SetColor(1.0f, 0.7f, 0.0f, 1.0f);
		break;
	}
}
//効果音
void Player::Sound(int SoundNum)
{
	if (SoundNum == 0) {//爆発
		SoundSource = NewGO<prefab::CSoundSource>(0);
		SoundSource->Init(L"sound/bakuhatu.wav");
		SoundSource->Play(false);                     //ワンショット再生。
		SoundSource->SetVolume(1.0f);                 //音量調節。
	}
	if (SoundNum == 1) {//弾音
		SoundSource = NewGO<prefab::CSoundSource>(0);
		SoundSource->Init(L"sound/shot1.wav");
		SoundSource->Play(false);                     //ワンショット再生。
		SoundSource->SetVolume(0.2f);                 //音量調節。
	}
	if (SoundNum == 2) {//進化
		SoundSource = NewGO<prefab::CSoundSource>(0);
		SoundSource->Init(L"sound/power-up1.wav");
		SoundSource->Play(false);                     //ワンショット再生。
		SoundSource->SetVolume(1.0f);                 //音量調節。
	}
	if (SoundNum == 3) {//星	
		SoundSource = NewGO<prefab::CSoundSource>(0);
		SoundSource->Init(L"sound/kira-nn.wav");
		SoundSource->Play(false);                     //ワンショット再生。
		SoundSource->SetVolume(1.0f);                 //音量調節。
	}
}
//プレイヤーの中心。
void Player::StarPos()
{
	switch (m_game->GetSansenKazu())
	{
	case 1:
		Tyuou = m_position;
		break;
	case 2:
		Tyuou = m_player[0]->GetPosition()/2 + m_player[1]->GetPosition()/2;
		break;
	case 3:
		Tyuou = m_player[0]->GetPosition()/3 + m_player[1]->GetPosition()/3
			+ m_player[2]->GetPosition()/3;
		break;
	case 4:
		Tyuou = m_player[0]->GetPosition()/4 + m_player[1]->GetPosition()/4
			+ m_player[2]->GetPosition()/4 + m_player[3]->GetPosition()/4;
		break;
	}
}
//プレイヤーをワープさせる()未使用。
void Player::Playerwarp()
{
	if (m_position.x > 35000.0f)
	{
		m_position.x = -30000.0f;
		m_CharaCon.SetPosition(m_position);
		m_skinModelRender->SetPosition(m_position);
	}
	if	(m_position.x < -35000.0f)
	{
	m_position.x = 30000.0f;
	m_CharaCon.SetPosition(m_position);
	m_skinModelRender->SetPosition(m_position);
	}
	if (m_position.z > 19000.0f)
	{
		m_position.z = -15000.0f;
		m_CharaCon.SetPosition(m_position);
		m_skinModelRender->SetPosition(m_position);
	}
	if (m_position.z < -19000.0f)
	{
		m_position.z = 15000.0f;
		m_CharaCon.SetPosition(m_position);
		m_skinModelRender->SetPosition(m_position);
	}
}

float Player::getBulletPercentage() {
	int max;
	float addSpeed;
	switch (Ver) {
	case 0:
		max = MaxSeiseiVer_1;
		addSpeed = SeiseiVer_1;
		break;
	case 1:
		max = MaxSeiseiVer_2;
		addSpeed = SeiseiVer_2;
		break;
	case 2:
		max = MaxSeiseiVer_3;
		addSpeed = SeiseiVer_3;
	}
	if (m_Short == 0) {
		return 0;
	}
	float parce = ((float)m_Short + (m_timer / addSpeed)) / max;
	return parce;
}

//最終進化後、☆を一定個数取ると強化。
void Player::Upper()
{
	if (StarCount >= Star30)
	{
		SyokiSpped = 13.0f;
	}
	else if (StarCount >= Star50)
	{
		SyokiSpped = 15.0f;
	}
}