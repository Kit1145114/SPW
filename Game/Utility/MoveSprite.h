#pragma once
#include "MovePosition.h"

class MoveSprite : public IGameObject{
public:
	MoveSprite() = default;
	~MoveSprite() = default;

	void Init(const wchar_t* texFilePath, float w, float h) {
		tex.CreateFromDDSTextureFromFile(texFilePath);
		sprite.Init(tex, w, h);
	}

	void setNowPos(const CVector3& pos) {
		movePos.setNowPos(pos);
	}

	CVector3 getNowPos() {
		return movePos.getNowPos();
	}

	void setTargetPos(const CVector3& pos) {
		movePos.setTargetPos(pos);
	}

	CVector3 getTargetPos() {
		return movePos.getTargetPos();
	}

	void setSpeed(float go, float back) {
		movePos.setSpeed(go, back);
	}

	void setWaitTime(float sec) {
		movePos.setWaitTime(sec);
	}

	void Update() override;

	void PostRender(CRenderContext& rc) override;

private:
	MovePosition movePos;
	CShaderResourceView tex;
	CSprite sprite;
};

