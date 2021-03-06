#include "stdafx.h"
#include "RocketGene.h"
#include "Rocket.h"
#include "..\Planet.h"
#include "..\Game.h"

void RocketGene::OnDestroy() {
	for (Rocket* satP : rocketArray) {
		DeleteGO(satP);
	}
}

void RocketGene::Update() {
	if (Game::GetInstance()->isWait())return;
	timer += GameTime().GetFrameDeltaTime();
	if (timer > interval) {
		timer = 0;

		//ランダムポップ。
		CVector3 hako;
		int tryCount = 5;//場所の提案に失敗しても指定回数分試行する
		while (tryCount > 0) {
			hako.x = Random().GetRandDouble() - 0.5f;
			hako.z = Random().GetRandDouble() - 0.5f;

			//ランダム生成する場所の制限。
			const float PosLimitx = 25000.0f * 2;
			const float PosLimitz = 15000.0f * 2;
			hako.x *= PosLimitx;
			hako.z *= PosLimitz;

			Game* game = Game::GetInstance();
			//プレイヤーの上にポップしないように
			for (int j = 0; j < game->GetSansenKazu(); j++) {
				float kyori = (game->m_player[j]->GetPosition() - hako).LengthSq();
				const float needKyori = 800.0f + 2500.0f + 1000.0f;//プレイヤー半径＋ロケット半径＋予備
				if (kyori < needKyori*needKyori) {
					tryCount--;
					goto LOOP_CONTINUE;
				}
			}

			//ロケットの上にポップしないように
			for (Rocket* rocket : rocketArray) {
				if (rocket != nullptr) {
					float kyori = (rocket->getPosition() - hako).LengthSq();
					const float needKyori = 5000.0f;
					if (kyori < needKyori*needKyori) {
						tryCount--;
						goto LOOP_CONTINUE;
					}
				}
			}

			//星の上にポップしないように
			for (Planet* p : game->memoryPP) {
				if (p != nullptr) {
					float kyori = (p->GetPosition() - hako).LengthSq();
					const float needKyori = p->GetRadius() + 2500.0f;
					if (kyori < needKyori*needKyori) {
						tryCount--;
						goto LOOP_CONTINUE;
					}
				}
			}
			break;
		LOOP_CONTINUE:;
		}

		//適当な場所が見つかっている場合、ロケットを生成する。
		if (tryCount > 0) {
			for (Rocket*& satP : rocketArray) {
				if (satP == nullptr) {
					satP = NewGO<Rocket>(0, "Rocket");
					satP->setPosition(hako);
					satP->setArrayPointer(&satP);
					break;
				}
			}
		}
	}
}

