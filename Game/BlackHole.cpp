#include "stdafx.h"
#include "BlackHole.h"
#include "Star.h"

BlackHole::BlackHole()
{
}


BlackHole::~BlackHole()
{
	if (effect !=nullptr) {
		DeleteGO(effect);
	}
}

bool BlackHole::Start()
{
	m_game = Game::GetInstance();

	//エフェクトを作成。
	effect = NewGO<prefab::CEffect>(0);
	//エフェクトを再生。
	effect->Play(L"effect/BH.efk");
	effect->SetScale(scale*radius);
	effect->SetPosition(m_position);
	return true;
}

void BlackHole::Generate(CVector3 position, float magnification)
{
	BlackHole* bh = NewGO<BlackHole>(0, "BlackHole");
	//保存。
	bh->m_position = position;
	bh->radius *= magnification/500;
}

void BlackHole::Generate2(CVector3 position, float magnification)
{
	BlackHole* bh = NewGO<BlackHole>(0, "BlackHole");
	//保存。
	bh->m_position = position;
	bh->radius *= magnification / 500;
	bh->Countflg = true;  //trueにすることで自然消滅しなくなる。
}

void BlackHole::Move()
{
	//Playerサーチ。
	for (int i = 0; i < Game::GetInstance()->GetSansenKazu(); i++) {
		//プレイヤーが無敵なら吸収をやめる。
		if (Game::GetInstance()->m_player[i]->GetMuteki() == false) {
			//対象との距離を測定。
			CVector3 kyori = Game::GetInstance()->m_player[i]->GetPosition() - m_position;
			//対象との距離がほぼ中心では吸収をやめる。
				if (radius * Searchment / 6<kyori.Length()&& kyori.Length() < radius * Searchment) {
					//Ｇ中心に遠ければ弱く、近ければ強く。
					float G = radius * Searchment - kyori.Length();
					//対象に渡す重力。kyoriにGをかけてG_limitarで制限調整して、反転（-1）すれば重力となる。
					Game::GetInstance()->m_player[i]->SetMoveSpeed(((kyori*G) / G_limitar)*-1);
					//対象との距離が中心に近くなったら。
					if (kyori.Length() < radius * Searchment / 3) {
						//破壊。
						Game::GetInstance()->m_player[i]->Death();
					}
				}
		}
	}
	//Plametサーチ。
	for (int i = 0; i < Planetnumber_Num; i++) {
		//対象がnullptrでなければ。
		if (Game::GetInstance()->memoryPP[i] != nullptr) {
			//対象との距離を測定。
			CVector3 kyori = Game::GetInstance()->memoryPP[i]->GetPosition() - m_position;
			//対象との距離が一定以下になったら。
			if (kyori.Length() < radius * Searchment) {
				//Ｇ中心に遠ければ弱く、近ければ強く。
				float G = radius * Searchment - kyori.Length();
				//対象に渡す重力。kyoriにGをかけてG_limitarで制限調整して、反転（-1）すれば重力となる。
				Game::GetInstance()->memoryPP[i]->SetPosition(((kyori*G) / G_limitar)*-1);
				//対象との距離が中心に近くなったら。
				if (kyori.Length() < radius * Searchment / 3) {
					//破壊。
					Game::GetInstance()->memoryPP[i]->explosion();
				}
			}
		}
	}
	//Starサーチ。
	QueryGOs<Star>("Star", [&](Star* star)->bool {
		CVector3 Kyori = star->GetPosition() - m_position;
		if (Kyori.Length() < radius * Searchment) {
			m_game->SetStarCount(-1);
			star->Death();
		} 
		return true;
	});

	//Bulletサーチ。
	QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b) ->bool {
		//対象との距離を測定。
		CVector3 kyori = b->GetPosition() - m_position;
		//対象との距離が一定以下になったら。
		if (kyori.Length() < radius * Searchment) {
			//Ｇ中心に遠ければ弱く、近ければ強く。
			float G = radius * Searchment - kyori.Length();
			//対象に渡す重力。kyoriにGをかけてG_limitarで制限調整して、反転（-1）すれば重力となる。
			b->SetMoveSpeed(((kyori*G) / G_limitar)*-1);
		}
		return true;
	});
}

void BlackHole::Gravity()
{

}

void BlackHole::Count()
{
	if (Countflg == false) {
		timer++;
		if (timer > 720) {
			Death();
		}
	}
}

void BlackHole::Death()
{
	DeleteGO(this);
	//effect = nullptr;
}

void BlackHole::Update()
{
	Move();
	Count();
}
