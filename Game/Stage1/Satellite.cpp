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
}

bool Satellite::Start() {
	for (prefab::CSkinModelRender*&t : tester) {
		t = NewGO<prefab::CSkinModelRender>(0);
		t->Init(L"modelData/Bulet.cmo");
		t->SetScale({ 5,5,5 });
	}
	testshaft = NewGO<prefab::CSkinModelRender>(0);
	testshaft->Init(L"modelData/Bullet2.cmo");
	testshaft->SetScale({ 5,5,5 });

	m_modelRender = NewGO<prefab::CSkinModelRender>(0);
	m_modelRender->Init(L"modelData/Satellite.cmo");
	collider.Init(m_pos, colliderPosition ,colliderSize);
	return true;
}

void Satellite::Update() {
	for(Player* p : Game::GetInstance()->m_player) {
		if (p != nullptr) {
			rotPower += collider.hitTest(p->GetPosition(), 800.0f);
		}
	}
	CQuaternion cq;
	cq.SetRotationDeg(CVector3::AxisY, rotPower*0.0001f);
	rot.Multiply(cq);
	collider.Rotate(cq);
	m_modelRender->SetRotation(rot);
	m_modelRender->SetPosition(m_pos);

	rotPower -= 100.0f;
	if (rotPower < 0) {
		rotPower = 0.0f;
	}

	for (int i = 0; i < 4; i++) {
		CVector3 p(0, 1000, 0);
		p.x = collider.vertex[i].x;
		p.z = collider.vertex[i].y;
		tester[i]->SetPosition(p);
	}
	CVector3 p(0, 0, 0);
	p.x = collider.shaft.x;
	p.z = collider.shaft.y;
	p *= 3000;
	p.y = 2000;
	testshaft->SetPosition(m_pos+p);
}

void BoxCollider2D::Init(const CVector3 & pos, const CVector2& localCenter, CVector2 size) {
	size = size / 2;
	m_pos = CVector2(pos.x, pos.z);
	CVector2 local = m_pos + localCenter;
	for (int i = 0; i < 4; i++) {
		vertex[i] = local + size;
		switch (i) {
		case 0:
			size.x *= -1;
			break;
		case 1:
			size.y *= -1;
			break;
		case 2:
			size.x *= -1;
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

float vec2Dot(const CVector2& v1, const CVector2& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y);
}

float vec2Cross(const CVector2& v1, const CVector2& v2) {
	return (v1.x * v2.y) - (v2.x * v1.y);
}

float vec2Length(const CVector2& v) {
	return sqrt(v.x*v.x + v.y*v.y);
}

float BoxCollider2D::hitTest(const CVector3 & p, float radius) {
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
				if (radius <= vec2Length(toPosVec) || radius <= vec2Length(toPosVec2)) {
					hit = true;
				}
			} else {
				//線分の内側なら確実にヒット
				hit = true;
			}
		}
	}

	if (inSquere) { hit = true; }//内部にいればヒット

	if (!hit) {
		return 0;
	}

	float dot = vec2Dot(shaft, pos - m_pos);
	float cross = vec2Cross(shaft, pos - m_pos);
	bool minas = cross*dot < 0;
	
	if (dot < 0) {
		dot *= -1;
	}

	if(minas) {
		return -dot;
	} else {
		return dot;
	}
}

void BoxCollider2D::Rotate(CQuaternion rot) {
	CVector3 shaft2(0, 0, 0);
	shaft2.x = shaft.x;
	shaft2.z = shaft.y;
	rot.Multiply(shaft2);
	shaft = { shaft2.x, shaft2.z };

	for (int i = 0; i < 4; i++) {
		CVector3 pos(0,0,0);
		pos.x = vertex[i].x - m_pos.x;
		pos.z = vertex[i].y - m_pos.y;
		rot.Multiply(pos);
		vertex[i] = { pos.x, pos.z };
	}

	for (int i = 0; i < 4; i++) {
		int next = i + 1;
		if (next == 4) {
			next = 0;
		}

		sideVec[i] = vertex[next] - vertex[i];
	}
}
