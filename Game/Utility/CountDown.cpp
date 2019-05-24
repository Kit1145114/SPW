#include "stdafx.h"
#include "CountDown.h"

CountDown::CountDown() {
}


CountDown::~CountDown() {
}

bool CountDown::Start() {
	tex_front.CreateFromDDSTextureFromFile(L"sprite/CountDown_front.dds");
	front.Init(tex_front, 500, 500);

	tex_back.CreateFromDDSTextureFromFile(L"sprite/CountDown_back.dds");
	back.Init(tex_back, 500, 500, false);
	back.Update(CVector3::Zero, CQuaternion::Identity, { 1.5f ,1.5f, 1.5f });

	ID3D11Device* device = Engine().GetGraphicsEngine().GetD3DDevice();
	dxFont = std::make_unique<DirectX::SpriteFont>(device, L"font/bigfont.spritefont");
	font.SetFont(dxFont.get());

	return true;
}

void CountDown::Update() {
	float delta = GameTime().GetFrameDeltaTime();
	if (!isStart) {
		if (startWait > 0.0f) {
			startWait -= delta;
			return;
		} else {
			isStart = true;
		}
	}

	float l_sec = sec / c_interval;

	alpha = 1.0f;
	if (l_sec > 0.8f) {
		alpha = 1.0f - (l_sec - 0.8f) / 0.2f;
	} else if (l_sec < 0.3f) {
		alpha = (l_sec - 0.1f) / 0.2f;
	}
	front.SetMulColor({ 1,1,1,alpha });

	front.Update(CVector3::Zero, CQuaternion::Identity, { scale ,scale, scale });

	if (count == 0) {
		back.setFillAmount(0);
	} else {
		back.setFillAmount(l_sec);
	}

	scale -= delta * l_sec*0.5f;

	sec -= delta;

	if (sec <= 0.0f) {
		count--;
		sec = c_interval;
		scale = c_scale;

		if (count < 0) {
			DeleteGO(this);
			*pp_me = nullptr;
		} else {
			prefab::CSoundSource* se = NewGO<prefab::CSoundSource>(0);

			if (count == 0) {
				se->Init(L"sound/Countdown2.wav");
			} else {
				se->Init(L"sound/Countdown1.wav");
			}
			se->Play(false);
			se->SetVolume(1.3f);
		}
	}
}

void CountDown::PostRender(CRenderContext & rc) {
	if (isStart) {
		const CMatrix& view = MainCamera2D().GetViewMatrix();
		const CMatrix& proj = MainCamera2D().GetProjectionMatrix();

		back.Draw(rc, view, proj);
		front.Draw(rc, view, proj);

		font.Begin(rc);
		wchar_t text[4];
		if (count == 0) {
			swprintf(text, L"go!");
			font.Draw(text, { -20,45 }, { 1*alpha,0,0,alpha }, 0, scale * 0.8f);
		} else {
			swprintf(text, L"%d", count);
			float threeHosei = (count == 3) ? 10 : 0;
			font.Draw(text, { -20+threeHosei,45 }, { 0,0,0,alpha }, 0, scale);
		}
		font.End(rc);
	}
}
