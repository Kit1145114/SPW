#include "stdafx.h"
#include "RocketGene.h"
#include "Rocket.h"
#include "..\Game.h"

void RocketGene::OnDestroy() {
	for (Rocket* satP : RocketArray) {
		DeleteGO(satP);
	}
}

void RocketGene::Update() {
	timer += GameTime().GetFrameDeltaTime();
	if (timer > interval) {
		timer = 0;

		//ランダムポップ。
		CVector3 hako;
		int tryCount = 3;//場所の提案に失敗しても指定回数分試行する
		while (tryCount > 0) {
			hako.x = Random().GetRandDouble() - 0.5f;
			hako.z = Random().GetRandDouble() - 0.5f;

			//ランダム生成する場所の制限。
			const float PosLimitx = 30000.0f * 2;
			const float PosLimitz = 20000.0f * 2;
			hako.x *= PosLimitx;
			hako.z *= PosLimitz;

			Game* game = Game::GetInstance();
			//プレイヤーの上にポップしないように
			for (int j = 0; j < game->GetSansenKazu(); j++) {
				float kyori = (game->m_player[j]->GetPosition() - hako).LengthSq();
				const float needKyori = 800.0f + 10000.0f;
				if (kyori < needKyori*needKyori) {
					tryCount--;
					continue;
				}
			}
			break;
		}

		//適当な場所が見つかっている場合、人工衛星を生成する。
		if (tryCount > 0) {
			for (Rocket*& satP : RocketArray) {
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

