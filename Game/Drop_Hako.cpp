#include "stdafx.h"
#include "Drop_Hako.h"


Drop_Hako::Drop_Hako()
{
}


Drop_Hako::~Drop_Hako()
{
	DeleteGO(m_skinModelRender);
}

bool Drop_Hako::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Hako.cmo");
	m_player = FindGO<Player>("Player");
	game = FindGO<Game>("Game");
	m_position = m_player->GetMemoryPosition();
	m_skinModelRender->SetPosition(m_position);
	return true;
}

void Drop_Hako::Update()
{
	//Spawn();
	Push();
	Hantei();
	timer++;
	if (timer == 900)
	{
		Death();
		spwancount--;
	}
}
//プレイヤーとの判定
void Drop_Hako::Hantei()
{
	if (m_player->GetDeathCount() == false) {
		CVector3 Kyori = m_player->GetPosition() - m_position;
		if (Kyori.Length() < 150.0f)
		{
			m_player->SetVer(1);
			Death();
		}
	}
}
//アイテムの生成
void Drop_Hako::Spawn()
{
}
//アイテムの削除。
void Drop_Hako::Death()
{
	DeleteGO(this);
}

void Drop_Hako::Push()
{
	m_skinModelRender->SetPosition(m_position);
}

