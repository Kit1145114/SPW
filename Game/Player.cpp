#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	draw_Pl = NewGO<Draw_Player>(0);
	draw_S = NewGO<Draw_Skazu>(0);
}

Player::~Player()
{
	DeleteGO(m_skinModelRender);
	if (d_hako != nullptr)
	{
		DeleteGO(d_hako);
	}
	DeleteGO(draw_Pl);
	DeleteGO(draw_S);
}

bool Player::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Senkan.cmo");
	m_scale = { 3.0f,3.0f,3.0f };
	m_skinModelRender->SetScale(m_scale);
	m_CharaCon.Init(300.0f, 300.0f, m_position);
	m_game = Game::GetInstance();
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
	Move();			//�v���C���[�̑���
	PBullet();		//�v���C���[�̎ˌ�����
	PBullet2();
	PBullet3();
	Pevolution();	//�v���C���[�̌`��
	//Hantei();
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
//�v���C���[�̑���
void Player::Move()
{
	if (DeathCount == false) {
		if (Muteki == false) {
			if (Ver == 0) {
				m_moveSpeed.x = Pad(PadNum).GetLStickXF()* +5.0f;
				m_moveSpeed.z = Pad(PadNum).GetLStickYF()* +5.0f;
				m_position = m_CharaCon.Execute(/*5.0f,*/ m_moveSpeed, 12.0f);
				m_skinModelRender->SetPosition(m_position);
			}
			else if (Ver == 1)
			{
				m_moveSpeed.x = Pad(PadNum).GetLStickXF()* +7.0f;
				m_moveSpeed.z = Pad(PadNum).GetLStickYF()* +7.0f;
				m_position = m_CharaCon.Execute(/*5.0f,*/ m_moveSpeed, 12.0f);
				m_skinModelRender->SetPosition(m_position);
			}
			else if (Ver == 2) {
				m_moveSpeed.x = Pad(PadNum).GetLStickXF()* +10.0f;
				m_moveSpeed.z = Pad(PadNum).GetLStickYF()* +10.0f;
				m_position = m_CharaCon.Execute(/*5.0f,*/ m_moveSpeed, 12.0f);
				m_skinModelRender->SetPosition(m_position);
			}
				if (m_moveSpeed.x != 0.0f || m_moveSpeed.z != 0.0f) {
				memoryHX = m_moveSpeed.x;
				memoryHZ = m_moveSpeed.z;
				memorySX = m_moveSpeed.x;
				memorySZ = m_moveSpeed.z;
			}
			else if (Pad(PadNum).GetLStickXF() == 0.0 && Pad(PadNum).GetLStickYF() == 0.0
					&& Pad(PadNum).GetRStickXF() == 0.0 && Pad(PadNum).GetRStickYF() == 0.0) {
				HoukouX = memoryHX * 10.0f;
				HoukouZ = memoryHZ * 10.0f;
				SpeedX = memorySX  * 10.0f;
				SpeedZ = memorySZ  * 10.0f;
			}
		}
		else if (Muteki == true)
		{
			m_moveSpeed.x = Pad(PadNum).GetLStickXF()* +10.0f;
			m_moveSpeed.z = Pad(PadNum).GetLStickYF()* +10.0f;
			m_position = m_CharaCon.Execute(/*5.0f,*/ m_moveSpeed, 12.0f);
			m_skinModelRender->SetPosition(m_position);
		}
	}
}
//�v���C���[�̋�(���`�ԁj
void Player::PBullet()
{
	if (DeathCount == false) {
		if (Ver == 0) {
			m_timer++;  // =GameTime().GetFrameDeltaTime;
			p_timer++;
			if (m_timer > SeiseiVer_1) {
				m_Short++;
				m_timer = Timer0;
			}
			if (m_Short > 0) {
				if (Pad(PadNum).IsPress(enButtonRB2) == true) {
					m_bullet = NewGO<Bullet>(0, "PlayerBullet");
					m_bullet->SetPB(PadNum);
					m_bullet->SetPosition(m_position);
					m_bullet->SetPositionXZ(HoukouX, HoukouZ);
					m_bullet->SetMoveSpeedZ(SpeedX, SpeedZ);
					m_Short--;
					ShortCount = true;
					m_game->SetKazu(1);
					p_timer = Timer0;
				}
				else {
					if (p_timer == 98)
					{
						ShortCount = false;
						//m_game->SetPBInit(false);
						p_timer = Timer0;
					}
				}
			}
		}
	}
}
//�v���C���[�̋��i���`�ԁj
void Player::PBullet2()
{
	if(DeathCount == false)
		if (Ver == 1)
		{
			m_timer++;  // =GameTime().GetFrameDeltaTime;
			p_timer++;
			if (m_timer > SeiseiVer_2) {
				m_Short++;
				m_timer = Timer0;
			}
			if (m_Short > 0)
			{
				if (Pad(PadNum).IsPress(enButtonRB2) == true) {
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
//�v���C���[�̋��i�ŏI�`�ԁj
void Player::PBullet3()
{
	if (DeathCount == false)
		if (Ver == 2)
		{
			m_timer++;  // =GameTime().GetFrameDeltaTime;
			p_timer++;
			if (m_timer > SeiseiVer_3) {
				m_Short++;
				m_timer = Timer0;
			}
			if (m_Short > 0)
			{
				if (Pad(PadNum).IsPress(enButtonRB2) == true) {
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
//�v���C���[�̐i���p
void Player::Pevolution()
{
	if (StarCount == 5 && m_mode == 0)
	{
		m_skinModelRender->Init(L"modelData/SenkanType2.cmo");
		m_scale = { 5.0f,5.0f,5.0f };
		m_skinModelRender->SetScale(m_scale);
		//S_Rtype2 = NewGO<Senkan_Rtype_2>(0,"Senkan_RType_2");
		Ver = 1;
		m_Short = 0;
		m_mode = 1;
	}
	if (StarCount == 10 && m_mode == 1)
	{
		m_skinModelRender->Init(L"modelData/SenkanType3.cmo");
		m_scale = { 7.0f,7.0f,7.0f };
		m_skinModelRender->SetScale(m_scale);
		Ver = 2;
		m_Short = 0;
		m_mode = 2;
	}
}
//�v���C���[�̃��u����
void Player::Hantei()
{
	if (Muteki == false) {
		if (Game::GetInstance()->m_enemy != nullptr) {
			CVector3 diff = Game::GetInstance()->GetPosition() - m_position;
			if (diff.Length() < 250.0f) {
				Death();
				draw_Pl->SetDeath(true);
			}
		}
	}
}
//�v���C���[�̔��Ƃ̔���
void Player::HakoHantei()
{
	CVector3 Kyori = m_position - d_hako->GetPosition();
	if (Kyori.Length() < 150.0f)
	{
		Ver = 1;
		d_hako->Death();
	}
}
//�v���C���[�̉�]�����B
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
//�v���C���[�̎��S�����B
void Player::Death()
{
	m_skinModelRender->Init(L"modelData/Hako.cmo");
	memory_position = m_position;
	ShortCount = false;
	DeathCount = true;
	Alive = false;
	draw_Pl->SetDeath(true);
	if (CountExplosion == false) {
		CountExplosion = true;
		//�G�t�F�N�g���쐬�B
		prefab::CEffect* effect;
		effect = NewGO<prefab::CEffect>(0);
		//�G�t�F�N�g���Đ��B
		effect->Play(L"effect/explosion2.efk");
		effect->SetPosition(this->m_position);
	}

}
//�v���C���[�̃��X�|�[�������B
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
			else if (Ver == 2)
			{
				m_skinModelRender->Init(L"modelData/SenkanType3.cmo");
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
//�v���C���[�̌������̐ݒ�B
void Player::Houdai()
{
	if (Ver == 0) {
		HoukouX = Pad(PadNum).GetRStickXF() * 75.0f;
		HoukouZ = Pad(PadNum).GetRStickYF() * 75.0f;
		SpeedX = Pad(PadNum).GetRStickXF() * 50.0f;
		SpeedZ = Pad(PadNum).GetRStickYF() * 50.0f;
		if (Pad(PadNum).GetRStickXF() == 0.0 && Pad(PadNum).GetRStickYF() == 0.0)
		{
			HoukouX = memoryHX;
			HoukouZ = memoryHZ;
			SpeedX = memorySX;
			SpeedZ = memorySZ;
		}
	}
	else if (Ver == 1)
	{
		HoukouX = Pad(PadNum).GetRStickXF() * 150.0f;
		HoukouZ = Pad(PadNum).GetRStickYF() * 150.0f;
		SpeedX = Pad(PadNum).GetRStickXF() * 100.0f;
		SpeedZ = Pad(PadNum).GetRStickYF() * 100.0f;
		if (Pad(PadNum).GetRStickXF() == 0.0 && Pad(PadNum).GetRStickYF() == 0.0)
		{
			HoukouX = memoryHX;
			HoukouZ = memoryHZ;
			//SpeedX = memorySX;
			//SpeedZ = memorySZ;
		}
	}
	else if (Ver == 2)
	{
		HoukouX = Pad(PadNum).GetRStickXF() * 150.0f;
		HoukouZ = Pad(PadNum).GetRStickYF() * 150.0f;
		SpeedX = Pad(PadNum).GetRStickXF() * 200.0f;
		SpeedZ = Pad(PadNum).GetRStickYF() * 200.0f;
		if (Pad(PadNum).GetRStickXF() == 0.0 && Pad(PadNum).GetRStickYF() == 0.0)
		{
			HoukouX = memoryHX;
			HoukouZ = memoryHZ;
			//SpeedX = memorySX;
			//SpeedZ = memorySZ;
		}
	}
}
//���̓����蔻��B
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
				draw_S->AddKazu(1);
				m_game->SetStarCount(-1);
				star->Death();
			}
			return true;
		});
	}
}
//�v���C���[�̗��Ƃ������̓����蔻��B
void Player::PlS_Hantei()
{
	if (DeathCount == false) {
		if (Game::GetInstance()->GetPlS_Init() == false)
		{
			Plstar = nullptr;
		}
		else if (Game::GetInstance()->GetPlS_Init() == true)
		{
			QueryGOs<PlayerStar>("PlayerStar", [&](PlayerStar* plstar)->bool {
				CVector3 Len = plstar->GetPosition() - m_position;
				if (Len.Length() < 400.0f)
				{
					StarCount += plstar->GetStarCount();
					draw_S->SetKazu(StarCount);
					Game::GetInstance()->AddPlStarCount(-1);
					plstar->Death();
				}
				return true;
			});
		}
	}
}
//�v���C���[���m�̋��̔���
void Player::B_Hantei()
{
	if (m_game->GetPBInit() == true) {
		if (Muteki == false) {
			QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b) ->bool {
				CVector3 kyori = b->GetPosition() - m_position;
				if (b->GetPB() != PadNum && kyori.Length() < BulletHantei)
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
//�v���C���[���m�̓����蔻��i���������B�j
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
//���G���Ԃ̒����B
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
//���񂾌��HP�������B
void Player::HP()
{
	if (PlHP <= 0)
	{
		PlHP = 0;
		Death();
	}
}
//�v���C���[�̎����𗎂Ƃ��B
void Player::StarPop()
{
	if (Alive == false && Plstar == nullptr)
	{
		if (StarCount > 1) {
			PopStar = StarCount / 2;
			StarCount -= PopStar;
			draw_S->SetKazu(StarCount);
			Plstar = NewGO<PlayerStar>(0, "PlayerStar");
			Plstar->SetPosition(m_position);
			Plstar->SetStarCount(PopStar);
			Game::GetInstance()->AddPlStarCount(1);
			Alive = true;
		}
	}
	else
	{
		PopStar = 0;
	}
}
//�v���C���[�̔ԍ������߂�B
void Player::SetPadNum(int num)
{
	PadNum = num;
	switch (PadNum)
	{
	case 0:
		draw_Pl->SetPlayerPicture(L"sprite/1P.dds");
		draw_Pl->SetPosition(-450.0f, -300.0f);
		draw_S->SetPosition(-450.0f, -220.0f);
		draw_S->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case 1:
		draw_Pl->SetPlayerPicture(L"sprite/2P.dds");
		draw_Pl->SetPosition(-150.0f, -300.0f);
		draw_S->SetPosition(-150.0f, -220.0f);
		draw_S->SetColor(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 2:
		draw_Pl->SetPlayerPicture(L"sprite/3P.dds");
		draw_Pl->SetPosition(150.0f, -300.0f);
		draw_S->SetPosition(150.0f, -220.0f);
		draw_S->SetColor(0.1f, 1.0f, 0.0f, 1.0f);
		break;
	case 3:
		draw_Pl->SetPlayerPicture(L"sprite/4P.dds");
		draw_Pl->SetPosition(450.0f, -300.0f);
		draw_S->SetPosition(450.0f, -220.0f);
		draw_S->SetColor(1.0f, 0.7f, 0.0f, 1.0f);
		break;
	}
}