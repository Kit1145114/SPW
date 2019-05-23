#pragma once
#include"Game.h"
#include "Utility/MoveSprite.h"

class ArrowRender : public IGameObject {
public:
	void Init(const wchar_t* texFilePath, float w, float h) {
		tex.CreateFromDDSTextureFromFile(texFilePath);
		sprite.Init(tex, w, h);
	}

	void setOffsetPos(const CVector3& pos) {
		offset = pos;
	}

	void setPos(CVector3 pos) {
		pos += offset;
		sprite.Update(pos, m_rot, CVector3::One);
	}

	void setPR(CVector3 pos, const CQuaternion& rot) {
		pos += offset;
		m_rot = rot;
		sprite.Update(pos, m_rot, CVector3::One);
	}

	void push() {
		pushFlash = 1.0f;
	}

	void Update() override {
		pushFlash -= GameTime().GetFrameDeltaTime() * 5;
		if (pushFlash < 0) {
			pushFlash = 0;
		}
		sprite.SetMulColor({ pushFlash,pushFlash,1.0f,0.7f });
	}

	void PostRender(CRenderContext& rc) override;

private:
	CQuaternion m_rot;
	CShaderResourceView tex;
	CSprite sprite;
	CVector3 offset;
	float pushFlash = 0.0f;
};

class SansenGamen : public IGameObject
{
public:
	SansenGamen();
	~SansenGamen();
	bool Start() override;
	void Update() override;
	void PostUpdate() override;
	void PostRender(CRenderContext& rc) override;

	void setBackGround(prefab::CSpriteRender* back) {
		sprite_back = back;
	}

private:
	CFont m_font;
	prefab::CSpriteRender* sprite_back = nullptr;
	MoveSprite* sprite_player = nullptr;
	MoveSprite* sprite_num = nullptr;

	ArrowRender* num_arrow[2] = {};

	prefab::CSoundSource* m_push = nullptr;
	int Kazu = 1;
	int MaxKazu = 4;
	int MinKazu = 1;
	bool GameStart = false;
	bool Death = false;

	float waitStageSelect = -1.0f;
};

