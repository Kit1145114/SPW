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
	Move();			//�v���C���[�̑���
	PBullet();		//�v���C���[�̎ˌ�����
	PBullet2();
	Pevolution();	//�v���C���[�̌`��
	Hantei();
	Rotation();
}
//�v���C���[�̑���
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
//�v���C���[�̋�(���`�ԁj
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
//�v���C���[�̋��i���`�ԁj
void Player::PBullet2()
{
	if (Ver == 1)
	{
		S_Rtype2 = NewGO<Senkan_Rtype_2>(0,"Senkan_RType_2");
	}
}
//�v���C���[�̐i���p
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
//�v���C���[�̎��S����
void Player::Hantei()
{	
	if (m_game->m_enemy != nullptr) {
		CVector3 diff = m_enemy->GetPosition() - m_position;
		if (diff.Length() < 250.0f) {
			Death();
		}
	}
}
//�v���C���[�̉�]�����B
void Player::Rotation()
{
	float Rot = atan2(m_moveSpeed.x, m_moveSpeed.z);
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY, Rot);
	m_skinModelRender->SetRotation(qRot);
}
//�v���C���[�̎��S�����B�i���͂܂����g�p�j
void Player::Death()
{
	m_skinModelRender->Init(L"modelData/Star.cmo");
	DeathCount = true;
}