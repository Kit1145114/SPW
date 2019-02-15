#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}


bool Player::Start()
{
	m_CharaCon.Init(30.0f, 100.0f, m_position);
	return true;
}

void Player::Update()
{

}

void Player::Move()
{
	//if (Pad(0).IsPress(enButtonX) == true) {
	//	m_moveSpeed.x = Pad(0).GetLStickXF()* +2.5f;
	//	m_moveSpeed.z = Pad(0).GetLStickYF()* +2.5f;
	//	m_position = m_CharaCon.Execute(5.0f, m_moveSpeed);
	//}
	//else if (Pad(0).IsPress(enButtonX) == false) {
	//	m_moveSpeed.x = Pad(0).GetLStickXF()* +1.5f;
	//	m_moveSpeed.z = Pad(0).GetLStickYF()* +1.5f;
	//	m_position = m_CharaCon.Execute(5.0f, m_moveSpeed);
	//}
}