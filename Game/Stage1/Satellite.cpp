#include "stdafx.h"
#include "Satellite.h"
#include "..\Bullet.h"
#include "..\Player.h"
#include "..\Planet.h"
#include "..\Game.h"
//#include "CVector2.h"
#include "..\Star.h"

const CVector2 Satellite::colliderSize = { 15797.811f, 2046.581f };
const CVector2 Satellite::colliderPosition = { 1868.701f ,112.663f };


Satellite::Satellite() {
}


Satellite::~Satellite() {
	DeleteGO(m_modelRender);
	*arrayP = nullptr;
}

bool Satellite::Start() {
	//モデルとコライダの初期化
	m_modelRender = NewGO<prefab::CSkinModelRender>(0);
	m_modelRender->Init(L"modelData/Satellite.cmo");
	m_modelRender->SetScale({ firstScale,firstScale, firstScale });
	collider.Init(m_pos, colliderPosition ,colliderSize);

	//動きの設定(ランダム)
	CQuaternion rot;
	rot.SetRotation(CVector3::AxisY, (float)Random().GetRandDouble() * CMath::PI2);
	rot.Multiply(m_move);

	//回転の設定(ランダム)
	rot.SetRotation(CVector3::AxisY, (float)Random().GetRandDouble() * CMath::PI2);
	m_rot = rot;
	collider.Rotate(rot);
	m_modelRender->SetRotation(rot);

	return true;
}

void Satellite::Update() {
	if (Game::GetInstance()->isWait())return;
	//エリア外判定
	if (m_pos.x > 35000.0f || m_pos.x< -35000.0f|| m_pos.z>25000.0f || m_pos.z < -25000.0f) {
		DeleteGO(this);
		return;
	}

	//生成時大きくなりながら登場
	if (firstScale < 1.0f) {
		firstScale += GameTime().GetFrameDeltaTime();
		if (firstScale > 1.0f) {
			firstScale = 1.0f;
		}
		m_modelRender->SetScale({ firstScale, firstScale, firstScale });

	} else
	//衝突判定
	{
		Game* game = Game::GetInstance();
		//星とぶつかったなら星を破壊。
		for (Planet* p : game->memoryPP) {
			if (p != nullptr) {
				HitResult result = collider.hitTest(p->GetPosition(), p->GetRadius());
				if (result.hit != NonHit) {
					p->explosion();
					return;
				}
			}
		}

		//プレイヤーとの衝突
		for (Player* p : game->m_player) {
			if (p != nullptr) {
				if (!p->GetDeathCount() && !p->GetMuteki()) {
					HitResult result = collider.hitTest(p->GetPosition(), 800.0f);
					if (result.hit == Side) {
						rotPower += result.rotSign * hitRotPower;
						p->AddHP(-100);
						lastBulletNum.playerLastBullet(p);
					} else if(result.hit == Center){
						m_move += p->GetMoveSpeed()*5;
						p->AddHP(-100);
						lastBulletNum.playerLastBullet(p);
					}
				}
			}
		}
		//弾との衝突


		QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b)->bool {
			HitResult result = collider.hitTest(b->GetPosition(), 0.1f);
			if (result.hit == Side) {
				rotPower += result.rotSign * hitRotPower;
				b->Death();
				prefab::CSoundSource* se = NewGO<prefab::CSoundSource>(0);
				lastBulletNum.pushBulletNum(b->GetPB());
				se->Init(L"sound/satellite.wav");
				se->SetVolume(0.2f);
				se->Play(false);
			} else if(result.hit == Center){
				m_move += b->GetMoveSpeed()*8;
				lastBulletNum.pushBulletNum(b->GetPB());
				b->Death();
				prefab::CSoundSource* se = NewGO<prefab::CSoundSource>(0);
				se->Init(L"sound/satellite.wav");
				se->SetVolume(0.2f);
				se->Play(false);
			}
			return true;
		});
	}

	//もろもろの更新
	{
		float delta = GameTime().GetFrameDeltaTime();
		//回転。最大値以上にはしない。
		if (rotPower > maxRot) {
			rotPower = maxRot;
		} else if (rotPower < -maxRot) {
			rotPower = -maxRot;
		}
		CQuaternion cq;
		cq.SetRotationDeg(CVector3::AxisY, rotPower*delta);
		m_rot.Multiply(cq);
		collider.Rotate(cq);
		m_modelRender->SetRotation(m_rot);

		//ポジションの更新
		m_pos += m_move * delta;
		collider.Move(m_move * delta);
		m_modelRender->SetPosition(m_pos);
		moveStar += m_move.Length() * delta;
		//スター生成
		if (moveStar > moveStarMax) {
			NewGO<Star>(0, "Star")->Pop(m_pos, {50,50,50});
			moveStar = 0.0f;
		}

		//回転力を減衰させる。
		int sign = rotPower > 0 ? 1 : -1;//符号を出して0に近づくように減衰させる。
		rotPower -= sign * rotDamping;
		if (rotPower * sign <= 0) {//符号が減衰前と反転したら回転力を0にする。
			rotPower = 0;
		}
	}
}

void NumArray::playerLastBullet(Player * p) {
	if (p->GetPadNum() != num[0]) {
		p->SetLABulletNum(num[0]);
	} else {
		p->SetLABulletNum(num[1]);
	}
}

void NumArray::pushBulletNum(int n) {
	if (n != num[0]) {
		num[1] = num[0];
		num[0] = n;
	}
}
