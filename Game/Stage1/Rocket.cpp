#include "stdafx.h"
#include "Rocket.h"
#include "..\Player.h"
#include "..\Planet.h"
#include "..\Bullet.h"
#include "..\Game.h"
#include "..\\Network\NPad.h"

const CVector2 Rocket::colliderSize = { 4989.508f, 1218.114f };
const CVector2 Rocket::colliderPosition = { 522.263f, 59.711f };

Rocket::~Rocket() {
	DeleteGO(m_modelRender);
	*arrayP = nullptr;
}

bool Rocket::Start() {
	m_modelRender = NewGO<prefab::CSkinModelRender>(0);
	m_modelRender->Init(L"modelData/ScrapRocket.cmo");
	m_modelRender->SetPosition(m_pos);

	//コライダ
	collider.Init(m_pos, colliderPosition, colliderSize);

	//動きの設定(ランダム)
	CQuaternion rot;
	radianRot = (float)Random().GetRandDouble() * CMath::PI2;
	rot.SetRotation(CVector3::AxisY, radianRot);
	rot.Multiply(m_move);

	collider.Rotate(rot);
	m_modelRender->SetRotation(rot);
	return true;
}

void Rocket::Update() {
	//エリア外判定
	if (m_pos.x > 30000.0f || m_pos.x< -30000.0f || m_pos.z>20000.0f || m_pos.z < -20000.0f) {
		DeleteGO(this);
		return;
	}

	//衝突判定
	{
		//星とぶつかったなら星を破壊。
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

		//プレイヤーとの衝突
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
		//弾との衝突
		bool _return = false;
		QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b)->bool {
			HitResult result = collider.hitTest(b->GetPosition(), 0.1f);
			if (result.hit != NonHit) {
				b->Death();
				if (ownerNum != b->GetPB()) {
					hp--;
				}
				if (hp == 0) {
					if (!awaking) {
						awaking = true;
						m_modelRender->Init(L"modelData/Rocket.cmo");
						ownerNum = b->GetPB();
						hp = max_hp;
					} else {
						DeleteGO(this);
						_return = true;
						return false;
					}
				}
			}
			return true;
		});
		if (_return) { return; }
	}

	float delta = GameTime().GetFrameDeltaTime();

	if (ownerNum >= 0) {
		CVector3 stick = {};
		stick.x = NPad(ownerNum).GetRStickXF();
		stick.z = NPad(ownerNum).GetRStickYF();

		if (stick.LengthSq() < 0.2f) {
			CVector3 normal = m_move;
			normal.Normalize();
			m_move += normal * controllPower * delta;
		} else {
			m_move += stick * controllPower * delta;
		}
	}
	
	m_pos += m_move * delta;
	m_modelRender->SetPosition(m_pos);
	CQuaternion rot;
	float radian = atan2f(-m_move.z, m_move.x);
	rot.SetRotation(CVector3::AxisY, radian);
	m_modelRender->SetRotation(rot);
	
	rot.SetRotation(CVector3::AxisY, radian - radianRot);
	collider.Rotate(rot);
	collider.Move(m_move*delta);

	radianRot = radian;
}
