#include "stdafx.h"
#include "Player.h"
#include "Network/NPad.h"
#include "Sinka_Bar.h"
#include "Crown.h"

Player::Player()
{
	draw_Pl = NewGO<Draw_Player>(0);
	draw_S = NewGO<Draw_Skazu>(0);
	r_ring = NewGO<RadarRing>(0);
}

void Player::OnDestroy()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(draw_Pl);
	DeleteGO(draw_S);
	DeleteGO(r_ring);
	DeleteGO(crown);
	if (effect != nullptr) {
		DeleteGO(effect);
	}
}

bool Player::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Senkan.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_scale = { 9.6f,9.6f,9.6f };
	m_skinModelRender->SetScale(m_scale);
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
	//ゲーム終了後の勝利演出。勝者の場合、移動とローテーションだけ許可する。
	if (!isWinner) {
		if (Game::GetInstance()->isWait()) {
			return;
		}
	} else {
		//同点1位の場合のワープ
		if (tiesMove > 0) {
			float delta = GameTime().GetFrameDeltaTime();
			if (tiesMove > c_tiseMove / 2) {
				m_position.y -= delta * 5000;
				tiesMove -= delta;
				if (tiesMove <= c_tiseMove / 2) {
					m_position.x = tiesMovePos.x;
					m_position.z = tiesMovePos.z;
				}
			} else {
				m_position.y += delta * 5000;
				tiesMove -= delta;
			}
		}

		Muteki = false;
		DeathCount = false;
		m_skinModelRender->SetActiveFlag(true);
		crown->setPosition(m_position);
	}
	if (StarCount == MaxStarCount)
	{
		StarCount = MaxStarCount;
	}
	Move();			//プレイヤーの操作
	Rotation();
	if (Game::GetInstance()->isWaitEnd())return;//勝者でもここから下は許可しない
	Upper();
	if (charge == false) {
		PBullet();		//プレイヤーの球（第一形態）
		PBullet2();		//プレイヤーの球（第二形態）
		PBullet3();		//プレイヤーの球（第三形態）
	}
	SpecialBullet();
	//dollars();
	Pevolution();	//プレイヤーの形態
	Respawn();
	S_Hantei();
	B_Hantei();
	Houdai();
	MutekiTimes();
	HP();
	StarPos();
	//Playerwarp();
	memory_position = m_position;
	draw_S->SetKazu(StarCount);
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
		m_timer += GameTime().GetFrameDeltaTime();  
		p_timer += GameTime().GetFrameDeltaTime();
		if (m_timer >= SeiseiVer_1) {
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
					if (NPad(PadNum).IsPress(enButtonRB1) == true
						|| NPad(PadNum).IsPress(enButtonRB2) == true) {
						float Btime = 1.00f;
						m_bullet = NewGO<Bullet>(0, "PlayerBullet");
						m_bullet->SetPBnum(PadNum);
						m_bullet->SetPosition(m_position);
						m_bullet->SetPositionXZ(HoukouX, HoukouZ);
						m_bullet->AddLimit(Btime);
						//プレイヤーの速度の単位をm/frameに変更する。
						m_bullet->SetMoveSpeedZ(SpeedX + GetmoveSpeedFrame().x, SpeedZ + GetmoveSpeedFrame().z);
						m_Short--;
						Sound(1);//効果音
						ShortCount = true;
						m_game->SetKazu(1);
						p_timer = Timer0;
					}
					else {
						if (p_timer == 98.0f)
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
		m_timer += GameTime().GetFrameDeltaTime();
		p_timer += GameTime().GetFrameDeltaTime();
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
					float Btime = 1.25f;
						if (NPad(PadNum).IsPress(enButtonRB1) == true
						|| NPad(PadNum).IsPress(enButtonRB2) == true) {
						m_bullet = NewGO<Bullet>(0, "PlayerBullet");
						m_bullet->SetPBnum(PadNum);
						m_bullet->SetPosition(m_position);
						m_bullet->SetPositionXZ(HoukouX, HoukouZ);
						m_bullet->AddLimit(Btime);
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
		m_timer += GameTime().GetFrameDeltaTime();
		p_timer += GameTime().GetFrameDeltaTime();
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
					float Btime = 1.50f;
						if (NPad(PadNum).IsPress(enButtonRB1) == true
						|| NPad(PadNum).IsPress(enButtonRB2) == true) {
						m_bullet = NewGO<Bullet>(0, "PlayerBullet");
						m_bullet->SetPBnum(PadNum);
						m_bullet->SetPosition(m_position);
						m_bullet->SetPositionXZ(HoukouX, HoukouZ);
						m_bullet->SetMoveSpeedZ(SpeedX + GetmoveSpeedFrame().x, SpeedZ + GetmoveSpeedFrame().z);
						m_bullet->AddLimit(Btime);
						//m_bullet->SetScale(BScale);
						
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
//プレイヤーの特殊球(早いのはここです。）
void Player::SpecialBullet()
{
	int Short = 20;				//球の消費をいじるときはこ↑こ↓
	int BDamage = 100;			//確殺です。
	int S_Double = 3;			//スピードを倍々チャンスしております。
	float Limit = 2.0;			//リミット。
	float B_Hantei = 3000.0f;	//判定の大きさをいじるときはこ↑こ↓
	CVector3 BScale = { 75.0f,75.0f,75.0f };	//球大きさ。
	CVector3 EScale = { 3.0f,3.0f,3.0f };		//エフェクトの大きさ。
	if (m_Short >= Short && charge  == false)
	{
		if (NPad(PadNum).IsPress(enButtonLB1)==true || NPad(PadNum).IsPress(enButtonLB2)== true)
		{
			charge = true;
			effect = NewGO<prefab::CEffect>(0);
			effect->Play(L"effect/o-ra.efk");
			effect->SetEffectFlag(true);
			m_Short -= Short;					//球の消費20発分。
		}
	}
	if (charge == true)
	{
		effect->SetPosition(m_position);
		effect->SetScale(EScale);
		timer += GameTime().GetFrameDeltaTime();
		if (timer >= Limit && DeathCount == false)
		{
			charge = false;
			timer = Timer0;
			DeleteGO(effect);
			effect = nullptr;
			m_bullet = NewGO<Bullet>(0, "PlayerBullet");
			m_bullet->SetPBnum(PadNum);
			m_bullet->SetPosition(m_position);
			m_bullet->SetPositionXZ(HoukouX, HoukouZ);
			m_bullet->SetScale(BScale);			//大きさ
			m_bullet->SetHantei(B_Hantei);		//判定の大きさ。
			m_bullet->SetDamage(BDamage);		//DAMAGE100
			m_bullet->SetMuteki(true);			//この球を無敵に
			//プレイヤーの速度の単位をm/frameに変更する。
			m_bullet->SetMoveSpeedZ(
			(SpeedX + GetmoveSpeedFrame().x)*S_Double,	//倍々
			(SpeedZ + GetmoveSpeedFrame().z)*S_Double	//倍々
			);
			Sound(1);//効果音
			ShortCount = true;
		}
		if (charge == true && DeathCount == true)
		{
			charge = false;
			timer = Timer0;
			DeleteGO(effect);
			effect = nullptr;
		}
	}
}
//プレイヤーの二ドル球
void Player::dollars()
{
	int Consumption = 10;
	if (m_Short > Consumption)
	{
		if (NPad(PadNum).IsPress(enButtonB))
		{
			m_Short -= Consumption;
		}
	}
}
//プレイヤーの進化用
void Player::Pevolution()
{
	if (StarCount >= 5 && m_mode == 0 && StarCount <= 14 && m_mode == 0)
	{
		m_skinModelRender->Init(L"modelData/SenkanType2.cmo");
		m_scale = { 9.0f,9.0f,9.0f };
		m_skinModelRender->SetScale(m_scale);
		//カメラの引きを進化によって決めるのはローカルでは使用しない。ネットワークがどうなるかは未定。
		//camera->SetPos(7000.0f);
		Ver = 1;
		m_Short = 0;
		m_mode = 1;
		Sound(2);//効果音
	}
	if (StarCount >= 15 && m_mode == 1|| StarCount >= 15 && Ver == 0)
	{
		m_skinModelRender->Init(L"modelData/SenkanType3.cmo");
		m_scale = { 10.0f,10.0f,10.0f };
		m_skinModelRender->SetScale(m_scale);
		//camera->SetPos(9000.0f);
		Ver = 2;
		m_Short = 0;
		m_mode = 2;
		Sound(2);//効果音
	}
}
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
		m_skinModelRender->SetActiveFlag(false);
		memory_position = m_position;
		ShortCount = false;
		DeathCount = true;
		Alive = false;
		Muteki = true;
		draw_Pl->SetDeath(true);
		if (CountExplosion == false) {
			CountExplosion = true;
			//効果音
			Sound(0);
		}
}
//プレイヤーのリスポーン処理。
void Player::Respawn()
{
	if (DeathCount == true)
	{
		float Respown = 3.0f;
 		d_timer += GameTime().GetFrameDeltaTime();
		if (d_timer > Respown)
		{
			if (Ver == 0) {
				m_skinModelRender->Init(L"modelData/Senkan.cmo");
				m_skinModelRender->SetPosition(m_position);
				m_CharaCon.SetPosition(m_position);
				d_timer = Timer0;
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
		HoukouX = NPad(PadNum).GetRStickXF() * 150.0f;
		HoukouZ = NPad(PadNum).GetRStickYF() * 150.0f;
		SpeedX = NPad(PadNum).GetRStickXF() * 110.0f;
		SpeedZ = NPad(PadNum).GetRStickYF() * 110.0f;
	}
	else if (Ver == 1)
	{
		HoukouX = NPad(PadNum).GetRStickXF() * 150.0f;
		HoukouZ = NPad(PadNum).GetRStickYF() * 150.0f;
		SpeedX = NPad(PadNum).GetRStickXF() * 150.0f;
		SpeedZ = NPad(PadNum).GetRStickYF() * 150.0f;
		
	}
	else if (Ver == 2)
	{
		HoukouX = NPad(PadNum).GetRStickXF() * 150.0f;
		HoukouZ = NPad(PadNum).GetRStickYF() * 150.0f;
		SpeedX = NPad(PadNum).GetRStickXF() * 200.0f;
		SpeedZ = NPad(PadNum).GetRStickYF() * 200.0f;
	}
		
	
}
//☆の当たり判定。
void Player::S_Hantei()
{
	QueryGOs<Star>("Star", [&](Star* star)->bool {
		CVector3 Kyori = star->GetPosition() - m_position;
		if (Kyori.Length() < StarHantei) {
			
			StarCount+= star->GetPoint();
			
			star->Death();
			if (StarCount > 20)
			{
				MaxSeiseiVer_3++;
			}
		}
		return true;
	});
}
//プレイヤー同士の球の判定
void Player::B_Hantei()
{
	if (Muteki == false) {
		QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b) ->bool {
			CVector3 kyori = b->GetPosition() - m_position;
			if (b->GetPB() != PadNum && kyori.Length() < BulletHantei)
			{
				PlHP -= b->GetDamage();
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

		if (MutekiTime >= 240) {
			m_skinModelRender->SetActiveFlag(true);
			Muteki = false;
			MutekiTime = 0;
		}
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
		draw_S->SetS_position(-500.0f, -279.0f);
		draw_S->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case 1:
		r_ring->SetPlayerRadar(L"modelData/Ring2P.cmo", this);
		draw_Pl->SetPlayerPicture(L"sprite/2P.dds");
		draw_Pl->SetPosition(-150.0f, -330.0f);
		//プレイヤーの☆の場所
		draw_S->SetS_kazuPosition(-168.0f, -269.0f);
		draw_S->SetStar(L"sprite/Star.dds");
		draw_S->SetS_position(-200.0f, -279.0f);
		draw_S->SetColor(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 2:
		r_ring->SetPlayerRadar(L"modelData/Ring3P.cmo", this);
		draw_Pl->SetPlayerPicture(L"sprite/3P.dds");
		draw_Pl->SetPosition(150.0f, -330.0f);
		//プレイヤーの☆の場所
		draw_S->SetS_kazuPosition(135.0f, -269.0f);
		draw_S->SetStar(L"sprite/Star.dds");
		draw_S->SetS_position(100.0f, -279.f);
		draw_S->SetColor(0.1f, 1.0f, 0.0f, 1.0f);
		break;
	case 3:
		r_ring->SetPlayerRadar(L"modelData/Ring4P.cmo", this);
		draw_Pl->SetPlayerPicture(L"sprite/4P.dds");
		draw_Pl->SetPosition(450.0f, -330.0f);
		//プレイヤーの☆の場所
		draw_S->SetS_kazuPosition(428.0f, -269.0f);
		draw_S->SetStar(L"sprite/Star.dds");
		draw_S->SetS_position(400.0f, -279.0f);
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

void Player::setWinner() {
	isWinner = true;
	crown = NewGO<Crown>(0);
	crown->setPosition(m_position);
}
//プレイヤーのカラー。
CVector4 Player::getColor() {
	switch (PadNum) {
	case 0:
		return CVector4(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case 1:
		return CVector4(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 2:
		return CVector4(0.1f, 1.0f, 0.0f, 1.0f);
		break;
	case 3:
		return CVector4(1.0f, 0.7f, 0.0f, 1.0f);
		break;
	}
	return CVector4::White;
}
//最終進化後、☆を一定個数取ると強化。
void Player::Upper()
{
	if (StarCount >= Star40)
	{
		SyokiSpped = 13.0f;
	}
	else if (StarCount >= Star60)
	{
		SyokiSpped = 15.0f;
	}
}