#include "stdafx.h"
#include "Rocket.h"
#include "..\Player.h"
#include "..\Planet.h"
#include "..\Bullet.h"
#include "..\Game.h"
#include "SatelliteGene.h"
#include "RocketGene.h"
#include "Satellite.h"
#include "..\\Network\NPad.h"

const CVector2 Rocket::colliderSize = { 4989.508f, 1218.114f };
const CVector2 Rocket::colliderPosition = { 522.263f, 59.711f };

void Rocket::OnDestroy() {
	DeleteGO(m_modelRender);
	DeleteGO(arrowSprite);
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
		Game* game = Game::GetInstance();
		//星とぶつかったなら星を破壊。
		for (Planet* p : game->memoryPP) {
			if (p != nullptr) {
				HitResult result = collider.hitTest(p->GetPosition(), p->GetRadius());
				if (result.hit != NonHit) {
					p->explosion();
					if (awaking) {
						hp--;
					} else {
						Explosion();
						return;
					}
				}
			}
		}

		{//人工衛星との衝突
			Satellite* const* sateArray = game->getSatelliteGene()->getArray();
			for (int i = 0; i < SatelliteGene::getArrayNum(); i++) {
				Satellite* sate = sateArray[i];
				if (sate != nullptr) {
					HitResult result = collider.hitTest(sate->getCollider());
					if (result.hit != NonHit) {
						if (awaking) {
							prefab::CEffect* effect;
							effect = NewGO<prefab::CEffect>(0);
							//エフェクトを再生。
							effect->Play(L"effect/BigExplosion.efk");
							effect->SetScale({ 2, 2, 2 });
							effect->SetPosition(sateArray[i]->getPosition() + CVector3(0, 1000, 0));
							DeleteGO(sateArray[i]);
							hp--;
						} else {
							Explosion();
							return;
						}
					}
				}
			}
		}

		{//ロケット同士の衝突
			Rocket* const* rocketArray = game->getRocketGene()->getArray();
			for (int i = 0; i < RocketGene::getArrayNum(); i++) {
				Rocket* rocket = rocketArray[i];
				if (rocket != nullptr && rocket != this) {
					HitResult result = collider.hitTest(rocket->getCollider());
					if (result.hit != NonHit) {
						if (rocketArray[i]->isAwaking()) {
							rocketArray[i]->damage();
						} else {
							rocketArray[i]->Explosion();
						}
						if (awaking) {
							hp--;
						} else {
							Explosion();
							return;
						}
					}
				}
			}
		}

		//プレイヤーとの衝突
		for (Player* p : game->m_player) {
			if (p != nullptr) {
				if (!p->GetDeathCount() && !p->GetMuteki()) {
					HitResult result = collider.hitTest(p->GetPosition(), 800.0f);
					if (result.hit != NonHit) {
						Explosion();
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
				if (!awaking) {
					hp--;
					if (hp == 0) {
						awaking = true;
						m_modelRender->Init(L"modelData/Rocket.cmo");
						ownerNum = b->GetPB();
						InitArrow(ownerNum);
						hp = max_hp;
					}
				}
			}
			return true;
		});

		if (hp <= 0) {
			Explosion();
			return;
		}
	}

	float delta = GameTime().GetFrameDeltaTime();

	if (ownerNum >= 0) {
		CVector3 stick = {};
		stick.x = NPad(ownerNum).GetRStickXF();
		stick.z = NPad(ownerNum).GetRStickYF();

		if (stick.x == 0 && stick.z == 0) {
			stick = m_move;
		}
		stick.Normalize();

		ArrowUpdate(stick);

		/*CVector3 normal = m_move;
		normal.Normalize();
		m_move += normal * (controllPower / 5) * delta;*/

		m_move += stick * controllPower * delta;
		if (m_move.LengthSq() > controllPower*controllPower) {
			m_move.Normalize();
			m_move *= controllPower;
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

void Rocket::Explosion() {
	prefab::CEffect* effect;
	effect = NewGO<prefab::CEffect>(0);
	//エフェクトを再生。
	effect->Play(L"effect/BigExplosion.efk");
	//エフェクトに半径/（Ｍａｘと差）をかける
	effect->SetScale({1, 1, 1});
	effect->SetPosition(m_pos + CVector3(0,1000,0));

	DeleteGO(this);
}

void Rocket::InitArrow(int ownerNum) {
	arrowSprite = NewGO<prefab::CSpriteRender>(0);
	arrowSprite->Init(L"sprite/RocketArrow.dds", 50, 40);
	arrowSprite->SetPivot({ 0.0f, 0.5f });
	CVector4 color;
	switch (ownerNum) {
	case 0:
		color = { 1.0f, 0.0f, 0.0f, 1.0f };
		break;
	case 1:
		color = { 0.0f, 0.0f, 1.0f, 1.0f };
		break;
	case 2:
		color = { 0.1f, 1.0f, 0.0f, 1.0f };
		break;
	case 3:
		color = { 1.0f, 0.7f, 0.0f, 1.0f };
		break;
	}
	arrowSprite->SetMulColor(color);
}

void Rocket::ArrowUpdate(const CVector3& stick) {
	//回転させる
	CQuaternion rot;
	rot.SetRotation(CVector3::AxisZ, atan2f(stick.z, stick.x));
	arrowSprite->SetRotation(rot);

	//表示位置を調整する
	CVector3 arrowVec = { 40, 0, 0 };
	rot.Multiply(arrowVec);
	CVector2 pos;
	MainCamera().CalcScreenPositionFromWorldPosition(pos, m_pos);
	pos.x += arrowVec.x;
	pos.y += arrowVec.y;
	arrowSprite->SetPosition(CVector3(pos.x, pos.y, 0));
}
