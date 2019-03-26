#include "stdafx.h"
#include "Senkan_Rtype_2.h"


Senkan_Rtype_2::Senkan_Rtype_2()
{
}


Senkan_Rtype_2::~Senkan_Rtype_2()
{
}

bool Senkan_Rtype_2::Start()
{
	m_player = FindGO<Player>("Player");
	return true;
}

void Senkan_Rtype_2::Update()
{
	m_timer++;
	p_timer++;
	if (m_timer > Maxtimer) {
		m_Short++;
		m_timer = 0;
	}
	//�����ꔭ�ȏ�
	if (m_Short > 0) {
		//ABUTTON�������ꂽ�Ƃ�
		if (Pad(0).IsPress(enButtonRB2/*enButtonA*/) == true) {
			//���
			m_bullet = NewGO<Bullet>(0, "Player_RType2Bullet1");
			m_bullet->SetPosition(m_player->GetPosition());
			m_bullet->SetMoveSpeedZ(15.0f);

			//���
			m_bullet = NewGO<Bullet>(0, "Player_RType2Bullet2");
			CVector3 pos = m_player->GetPosition();
			pos.x += 50.0f;
			m_bullet->SetPosition(pos);
			m_bullet->SetMoveSpeedZ(15.0f);

			//�O��
			m_bullet = NewGO<Bullet>(0, "Player_RType2Bullet3");
			pos.x -= 100.0f;
			m_bullet->SetPosition(pos);
			m_bullet->SetMoveSpeedZ(15.0f);

			m_Short--;
			ShortCount = true;
			p_timer = 0;
		}
	}
	else if (Pad(0).IsPress(enButtonRB2/*enButtonA*/) == false) {
		if (p_timer == 98)
		{
			ShortCount = false;
			p_timer = 0;
		}
	}
}