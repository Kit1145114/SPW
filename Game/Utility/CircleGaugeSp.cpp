#include "stdafx.h"
#include "CircleGaugeSp.h"

template<class T, std::size_t N>
int arraySize(const T(&)[N]) {
	return N;
}

int getSign(float num) {
	if (num > 0) {
		return 1;
	} else if (num < 0){
		return -1;
	} else {
		return 0;
	}
}

void CircleGaugeSp::Init(CShaderResourceView & tex, float w, float h, bool clockwise_) {
	//�V�F�[�_�[���[�h�B
	m_ps.Load("shader/sprite.fx", "PSMain", CShader::EnType::PS);
	m_vs.Load("shader/sprite.fx", "VSMain", CShader::EnType::VS);
	m_size.x = w;
	m_size.y = h;
	float halfW = w * 0.5f;
	float halfH = h * 0.5f;

	clockwise = clockwise_;

	//���_�o�b�t�@�̃\�[�X�f�[�^�B
	vertices[0] = {//�����v���̂Ƃ���ԍŏ��ɓ������_�B(�����łȂ���Γ����Ȃ�)
			CVector4(0.0f , halfH, 0.0f, 1.0f),
			CVector2(0.5f, 0.0f)
	};
	vertices[1] = {//�E��
			CVector4(halfW, halfH, 0.0f, 1.0f),
			CVector2(1.0f, 0.0f)
	};
	vertices[2] = {//�E��
			CVector4(halfW, -halfH, 0.0f, 1.0f),
			CVector2(1.0f, 1.0f),
	};
	vertices[3] = {//����
			CVector4(-halfW, -halfH, 0.0f, 1.0f),
			CVector2(0.0f, 1.0f),
	};
	vertices[4] = {//����
			CVector4(-halfW, halfH, 0.0f, 1.0f),
			CVector2(0.0f, 0.0f)
	};
	vertices[5] = {//���v���̂Ƃ���ԍŏ��ɓ������_�B(�����łȂ���Γ����Ȃ�)
			CVector4(0.0f , halfH, 0.0f, 1.0f),
			CVector2(0.5f, 0.0f)
	};
	vertices[6] = {//���S�̒��_(�����Ȃ�)
			CVector4(0.0f, 0.0f, 0.0f, 1.0f),
			CVector2(0.5f, 0.5f)
	};
	
	short indices[] = { 5,4,6, 4,3,6, 3,2,6, 2,1,6, 1,0,6 };

	m_primitive.Create(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		arraySize(vertices),
		sizeof(SSimpleVertex),
		vertices,
		arraySize(indices),
		CIndexBuffer::enIndexType_16,
		indices
	);
	m_textureSRV = &tex;
	m_cb.Create(nullptr, sizeof(SSpriteCB));
	m_isInited = true;
}

void CircleGaugeSp::setFillAmount(float amount) {
	//���炷�����ɍl���邽��1�������
	float reduce = 1 - amount;
	if (reduce < 0) {
		reduce = 0;
	} else if (reduce > 1) {
		reduce = 1;
	}

	float radian = reduce * CMath::PI2;
	int moveVCount = 1;
	{
		//�ŏ��̒��_��45�x���������Ȃ��̂ł�����܂�����
		float countRad = radian - (CMath::PI / 4);
		//countRad��0���傫��(�ړ��ʂ�45�x���傫��)�ꍇ�A���������_��1�v���X
		//�ȍ~90�x���Ƃ�1�v���X���Ă���
		for (; countRad > 0.0f; countRad -= CMath::PI / 2) {
			moveVCount += 1;
		}
	}

	float xORy;
	{
		//���a���`��钼�p�O�p�`�̊p�x�����߂�B����͒��S�ɋ߂��p�B
		float rAngle = radian;
		while (rAngle > CMath::PI / 2) {//90�x�Ŋ������]��
			rAngle -= CMath::PI / 2;
		}
		if (rAngle > CMath::PI / 4) {//45�x�𒴂����甽�]����
			rAngle = CMath::PI / 2 - rAngle;
		}

		//�������Ă��Ȃ������p�x
		float kakudo = CMath::PI - rAngle - (CMath::PI / 2);

		//�����藝�̒��p�O�p�`���Ȃ��O�ډ~�̒��a
		float r2 = 1 / sinf(kakudo);
		//�������璼�p�O�p�`��x���W��y���W�Ƃ��Ďg���邠�����̕ӂ����߂�B
		xORy = r2 * sinf(rAngle);

	}

	CVector4 pos(m_size.x / 2, m_size.y / 2, 0.0f, 1.0f);
	CVector2 tex;

	int clockSign = clockwise ? -1 : 1;

	//��]�̃X�^�[�g��y���ォ��Ȃ̂�y���W��cos�ŁAx���W��sin�ŋ��߂�B
	//�e�N�X�`�����W�ł͏オ�O�ŉ����P�Ȃ̂ŃR�T�C���̌v�Z�Ƀ}�C�i�X�������邱�ƂŔ��]������B
	if (moveVCount % 2 == 0) {
		//moveVCount�������̏ꍇ�A���_�͏c�����̕ӏ�ɂ���̂�x���W�͉E�����������l����΂悢�B
		pos.x *= getSign( sinf(radian) ) * clockSign;
		pos.y *= xORy * getSign(cosf(radian));

		tex.x = getSign(sinf(radian)) * 0.5f * clockSign + 0.5f;
		tex.y = xORy* -getSign(cosf(radian)) * 0.5f + 0.5f;
	} else {
		//moveVCount����̏ꍇ�A���_�͉������̕ӏ�ɂ���̂�y���W�͏ォ���������l����΂悢�B
		pos.x *= xORy * getSign(sinf(radian)) * clockSign;
		pos.y *= getSign( cosf(radian) );

		tex.x = xORy * getSign(sinf(radian)) *0.5f * clockSign + 0.5f;
		tex.y = -getSign(cosf(radian)) * 0.5f + 0.5f;
	}

	//���������_�ɂ͌v�Z�������_���A����ȊO�͌��̒��_������
	SSimpleVertex movedVer[vNum];
	for (int roopi = 0; roopi < vNum; roopi++) {
		int i = roopi;
		if (clockwise && i < 6) {
			i = 5 - i;
		}

		if (roopi < moveVCount) {
			movedVer[i] = {pos, tex};
		} else {
			movedVer[i] = vertices[i];
		}
	}

	//���_�o�b�t�@�A�b�v�f�[�g
	CRenderContext& rc = Engine().GetGraphicsEngine().GetRenderContext();
	CVertexBuffer& vBuffer = m_primitive.GetVertexBuffer();

	rc.UpdateSubresource(vBuffer, movedVer);
}
