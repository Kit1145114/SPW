#include "stdafx.h"
#include "SatelliteGene.h"
#include "Satellite.h"
#include "..\Game.h"

void SatelliteGene::OnDestroy() {
	for (Satellite* satP : satelliteArray) {
		DeleteGO(satP);
	}
}

void SatelliteGene::Update() {
	timer += GameTime().GetFrameDeltaTime();
	if (timer > interval) {
		timer = 0;

		//ランダムポップ。
		CVector3 hako;
		int tryCount = 6;//場所の提案に失敗しても指定回数分試行する
		while(tryCount > 0){
			hako.x = Random().GetRandDouble() - 0.5f;
			hako.z = Random().GetRandDouble() - 0.5f;

			//ランダム生成する場所の制限。
			const float PosLimitx = 20000.0f * 2;
			const float PosLimitz = 10000.0f * 2;
			hako.x *= PosLimitx;
			hako.z *= PosLimitz;

			Game* game = Game::GetInstance();
			//プレイヤーの上にポップしないように
			for (int j = 0; j < game->GetSansenKazu(); j++) {
				float kyori = (game->m_player[j]->GetPosition() - hako).LengthSq();
				const float needKyori = 15000.0f;
				if (kyori < needKyori*needKyori) {
					tryCount--;
					goto LOOP_CONTINUE;
				}
			}

			for (Satellite* sate : satelliteArray) {
				if (sate != nullptr) {
					float kyori = (sate->getPosition() - hako).LengthSq();
					const float needKyori = 7000.0f;
					if (kyori < needKyori*needKyori) {
						tryCount--;
						goto LOOP_CONTINUE;
					}
				}
			}

			break;
		LOOP_CONTINUE:;
		}

		//適当な場所が見つかっている場合、人工衛星を生成する。
		if (tryCount > 0) {
			for (Satellite*& satP : satelliteArray) {
				if (satP == nullptr) {
					satP = NewGO<Satellite>(0, "Satellite");
					satP->setPosition(hako);
					satP->setArrayPointer(&satP);
					break;
				}
			}
		}
	}
}
