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

HitResult BoxCollider2D::hitTest(const CVector3 & p, float radius) {
	bool hit = false;
	bool inSquere = true;//�l�p�`�����ɂ��锻��B�S�Ă̕ӂ������𖞂����Ȃ��Ƃ����Ȃ��B

	CVector2 pos(p.x, p.z);
	for (int i = 0; i < 4; i++) {
		CVector2 toPosVec = pos - vertex[i];

		//�����Ƃ̊O�ς����߂�
		float high = vec2Cross(sideVec[i], toPosVec);
		//�l�p�`�����ɂ��邩����B
		if (inSquere && high > 0) {
			inSquere = false;
		}

		//�O�ς��Βl�����ĕӂ̒����Ŋ����ċ����ɂ���B
		if (high < 0) { high *= -1; }
		high /= vec2Length(sideVec[i]);

		//�����Ƃ̋��������a�ȉ�
		if (high < radius) {
			int next = i;
			if (next == 4) { next = 0; }
			CVector2 toPosVec2 = pos - vertex[next];

			//�~�̒��S�������̊O���ɂ���
			if (vec2Dot(sideVec[i], toPosVec) * vec2Dot(sideVec[i], toPosVec2) > 0) {

				//����ł������̒[���~�̔��a���Ƃ炦����q�b�g
				if (radius >= vec2Length(toPosVec) || radius >= vec2Length(toPosVec2)) {
					hit = true;
				}
			} else {
				//�����̓����Ȃ�m���Ƀq�b�g
				hit = true;
			}
		}
	}

	if (inSquere) { hit = true; }//�����ɂ���΃q�b�g

	HitResult result;

	if (!hit) {//�q�b�g���Ă��Ȃ��ꍇ
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

void BoxCollider2D::Rotate(CQuaternion rot) {
	//��]�ɗ��p����V���t�g����]������B�����͐e��B
	CVector3 shaft2(0, 0, 0);
	shaft2.x = shaft.x;
	shaft2.z = shaft.y;
	rot.Multiply(shaft2);
	shaft = { shaft2.x, shaft2.z };

	//���_�̉�]�B�����̓��[���h��Ȃ̂ň�x���_�ɖ߂��Ă���񂷁B
	for (int i = 0; i < 4; i++) {
		CVector3 pos(0, 0, 0);
		pos.x = vertex[i].x - m_pos.x;
		pos.z = vertex[i].y - m_pos.y;
		rot.Multiply(pos);
		pos.x += m_pos.x;
		pos.z += m_pos.y;
		vertex[i] = { pos.x, pos.z };
	}

	//���v���̃x�N�g�����Z�o���Ă���
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