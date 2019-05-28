#pragma once
class Fade : public IGameObject{
public:
	Fade();
	~Fade();

	enum FadeState {
		enFadeIn,
		enIdle,
		enFadeOut
	};

	static void fadeIn(const std::function<void()>& function = nullptr, prefab::CSoundSource* bgm = nullptr) {
		if (st_fade->m_state != enFadeIn && st_fade->alpha != 1.0f) {
			st_fade->m_state = enFadeIn;
			st_fade->func = function;
			st_fade->bgm = bgm;
			st_fade->volum = bgm ? bgm->GetVolume() : 0;
		}
	}

	static void fadeOut() {
		st_fade->m_state = enFadeOut;
	}

	static void Init() {
		if (st_fade == nullptr) {
			st_fade = NewGO<Fade>(10);
		}
	}

	static void Delete() {
		DeleteGO(st_fade);
		st_fade = nullptr;
	}

	static FadeState state() {
		return st_fade->m_state;
	}

	void Update() override;
	
	void PostRender(CRenderContext& rc) override;
private:
	static Fade* st_fade;

	CShaderResourceView texture;
	CSprite sprite;

	prefab::CSoundSource* bgm = nullptr;
	float volum = 0.0f;

	std::function<void()> func;
	FadeState m_state = enFadeOut;
	float alpha = 1.0f;
};

