#pragma once
#include "Utility\MoveSprite.h"

class StageIcon {
public:
	StageIcon() = default;

	void Init(const wchar_t* image, CVector3 position, float wait);

	void draw(CRenderContext& rc) {
		sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	}

	CVector3 getTargetPos() {
		return movePos.getTargetPos() + CVector3(0, 15, 0);//セレクターを合わせるための調整
	}

	CVector3 getNowPos() {
		return movePos.getNowPos() + CVector3(0, 15, 0);//セレクターを合わせるための調整
	}

	void finishAnim(float wait) {
		movePos.setWaitTime(wait);
		movePos.setTargetPos(movePos.getNowPos() + CVector3(0, -500, 0));
	}

	void Update() {
		movePos.Update();
		sprite.Update(movePos.getNowPos(), CQuaternion::Identity, CVector3::One);
	}

private:
	MovePosition movePos;
	CShaderResourceView texture;
	CSprite sprite;
	int sansenKazu;
};


class StageSelect : public IGameObject{
public:
	StageSelect() = default;
	~StageSelect();

	void setBackGround(prefab::CSpriteRender* back) {
		backSprite = back;
	}

	void setBGM(prefab::CSoundSource* bgm) {
		m_bgm = bgm;
	}

	void setSansenKazu(int kazu) {
		sansenKazu = kazu;
	}

	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& rc) override;
	void Sound(int SoundNum);

private:
	void finishAnim();

	int sansenKazu = 0;

	int selectNumber = 0;
	static constexpr int iconNum = 6;
	StageIcon iconArray[iconNum];

	prefab::CSpriteRender* backSprite = nullptr;

	MoveSprite* titleSprite = nullptr;

	MoveSprite* selectSprite = nullptr;

	prefab::CSoundSource* m_push = nullptr;//BGM用のサウンドソース。

	prefab::CSoundSource* m_bgm = nullptr;

	float waitSansen = -1.0f;
};

