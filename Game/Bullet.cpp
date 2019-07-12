#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
	m_game = Game::GetInstance();
}


Bullet::~Bullet()
{
	DeleteGO(m_skinModelRender);
}

bool Bullet::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	//�v���C���[����󂯎�����ԍ��ŐF��ς���B
	if (PB == 0)
	{
		m_skinModelRender->Init(L"modelData/Bulet.cmo");
	}
	else if (PB == 1)
	{
		m_skinModelRender->Init(L"modelData/Bullet2.cmo");
	}
	else if (PB == 2)
	{
		m_skinModelRender->Init(L"modelData/Bullet3.cmo");
	}
	else if (PB == 3)
	{
		m_skinModelRender->Init(L"modelData/Bullet4.cmo");
	}
	//m_scale = { 10.0f,10.0f,10.0f };
	m_skinModelRender->SetScale(m_scale);
	return true;
}

void Bullet::Update()
{
	m_position += m_moveSpeed * GameTime().GetFrameDeltaTime() * 60;
	m_position.y = BulletYpos;
	m_skinModelRender->SetPosition(m_position);
	timer += GameTime().GetFrameDeltaTime();
	if (timer > Limit)
	{
		Death();
	}
	BulletDeath();
}
//�ǂ̃v���C���[��������������B
int Bullet::GetPB()
{
	switch (PB)
	{
		case 0:
			return 0;
			break;
		case 1:
			return 1;
			break;
		case 2:
			return 2;
			break;
		case 3:
			return 3;
			break;
	}
}
//�ˑR�̎�
void Bullet::Death()
{
	DeleteGO(this);
}
//�v���C���[�̋����m�ŎE�������B
void Bullet::BulletDeath()
{
	QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b)->bool {
		CVector3 kyori = b->GetPosition() - m_position;
		if (b->GetPB() != PB && kyori.Length() < BulletHantei)
		{
			b->Death();
			if (Muteki == false) {
				Death();
			}
		}
			else
			{

			}
			return true;
		});
}
