#include "stdafx.h"
#include "Rocket.h"
#include "..\Player.h"
#include "..\Planet.h"
#include "..\Bullet.h"
#include "..\Game.h"

Rocket::Rocket() {
}


Rocket::~Rocket() {
	DeleteGO(m_modelRender);
	*arrayP = nullptr;
}

bool Rocket::Start() {
	m_modelRender = NewGO<prefab::CSkinModelRender>(0);
	m_modelRender->Init(L"modelData/Rocket.cmo");
	m_modelRender->SetPosition(m_pos);

	//�����̐ݒ�(�����_��)
	CQuaternion rot;
	rot.SetRotation(CVector3::AxisY, (float)Random().GetRandDouble() * CMath::PI2);
	rot.Multiply(m_move);

	m_modelRender->SetRotation(rot);
	return true;
}

void Rocket::Update() {
	//�G���A�O����
	if (m_pos.x > 30000.0f || m_pos.x< -30000.0f || m_pos.z>20000.0f || m_pos.z < -20000.0f) {
		DeleteGO(this);
		return;
	}

	//�Փ˔���
	{
		//���ƂԂ������Ȃ琯��j��B
		for (Planet* p : Game::GetInstance()->memoryPP) {
			if (p != nullptr) {
				HitResult result = collider.hitTest(p->GetPosition(), p->GetRadius());
				if (result.hit != NonHit) {
					p->explosion();
					DeleteGO(this);
					return;
				}
			}
		}

		//�v���C���[�Ƃ̏Փ�
		for (Player* p : Game::GetInstance()->m_player) {
			if (p != nullptr) {
				if (!p->GetDeathCount() && !p->GetMuteki()) {
					HitResult result = collider.hitTest(p->GetPosition(), 800.0f);
					if (result.hit != NonHit) {
						DeleteGO(this);
						p->AddHP(-100);
						return;
					}
				}
			}
		}
		//�e�Ƃ̏Փ�
		QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b)->bool {
			HitResult result = collider.hitTest(b->GetPosition(), 0.1f);
			if (result.hit != NonHit) {
				/*if (!awaking || ) {

				}*/
				needBullet--;
				if (needBullet == 0) {
					if (!awaking) {
						awaking = true;
						ownerNum = b->GetPB();
					} else {
						DeleteGO(this);
						return;
					}
				}
			}
			return true;
		});
	}

	float delta = GameTime().GetFrameDeltaTime();
	m_pos += m_move * delta;
	m_modelRender->SetPosition(m_pos);
}
