#include "stdafx.h"
#include "Fade.h"

Fade* Fade::st_fade = nullptr;

Fade::Fade() {
	texture.CreateFromDDSTextureFromFile(L"sprite/dummy.dds");
	sprite.Init(texture, MainCamera2D().GetWidth(), MainCamera2D().GetHeight());
}


Fade::~Fade() {
}

void Fade::Update() {
	float delta = GameTime().GetFrameDeltaTime() * 3;
	if (m_state == enFadeIn && alpha < 1.0f) {
		alpha += delta;
		if (alpha >= 1.0f) {
			alpha = 1.0f;
			m_state = enIdle;
			if (func) {
				func();
			}
			func = nullptr;
		}
	}else
	if (m_state == enFadeOut && alpha > 0.0f) {
		alpha -= delta;
		if (alpha <= 0.0f) {
			alpha = 0.0f;
			m_state = enIdle;
		}
	}
	sprite.SetMulColor({ 1,1,1,alpha });
}

void Fade::PostRender(CRenderContext & rc) {
	sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
