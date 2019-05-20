#include "stdafx.h"
#include "BoxCollider2D.h"
#include "CVector2.h"

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

HitResult BoxCollider2D::hitTest(const CVector3 & p, float radius) const{
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
		if (high < 0) { high *= -1; }
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

	if (abs(dot) < 2000.0f) {
		result.hit = Center;
		return result;
	}

	float cross = vec2Cross(shaft, pos - m_pos);
	bool minas = cross * dot < 0;

	result.hit = Side;

	if (minas) {
		result.rotSign = -1;
		return result;
	} else {
		result.rotSign = 1;
		return result;
	}
}

bool isCrossLine(const CVector2& line1p1, const CVector2& line1p2,
				 const CVector2& line2p1, const CVector2& line2p2) {
	const CVector2* l1p1 = &line1p1;
	const CVector2* l1p2 = &line1p2;
	const CVector2* l2p1 = &line2p1;
	const CVector2* l2p2 = &line2p2;

	//x1~y2には直線の2点の座標。x,yに線分の2点のうち1点の座標で答えを出し、もう片方の点でも答えを出す。
	//(x1-x2)*(y - y1) + (y1-y2)*(x1-x) = ？
	//2つの答えの積がマイナスなら直線と線分は重なっている。
	//線分と線分が重なっているか調べるため、直線と線分を入れ替えてもう一度同じことをやる。

	bool cross = false;

	for (int i = 0; i < 2; i++) {
		float ans1 = (l1p1->x - l1p2->x)*(l2p1->y - l1p1->y) + (l1p1->y - l1p2->y)*(l1p1->x - l2p1->x);
		float ans2 = (l1p1->x - l1p2->x)*(l2p2->y - l1p1->y) + (l1p1->y - l1p2->y)*(l1p1->x - l2p2->x);

		if (ans1*ans2 <= 0) {
			if (i == 0) {
				const CVector2* swapP;
				swapP = l1p1;
				l1p1 = l2p1;
				l2p1 = swapP;

				swapP = l1p2;
				l1p2 = l2p2;
				l2p2 = swapP;
			} else {
				cross = true;
			}
		} else {
			break;
		}
	}
	return cross;
}

HitResult BoxCollider2D::hitTest(const BoxCollider2D* box) const{
	bool hit = false;
	for (int i = 0; i < 4; i++) {
		int nextI = i + 1;
		if (nextI == 4) { nextI = 0; }

		const CVector2& iVer1 = vertex[i];
		const CVector2& iVer2 = vertex[nextI];
		//(x1-x2)*(y - y1) + (y1-y2)*(x1-x) = ?

		for (int j = 0; j < 4; j++) {
			int nextJ = j + 1;
			if (nextJ == 4) { nextJ = 0; }

			const CVector2* targV = box->getVertexArray();
			if (isCrossLine(iVer1, iVer2, targV[j], targV[nextJ])) {
				hit = true;
				goto LOOP_BREAK;
			}
		}

	}
LOOP_BREAK:

	HitResult result;

	if (!hit) {//ヒットしていない場合
		return result;
	}

	float dot = vec2Dot(shaft, box->getPos() - m_pos);

	if (abs(dot) < 2000.0f) {
		result.hit = Center;
		return result;
	}

	float cross = vec2Cross(shaft, box->getPos() - m_pos);
	bool minas = cross * dot < 0;

	result.hit = Side;

	if (minas) {
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
		CVector3 pos(0, 0, 0);
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