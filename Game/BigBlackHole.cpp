#include "stdafx.h"
#include "BigBlackHole.h"


BigBlackHole::BigBlackHole()
{
}


BigBlackHole::~BigBlackHole()
{
	if (effect != nullptr) {
		DeleteGO(effect);
	}
}

bool BigBlackHole::Start()
{
	m_game = Game::GetInstance();
	//エフェクトを作成。
	effect = NewGO<prefab::CEffect>(0);
	//エフェクトを再生。
	effect->Play(L"effect/BH.efk");
	effect->SetScale(BBHscale*BBHradius);
	effect->SetPosition(BBHposition);
	//Generate2(BBHposition, radius);
	return true;
}

void BigBlackHole::Update()
{
	Move();
	Count();
}
