#include "stdafx.h"
#include "Fade.h"


Fade::Fade() {
	texture.CreateFromDDSTextureFromFile(L"sprite/dummy.dds");
	sprite.Init(texture, MainCamera2D().GetWidth(), MainCamera2D().GetHeight());
}


Fade::~Fade() {
}

void Fade::Update() {
	if (state == FadeIn && alpha < 1.0f) {

	}else
	if (state == FadeOut && alpha > 0.0f) {

	}
}

void Fade::PostRender(CRenderContext & rc) {
	sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
