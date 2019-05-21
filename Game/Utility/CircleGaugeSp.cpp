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
	//シェーダーロード。
	m_ps.Load("shader/sprite.fx", "PSMain", CShader::EnType::PS);
	m_vs.Load("shader/sprite.fx", "VSMain", CShader::EnType::VS);
	m_size.x = w;
	m_size.y = h;
	float halfW = w * 0.5f;
	float halfH = h * 0.5f;

	clockwise = clockwise_;

	//頂点バッファのソースデータ。
	vertices[0] = {//反時計回りのとき一番最初に動く頂点。(そうでなければ動かない)
			CVector4(0.0f , halfH, 0.0f, 1.0f),
			CVector2(0.5f, 0.0f)
	};
	vertices[1] = {//右上
			CVector4(halfW, halfH, 0.0f, 1.0f),
			CVector2(1.0f, 0.0f)
	};
	vertices[2] = {//右下
			CVector4(halfW, -halfH, 0.0f, 1.0f),
			CVector2(1.0f, 1.0f),
	};
	vertices[3] = {//左下
			CVector4(-halfW, -halfH, 0.0f, 1.0f),
			CVector2(0.0f, 1.0f),
	};
	vertices[4] = {//左上
			CVector4(-halfW, halfH, 0.0f, 1.0f),
			CVector2(0.0f, 0.0f)
	};
	vertices[5] = {//時計回りのとき一番最初に動く頂点。(そうでなければ動かない)
			CVector4(0.0f , halfH, 0.0f, 1.0f),
			CVector2(0.5f, 0.0f)
	};
	vertices[6] = {//中心の頂点(動かない)
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
	//減らす方向に考えるため1から引く
	float reduce = 1 - amount;
	if (reduce < 0) {
		reduce = 0;
	} else if (reduce > 1) {
		reduce = 1;
	}

	float radian = reduce * CMath::PI2;
	int moveVCount = 1;
	{
		//最初の頂点が45度しか動かないのでそれをまず引く
		float countRad = radian - (CMath::PI / 4);
		//countRadが0より大きい(移動量が45度より大きい)場合、動かす頂点を1プラス
		//以降90度ごとに1プラスしていく
		for (; countRad > 0.0f; countRad -= CMath::PI / 2) {
			moveVCount += 1;
		}
	}

	float xORy;
	{
		//半径が形作る直角三角形の角度を求める。これは中心に近い角。
		float rAngle = radian;
		while (rAngle > CMath::PI / 2) {//90度で割った余り
			rAngle -= CMath::PI / 2;
		}
		if (rAngle > CMath::PI / 4) {//45度を超えたら反転する
			rAngle = CMath::PI / 2 - rAngle;
		}

		//判明していなかった角度
		float kakudo = CMath::PI - rAngle - (CMath::PI / 2);

		//正弦定理の直角三角形がなす外接円の直径
		float r2 = 1 / sinf(kakudo);
		//そこから直角三角形のx座標かy座標として使えるあそこの辺を求める。
		xORy = r2 * sinf(rAngle);

	}

	CVector4 pos(m_size.x / 2, m_size.y / 2, 0.0f, 1.0f);
	CVector2 tex;

	int clockSign = clockwise ? -1 : 1;

	//回転のスタートがy軸上からなのでy座標はcosで、x座標はsinで求める。
	//テクスチャ座標では上が０で下が１なのでコサインの計算にマイナスをかけることで反転させる。
	if (moveVCount % 2 == 0) {
		//moveVCountが偶数の場合、頂点は縦方向の辺上にあるのでx座標は右か左かだけ考えればよい。
		pos.x *= getSign( sinf(radian) ) * clockSign;
		pos.y *= xORy * getSign(cosf(radian));

		tex.x = getSign(sinf(radian)) * 0.5f * clockSign + 0.5f;
		tex.y = xORy* -getSign(cosf(radian)) * 0.5f + 0.5f;
	} else {
		//moveVCountが奇数の場合、頂点は横方向の辺上にあるのでy座標は上か下かだけ考えればよい。
		pos.x *= xORy * getSign(sinf(radian)) * clockSign;
		pos.y *= getSign( cosf(radian) );

		tex.x = xORy * getSign(sinf(radian)) *0.5f * clockSign + 0.5f;
		tex.y = -getSign(cosf(radian)) * 0.5f + 0.5f;
	}

	//動かす頂点には計算した頂点を、それ以外は元の頂点を入れる
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

	//頂点バッファアップデート
	CRenderContext& rc = Engine().GetGraphicsEngine().GetRenderContext();
	CVertexBuffer& vBuffer = m_primitive.GetVertexBuffer();

	rc.UpdateSubresource(vBuffer, movedVer);
}
