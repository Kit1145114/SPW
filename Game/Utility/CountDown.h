#pragma once
#include "CircleGaugeSp.h"

class CountDown : public IGameObject{
public:
	CountDown();
	~CountDown();

	bool Start() override;
	void Update() override;

	void PostRender(CRenderContext& rc) override;

	void setPP(CountDown** pp) {
		pp_me = pp;
	}

private:
	CShaderResourceView tex_front;
	CSprite front;

	CShaderResourceView tex_back;
	CircleGaugeSp back;

	float startWait = 0.5f;
	bool isStart = false;

	char count = 3;
	static constexpr float c_interval = 1.4f;
	float sec = c_interval;

	static constexpr float c_scale = 1.7f;
	float scale = c_scale;

	float alpha = 0.0f;

	std::unique_ptr<DirectX::SpriteFont> dxFont;
	CFont font;

	CountDown** pp_me = nullptr;
};

