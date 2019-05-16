#include "stdafx.h"
#include "Satellite.h"
#include "..\Bullet.h"
#include "..\Player.h"
#include "..\Planet.h"
#include "..\Game.h"
#include "CVector2.h"

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
	//エリア外判定
	if (m_pos.x > 30000.0f || m_pos.x< -30000.0f|| m_pos.z>20000.0f || m_pos.z < -20000.0f) {
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
					return;
				}
			}
		}

		//回転力を加える衝突判定。
		for (Player* p : Game::GetInstance()->m_player) {
			if (p != nullptr) {
				if (!p->GetDeathCount() && !p->GetMuteki()) {
					HitResult result = collider.hitTest(p->GetPosition(), 800.0f);
					if (result.hit == Side) {
						rotPower += result.rotSign * hitRotPower;
						p->AddHP(-100);
					}
				}
			}
		}

		QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b)->bool {
			HitResult result = collider.hitTest(b->GetPosition(), 0.1f);
			if (result.hit == Side) {
				rotPower += result.rotSign * hitRotPower;
				b->Death();
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

		//回転力を減衰させる。
		int sign = rotPower > 0 ? 1 : -1;//符号を出して0に近づくように減衰させる。
		rotPower -= sign * rotDamping;
		if (rotPower * sign <= 0) {//符号が減衰前と反転したら回転力を0にする。
			rotPower = 0;
		}
	}
}

void BoxCollider2D::Init(const CVector3 & pos, const CVector2& localCenter, CVector2 size) {
	size = size / 2;
	m_pos = CVector2(pos.x, pos.z);
	CVector2 local = m_pos + localCenter;
	for (int i = 0; i < 4; i++) {
		vertex[i] = local + size;
		switch (i) {
		case 0:
			size.y *= -1;
			break;
		case 1:
			size.x *= -1;
			break;
		case 2:
			size.y *= -1;
			break;
		}
	}
	for (int i = 0; i < 4; i++) {
		int next = i + 1;
		if (next == 4) {
			next = 0;
		}

		sideVec[i] = vertex[next] - vertex[i];
	}
}

HitResult BoxCollider2D::hitTest(const CVector3 & p, float radius) {
	bool hit = false;
	bool inSquere = true;//四角形内部にある判定。全ての辺が条件を満たさないといけない。

	CVector2 pos(p.x, p.z);
	for (int i = 0; i < 4; i++) {
		CVector2 toPosVec = pos - vertex[i];

		//直線との外積を求める
		float high = vec2Cross(sideVec[i], toPosVec);
		//四角形内部にいるか判定。
		if (inSquere && high > 0) {
			inSquere = false;
		}

		//外積を絶対値化して辺の長さで割って距離にする。
		if (high < 0) { high *= -1;}
		high /= vec2Length(sideVec[i]);

		//直線との距離が半径以下
		if (high < radius) {
			int next = i;
			if (next == 4) { next = 0; }
			CVector2 toPosVec2 = pos - vertex[next];

			//円の中心が線分の外側にある
			if (vec2Dot(sideVec[i], toPosVec) * vec2Dot(sideVec[i], toPosVec2) > 0) {

				//それでも線分の端を円の半径がとらえたらヒット
				if (radius >= vec2Length(toPosVec) || radius >= vec2Length(toPosVec2)) {
					hit = true;
				}
			} else {
				//線分の内側なら確実にヒット
				hit = true;
			}
		}
	}

	if (inSquere) { hit = true; }//内部にいればヒット

	HitResult result;

	if (!hit) {//ヒットしていない場合
		return result;
	}

	float dot = vec2Dot(shaft, pos - m_pos);

	if (abs(dot) < 1000.0f) {
		result.hit = Center;
		return result;
	}

	float cross = vec2Cross(shaft, pos - m_pos);
	bool minas = cross*dot < 0;

	result.hit = Side;

	if(minas) {
		result.rotSign = -1;
		return result;
	} else {
		result.rotSign = 1;
		return result;
	}
}

void BoxCollider2D::Rotate(CQuaternion rot) {
	//回転に利用するシャフトを回転させる。こいつは親基準。
	CVector3 shaft2(0, 0, 0);
	shaft2.x = shaft.x;
	shaft2.z = shaft.y;
	rot.Multiply(shaft2);
	shaft = { shaft2.x, shaft2.z };

	//頂点の回転。こいつはワールド基準なので一度原点に戻してから回す。
	for (int i = 0; i < 4; i++) {
		CVector3 pos(0,0,0);
		pos.x = vertex[i].x - m_pos.x;
		pos.z = vertex[i].y - m_pos.y;
		rot.Multiply(pos);
		pos.x += m_pos.x;
		pos.z += m_pos.y;
		vertex[i] = { pos.x, pos.z };
	}

	//時計回りのベクトルを算出しておく
	for (int i = 0; i < 4; i++) {
		int next = i + 1;
		if (next == 4) {
			next = 0;
		}

		sideVec[i] = vertex[next] - vertex[i];
	}
}

void BoxCollider2D::Move(CVector3 move) {
	m_pos.x += move.x;
	m_pos.y += move.z;
	for (int i = 0; i < 4; i++) {
		vertex[i].x += move.x;
		vertex[i].y += move.z;
	}
}