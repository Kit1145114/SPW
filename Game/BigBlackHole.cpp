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
	effect->SetScale(scale*radius);
	effect->SetPosition(BBHposition);
	return true;
}

void BigBlackHole::Generate(CVector3 position, float magnification, float Search, float Limit)
{
	BigBlackHole* bh = NewGO<BigBlackHole>(0, "BigBlackHole");
	//保存。
	bh->position = position;
	bh->radius *= magnification;
	bh->Searchment = Search;//	BHの重力範囲の調整。
	bh->G_limitar = Limit;//   BHの重力（Ｇ）調整。
}

void BigBlackHole::Gravity()
{
	//Playerサーチ。
	for (int i = 0; i < Game::GetInstance()->GetSansenKazu(); i++) {
		//プレイヤーが無敵なら吸収をやめる。
		if (Game::GetInstance()->m_player[i]->GetMuteki() == false) {
			//対象との距離を測定。
			CVector3 kyori = Game::GetInstance()->m_player[i]->GetPosition() - position;
			//対象との距離がほぼ中心では吸収をやめる。
			if (radius * Searchment / 10 < kyori.Length() && kyori.Length() < radius * Searchment) {
				//Ｇ中心に遠ければ弱く、近ければ強く。
				float G = radius * Searchment - kyori.Length();
				//対象に渡す重力。kyoriにGをかけてG_limitarで制限調整して、反転（-1）すれば重力となる。
				Game::GetInstance()->m_player[i]->SetMoveSpeed(((kyori*G) / G_limitar)*-1);
				//対象との距離が中心に近くなったら。
				if (kyori.Length() < radius * Searchment / 5) {
					//破壊。
					Game::GetInstance()->m_player[i]->Death();
					Game::GetInstance()->m_player[i]->SetLABulletNum(-1);
				}
			}
		}
	}
	//Plametサーチ。
	for (int i = 0; i < Planetnumber_Num; i++) {
		//対象がnullptrでなければ。
		if (Game::GetInstance()->memoryPP[i] != nullptr) {
			//対象との距離を測定。
			CVector3 kyori = Game::GetInstance()->memoryPP[i]->GetPosition() - position;
			//対象との距離がほぼ中心では吸収をやめる。
			if (radius * Searchment / 10 < kyori.Length() && kyori.Length() < radius * Searchment) {
				//対象との距離が一定以下になったら。
				if (kyori.Length() < radius * Searchment) {
					//Ｇ中心に遠ければ弱く、近ければ強く。
					float G = radius * Searchment - kyori.Length();
					//対象に渡す重力。kyoriにGをかけてG_limitarで制限調整して、反転（-1）すれば重力となる。
					Game::GetInstance()->memoryPP[i]->SetPosition(((kyori*G) / G_limitar)*-1);
					//対象との距離が中心に近くなったら。
					if (kyori.Length() < radius * Searchment / 5) {
						//破壊。
						Game::GetInstance()->memoryPP[i]->explosion();
					}
				}
			}
		}
	}
	//Starサーチ。
	QueryGOs<Star>("Star", [&](Star* star)->bool {
		CVector3 Kyori = star->GetPosition() - position;
		if (Kyori.Length() < radius * Searchment) {
			m_game->SetStarCount(-1);
			star->Death();
		}
		return true;
	});
	//Bulletサーチ。
	QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b) ->bool {
		//対象との距離を測定。
		CVector3 kyori = b->GetPosition() - position;
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

void BigBlackHole::Update()
{
	Gravity();
}
