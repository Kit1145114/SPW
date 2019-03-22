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
	if (m_timer > 30) {
		m_Short++;
		m_timer = 0;
	}
	//球が一発以上
	if (m_Short > 0) {
		//ABUTTONが押されたとき
		if (Pad(0).IsPress(enButtonRB2/*enButtonA*/) == true) {
			//一つ目
			m_bullet = NewGO<Bullet>(0, "Player_RType2Bullet1");
			m_bullet->SetPosition(m_player->GetPosition());
			m_bullet->SetMoveSpeedZ(10.0f);

			//二つ目
			m_bullet = NewGO<Bullet>(0, "Player_RType2Bullet2");
			CVector3 pos = m_player->GetPosition();
			pos.x += 50.0f;
			m_bullet->SetPosition(pos);
			m_bullet->SetMoveSpeedZ(10.0f);

			//三つ目
			m_bullet = NewGO<Bullet>(0, "Player_RType2Bullet3");
			pos.x -= 100.0f;
			m_bullet->SetPosition(pos);
			m_bullet->SetMoveSpeedZ(10.0f);
			m_Short--;
			ShortCount = true;
			p_timer = 0;
		}
	}
	else if (Pad(0).IsPress(enButtonRB2/*enButtonA*/) == false) {
		if (p_timer == 99)
		{
			ShortCount = false;
			p_timer = 0;
		}
	}
}