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
	//
	effect->SetEffectFlag(true);
	return true;
}

void BigBlackHole::Generate()
{
	BigBlackHole* bh = NewGO<BigBlackHole>(0, "BBH");
}

void BigBlackHole::Gravity()
{
	
	//Playerサーチ。
	for (int i = 0; i < Game::GetInstance()->GetSansenKazu(); i++) {
		//プレイヤーが無敵なら吸収をやめる。
		if (Game::GetInstance()->m_player[i]->GetMuteki() == false) {
			//対象との距離を測定。
			CVector3 kyori = Game::GetInstance()->m_player[i]->GetPosition() - position;
			
					//BBH特別Ｇ 5倍の距離をサーチする。
					if (kyori.Length() <= radius * Searchment * BBHSearchment) {
						//Ｇ中心に遠ければ弱く、近ければ強く。
						float BigG = radius * Searchment * BBHSearchment - kyori.Length();
						//対象に渡す重力。kyoriにGをかけてG_limitarで制限調整して、反転（-1）すれば重力となる。
						BBHG_limitar = { 500.0f };//   BBHの重力（Ｇ）調整。
						CVector3 Migawari = kyori;
						Migawari.Normalize();
						BigG = BigG * BigG / BBHnizyou;
						Game::GetInstance()->m_player[i]->SetMoveSpeed(((Migawari * BigG) / BBHG_limitar)*-1);
					}
					
					if (kyori.Length() < radius * Searchment) {
						//Ｇ中心に遠ければ弱く、近ければ強く。
						float G = radius * Searchment - kyori.Length();
						//対象に渡す重力。kyoriにGをかけてG_limitarで制限調整して、反転（-1）すれば重力となる。
						Game::GetInstance()->m_player[i]->SetMoveSpeed(((kyori*G) / G_limitar)*-1);
						//	//対象との距離が中心に近くなったら。
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
			
			//BBH特別Ｇ 5倍の距離をサーチする。
			if (kyori.Length() <= radius * Searchment * BBHSearchment) {
				//Ｇ中心に遠ければ弱く、近ければ強く。
				float BigG = radius * Searchment * BBHSearchment - kyori.Length();
				//対象に渡す重力。kyoriにGをかけてG_limitarで制限調整して、反転（-1）すれば重力となる。
				BBHG_limitar = { 500.0f };//   BBHの重力（Ｇ）調整。
				CVector3 Migawari = kyori;
				Migawari.Normalize();
				BigG = BigG * BigG / BBHnizyou;
				Game::GetInstance()->memoryPP[i]->SetMoveSpeed(((Migawari * BigG) / BBHG_limitar)*-1);
			}
			//対象との距離が一定以下になったら。
			if (kyori.Length() < radius * Searchment) {
				//Ｇ中心に遠ければ弱く、近ければ強く。
				float G = radius * Searchment - kyori.Length();
				//対象に渡す重力。kyoriにGをかけてG_limitarで制限調整して、反転（-1）すれば重力となる。
				Game::GetInstance()->memoryPP[i]->SetMoveSpeed(((kyori*G) / G_limitar)*-1);
				//対象との距離が中心に近くなったら。
				if (kyori.Length() < radius * Searchment / 5) {
					//破壊。
					Game::GetInstance()->memoryPP[i]->explosion();
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
		//BBH特別Ｇ 5倍の距離をサーチする。
		if (kyori.Length() <= radius * Searchment * BBHSearchment) {
			//Ｇ中心に遠ければ弱く、近ければ強く。
			float BigG = radius * Searchment * BBHSearchment - kyori.Length();
			//対象に渡す重力。kyoriにGをかけてG_limitarで制限調整して、反転（-1）すれば重力となる。
			BBHG_limitar = { 6000.0f };//   BBHの重力（Ｇ）調整。
			CVector3 Migawari = kyori;
			Migawari.Normalize();
			BigG = BigG * BigG / BBHnizyou;
			b->SetMoveSpeed(((Migawari * BigG) / BBHG_limitar)*-1);
		}
		//対象との距離がeffect以下になったら。
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
