#include "stdafx.h"
#include "SansenGamen.h"
#include "StageSelect.h"
#include "Fade.h"

SansenGamen::SansenGamen() {
}


SansenGamen::~SansenGamen() {
	DeleteGO(m_spriteRender);
}

bool SansenGamen::Start() {
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/Sanka.dds", 1280.0f, 720.0f);
	m_push = NewGO<prefab::CSoundSource>(0);
	m_push->Init(L"sound/Kettei.wav");

	Fade::fadeOut();
	return true;
}


void SansenGamen::Update() {
	if (GameStart == false) {
		if (Pad(0).IsTrigger(enButtonUp)) {
			if (Kazu < MaxKazu) {
				Kazu++;
				m_push = NewGO<prefab::CSoundSource>(0);
				m_push->Init(L"sound/piko.wav");
				m_push->Play(false);
			} else if (Kazu > MaxKazu) {
				Kazu = MaxKazu;
				m_push = NewGO<prefab::CSoundSource>(0);
				m_push->Init(L"sound/piko.wav");
				m_push->Play(false);
			}
		} else if (Pad(0).IsTrigger(enButtonDown)) {
			if (Kazu > MinKazu) {
				Kazu--;
				m_push = NewGO<prefab::CSoundSource>(0);
				m_push->Init(L"sound/piko.wav");
				m_push->Play(false);
			} else if (Kazu < MinKazu) {
				Kazu = MinKazu;
				m_push = NewGO<prefab::CSoundSource>(0);
				m_push->Init(L"sound/piko.wav");
				m_push->Play(false);
			}
		}
	}
	if (Pad(0).IsTrigger(enButtonA)) {
		int l_kazu = Kazu;
		Fade::fadeIn([&,l_kazu]() {
			m_push = NewGO<prefab::CSoundSource>(0);
			m_push->Init(L"sound/tugihe.wav");
			m_push->Play(false);
			DeleteGO(this);
			GameStart = true;
			m_push->Play(false);
			//NewGO<Game>(0, "Game")->SetSanSenkazu(Kazu);
			NewGO<StageSelect>(0)->setSansenKazu(l_kazu);
		});
	}
}

void SansenGamen::PostRender(CRenderContext& rc) {
	if (Death == false) {
		wchar_t text[2506];

		swprintf_s(text, L"player %d\n", Kazu);
		m_font.Begin(rc);

		m_font.Draw(
			text,
			{ 0.0f, -250.0f },
			{ 0.0f, 0.0f, 1.0f, 1.0f },
			0.0f,
			1.5f
		);
		m_font.End(rc);
	}
}
