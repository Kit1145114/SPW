#include "stdafx.h"
#include "SatelliteGene.h"
#include "Satellite.h"
#include "..\Game.h"

SatelliteGene::~SatelliteGene() {
	for (Satellite* satP : satelliteArray) {
		DeleteGO(satP);
	}
}

void SatelliteGene::Update() {
	timer += GameTime().GetFrameDeltaTime();
	if (timer > interval) {
		timer = 0;

		//�����_���|�b�v�B
		CVector3 hako;
		int tryCount = 3;//�ꏊ�̒�ĂɎ��s���Ă��w��񐔕����s����
		while(tryCount > 0){
			hako.x = Random().GetRandDouble() - 0.5f;
			hako.z = Random().GetRandDouble() - 0.5f;

			//�����_����������ꏊ�̐����B
			const float PosLimitx = 30000.0f * 2;
			const float PosLimitz = 20000.0f * 2;
			hako.x *= PosLimitx;
			hako.z *= PosLimitz;

			Game* game = Game::GetInstance();
			//�v���C���[�̏�Ƀ|�b�v���Ȃ��悤��
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

		//�K���ȏꏊ���������Ă���ꍇ�A�l�H�q���𐶐�����B
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