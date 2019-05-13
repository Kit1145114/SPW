#pragma once
class Fade : public IGameObject{
public:
	Fade();
	~Fade();

	void Update() override;
	
	void PostRender(CRenderContext& rc) override;

private:
	CShaderResourceView texture;
	CSprite sprite;

	enum FadeState {
		FadeIn,
		Idle,
		FadeOut
	};

	FadeState state = FadeOut;
	float alpha = 1.0f;
};

