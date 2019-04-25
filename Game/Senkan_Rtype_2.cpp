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
	PadNum = m_player->GetPadNum();
	return true;
}

void Senkan_Rtype_2::Update()
{
	m_timer++;
	p_timer++;
	Houdai();
	if (m_timer > Maxtimer) {
		m_Short++;
		m_timer = 0;
	}
	//‹…‚ªˆê”­ˆÈã
	if (m_Short > 0) {
		//ABUTTON‚ª‰Ÿ‚³‚ê‚½‚Æ‚«
		if (Pad(PadNum).IsPress(enButtonRB2/*enButtonA*/) == true) {
			//ˆê‚Â–Ú
			m_bullet = NewGO<Bullet>(0, "PlayerBullet");
			m_bullet->SetPosition(m_player->GetPosition());
			m_bullet->SetPositionXZ(HoukouX, HoukouZ);
			m_bullet->SetMoveSpeedZ(SpeedX, SpeedZ);

			//“ñ‚Â–Ú
			m_bullet = NewGO<Bullet>(0, "PlayerBullet");
			CVector3 pos = m_player->GetPosition();
			pos.x += 50.0f;
			m_bullet->SetPosition(pos);
			m_bullet->SetPositionXZ(HoukouX, HoukouZ);
			m_bullet->SetMoveSpeedZ(SpeedX, SpeedZ);

			//ŽO‚Â–Ú
			m_bullet = NewGO<Bullet>(0, "PlayerBullet");
			pos.x -= 100.0f;
			m_bullet->SetPosition(pos);
			m_bullet->SetPositionXZ(HoukouX, HoukouZ);
			m_bullet->SetMoveSpeedZ(SpeedX, SpeedZ);

			m_Short--;
			ShortCount = true;
			//m_game->SetKazu(3);
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
//’e‚Ì•ûŒü
void Senkan_Rtype_2::Houdai()
{
	//HoukouX = Pad(PadNum).GetRStickXF() * 150.0f;
	//HoukouZ = Pad(PadNum).GetRStickYF() * 150.0f;
	//SpeedX = Pad(PadNum).GetRStickXF() * 15.0f;
	//SpeedZ = Pad(PadNum).GetRStickYF() * 15.0f;
	if (Pad(m_player->GetPadNum()).GetRStickXF() == 0.0, Pad(m_player->GetPadNum()).GetRStickYF() == 0.0)
	{
		HoukouX = 0.0f;
		HoukouZ = 150.0f;
		SpeedX = 0.0f;
		SpeedZ = 15.0f;
	}
}