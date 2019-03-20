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
	Move();			//�v���C���[�̑���
	PBullet();		//�v���C���[�̎ˌ�����	//�v���C���[�̌`��
	//PHantei();
	Rotation();
}

void Player_RType2::Move()
{
	m_moveSpeed.x = Pad(0).GetLStickXF()* +2.5f;
	m_moveSpeed.z = Pad(0).GetLStickYF()* +2.5f;
	m_position = m_CharaCon.Execute(/*5.0f,*/ m_moveSpeed, 14.0f);
	m_skinModelRender->SetPosition(m_position);
}

void Player_RType2::PBullet()
{
	m_timer++;

	if (m_timer > 30) {
		m_Short++;
		m_timer = 0;
	}
	//�����ꔭ�ȏ�
	if (m_Short > 0) {
		//ABUTTON�������ꂽ�Ƃ�
		if (Pad(0).IsPress(enButtonRB1/*enButtonA*/)) {
			//���
			m_bullet = NewGO<Bullet>(0, "Player_RType2Bullet");
			m_bullet->SetPosition(m_position);
			m_bullet->SetMoveSpeed(10.0f);
			
			//���
			m_bullet = NewGO<Bullet>(0, "Player_RType2Bullet");
			CVector3 pos = m_position;
			pos.x += 50.0f;
			m_bullet->SetPosition(pos);
			m_bullet->SetMoveSpeed(10.0f);
			
			//�O��
			m_bullet = NewGO<Bullet>(0, "Player_RType2Bullet");
			pos.x -= 100.0f;
			m_bullet->SetPosition(pos);
			m_bullet->SetMoveSpeed(10.0f);
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

void Player_RType2::PHantei()
{
	CVector3 diff = m_enemy->GetPosition() - m_position;
	if (diff.Length() < 250.0f) {
		m_game = FindGO<Game>("Game");
		m_game->GameMode = 1;
	}
}

void Player_RType2::Rotation()
{
	float Rot = atan2(m_moveSpeed.x, m_moveSpeed.z);
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY, Rot);
	m_skinModelRender->SetRotation(qRot);
}