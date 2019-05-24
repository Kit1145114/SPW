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
	if (Game::GetInstance()->isWaitStart())return;
	timer += GameTime().GetFrameDeltaTime();
	if (timer > interval) {
		timer = 0;

		//�����_���|�b�v�B
		CVector3 hako;
		int tryCount = 5;//�ꏊ�̒�ĂɎ��s���Ă��w��񐔕����s����
		while (tryCount > 0) {
			hako.x = Random().GetRandDouble() - 0.5f;
			hako.z = Random().GetRandDouble() - 0.5f;

			//�����_����������ꏊ�̐����B
			const float PosLimitx = 25000.0f * 2;
			const float PosLimitz = 15000.0f * 2;
			hako.x *= PosLimitx;
			hako.z *= PosLimitz;

			Game* game = Game::GetInstance();
			//�v���C���[�̏�Ƀ|�b�v���Ȃ��悤��
			for (int j = 0; j < game->GetSansenKazu(); j++) {
				float kyori = (game->m_player[j]->GetPosition() - hako).LengthSq();
				const float needKyori = 800.0f + 2500.0f + 1000.0f;//�v���C���[���a�{���P�b�g���a�{�\��
				if (kyori < needKyori*needKyori) {
					tryCount--;
					goto LOOP_CONTINUE;
				}
			}

			//���P�b�g�̏�Ƀ|�b�v���Ȃ��悤��
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

			//���̏�Ƀ|�b�v���Ȃ��悤��
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

		//�K���ȏꏊ���������Ă���ꍇ�A���P�b�g�𐶐�����B
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

