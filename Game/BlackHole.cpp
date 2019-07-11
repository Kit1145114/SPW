#include "stdafx.h"
#include "BlackHole.h"
#include "Star.h"

BlackHole::BlackHole()
{
}

BlackHole::~BlackHole()
{
	if (effect != nullptr) {
		DeleteGO(effect);
	}
}

bool BlackHole::Start()
{
	//シングルトンでアクセスするため。
	m_game = Game::GetInstance();

	//エフェクトを作成。
	effect = NewGO<prefab::CEffect>(0);
	//エフェクトを再生。
	effect->Play(L"effect/BH.efk");
	scale = { 0.1f,0.1f,0.1f };
	//BHの大きさはぶつかった惑星の大きさに比例させる。
	effect->SetScale(scale*radius);
	effect->SetPosition(m_position);
	//BHカウントしておく。
	Game::GetInstance()->SetBHCount(1);
	effect->SetEffectFlag(true);
	return true;
}

void BlackHole::Generate(CVector3 position, float magnification)
{
	BlackHole* bh = NewGO<BlackHole>(0, "BlackHole");
	//保存。
	//BH発生場所の受け渡し。
	bh->m_position = position;
	//BHの大きさはぶつかった惑星の大きさに比例させる。
	bh->radius *= magnification / 500;
}

void BlackHole::Gravity()
{

	//Playerサーチ。
	for (int i = 0; i < Game::GetInstance()->GetSansenKazu(); i++) {
		//プレイヤーが無敵なら吸収をやめる。
		if (Game::GetInstance()->m_player[i]->GetMuteki() == false) {
			//対象との距離を測定。
			CVector3 kyori = Game::GetInstance()->m_player[i]->GetPosition() - m_position;
			//対象との距離が一定以下になったら。
			if (kyori.Length() < radius * Searchment * 1.2) {
				//BH中心と対象との距離。
				float G = radius * Searchment - kyori.Length();
				//BHの重力（Ｇ）調整。
				G_limitar = { 50.0f };
				//ベクトルの向き。
				CVector3 kyori2 = kyori;
				kyori2.Normalize();
				//対象との距離を二乗することで　Ｇ中心に遠ければ弱く、近ければ強く。
				G = G * G / BBHnizyou;
				//プレイヤーへ渡すベクトル。
				//kyori2 * G　(向き*Ｇ) / G_limitar (重力の調整)* -1 (反転すれば中心へと向かう重力となる)。
				Game::GetInstance()->m_player[i]->SetMoveSpeed(((kyori2 * G) / G_limitar) * -1);
				//対象との距離が中心に近くなったら。
				if (kyori.Length() < radius * Searchment / 5) {
					//破壊。
					Game::GetInstance()->m_player[i]->AddHP(-100);
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
			CVector3 kyori = Game::GetInstance()->memoryPP[i]->GetPosition() - m_position;
			//対象との距離が一定以下になったら。
			if (kyori.Length() < radius * Searchment) {
				//BH中心と対象との距離。
				float G = radius * Searchment - kyori.Length();
				//BHの重力（Ｇ）調整。
				G_limitar = { 100.0f };
				//ベクトルの向き。
				CVector3 kyori2 = kyori;
				kyori2.Normalize();
				//対象との距離を二乗することで　Ｇ中心に遠ければ弱く、近ければ強く。
				G = G * G / BBHnizyou;
				// プレイヤーへ渡すベクトル。
				//kyori2 * G　(向き*Ｇ) / G_limitar (重力の調整)*-1(反転すれば中心へと向かう重力となる)。
				Game::GetInstance()->memoryPP[i]->SetMoveSpeed(((kyori2 * G) / G_limitar) * -1);
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
		//対象との距離を測定。
		CVector3 Kyori = star->GetPosition() - m_position;
		//対象との距離が一定以下になったら。
		if (Kyori.Length() < radius * Searchment) {
			//破壊。
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
			//BH中心と対象との距離。
			float G = radius * Searchment - kyori.Length();
			//BHの重力（Ｇ）調整。
			G_limitar = { 100.0f };
			//ベクトルの向き。
			CVector3 kyori2 = kyori;
			kyori2.Normalize();
			//対象との距離を二乗することで　Ｇ中心に遠ければ弱く、近ければ強く。
			G = G * G / BBHnizyou;
			//対象へ渡すベクトル。
			//kyori2 * G　(向き*Ｇ) / G_limitar (重力の調整)*-1(反転すれば中心へと向かう重力となる)。
			b->SetMoveSpeed(((kyori2 * G) / G_limitar) * -1);
		}
		return true;
	});
	//メテオサーチ。
	QueryGOs<Meteo>("Meteo", [&](Meteo* m) ->bool {
		//対象との距離を測定。
		CVector3 kyori = m->GetPosition() - m_position;
		//対象との距離が一定以下になったら。
		if (kyori.Length() < radius * Searchment) {
			//BH中心と対象との距離。
			float G = radius * Searchment - kyori.Length();
			//BHの重力（Ｇ）調整。
			G_limitar = { 600.0f };
			//ベクトルの向き。
			CVector3 kyori2 = kyori;
			kyori2.Normalize();
			//対象との距離を二乗することで　Ｇ中心に遠ければ弱く、近ければ強く。
			G = G * G / BBHnizyou;
			//対象へ渡すベクトル。
			//kyori2 * G　(向き*Ｇ) / G_limitar (重力の調整)*-1(反転すれば中心へと向かう重力となる)。
			m->SetMoveSpeed(((kyori2 * G) / G_limitar) * -1);
			if (kyori.Length() < radius * Searchment / 5) {
				//破壊。
				m->Death();
			}
		}
		return true;
	});
}

void BlackHole::Count()
{
	if (Countflg == false) {
		timer += GameTime().GetFrameDeltaTime();
		//BH発生から一定時間経過後。
		if (timer > Deathtime) {
			//BH消滅。
			DeathSize();
		}
	}
}

void BlackHole::Death()
{
	DeleteGO(this);
	//自分のカウントを減らす。
	Game::GetInstance()->SetBHCount(-1);
}

void BlackHole::PopSize()
{
	if (scale.x <= 1.0f
		&&timer < 8.0f) {
		//毎フレーム0.01ｆづつ大きくなる。
		scale += { 0.01f, 0.01f, 0.01f };
		effect->SetScale(scale*radius);
	}
}
void BlackHole::DeathSize() {

	if (scale.x >= 0.2f) {
		//毎フレーム0.01ｆづつ小さくなる。
		scale -= { 0.01f, 0.01f, 0.01f };
		effect->SetScale(scale*radius);
	}
	//scale.x >= 0.2fになったら。
	else {
		//破壊。
		Death();
	}

}

void BlackHole::Update()
{
	//カウントなどは処理の停止。
	if (Game::GetInstance()->isWait())return;
	PopSize();
	Gravity();
	Count();
}
