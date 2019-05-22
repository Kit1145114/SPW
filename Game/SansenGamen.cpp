#include "stdafx.h"
#include "SansenGamen.h"
#include "StageSelect.h"
#include "Fade.h"
#include "Title_2.h"
#include "Utility/CVector2.h"

SansenGamen::SansenGamen() {
}


SansenGamen::~SansenGamen() {
	DeleteGO(sprite_back);
	DeleteGO(sprite_player);
	DeleteGO(sprite_num);
}

bool SansenGamen::Start() {
	sprite_back = NewGO<prefab::CSpriteRender>(0);
	sprite_back->Init(L"sprite/BackTile.dds", 1280.0f, 720.0f);

	sprite_player = NewGO<MoveSprite>(0);
	sprite_player->Init(L"sprite/Sansen_Player.dds", 1280.0f, 241.2f);
	sprite_player->setNowPos({ 0.0f, 500.0f ,0.0f});
	sprite_player->setTargetPos({ 0.0f, 200.0f ,0.0f });

	sprite_num = NewGO<MoveSprite>(0);
	sprite_num->Init(L"sprite/Sansen_Number.dds", 1280.0f, 110.4f);
	sprite_num->setNowPos({ 0.0f, -500, 0.0f});
	sprite_num->setTargetPos({ 0.0f, -280, 0.0f });

	m_push = NewGO<prefab::CSoundSource>(0);
	m_push->Init(L"sound/Kettei.wav");

	Fade::fadeOut();
	return true;
}


void SansenGamen::Update() {
	if(Pad(0).IsTrigger(enButtonB)) {
		sprite_player->setTargetPos({ 0.0f, 500.0f ,0.0f });
		sprite_num->setTargetPos({ 0,-500,0 });
		Fade::fadeIn([&]() {
			NewGO<Title_2>(0, "Title_2");
			DeleteGO(this);
		});
	}
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
		sprite_player->setTargetPos({ 0.0f, 500.0f ,0.0f });
		sprite_num->setTargetPos({ 0,-500,0 });
		int l_kazu = Kazu;
		m_push = NewGO<prefab::CSoundSource>(0);
		m_push->Init(L"sound/tugihe.wav");
		m_push->Play(false);
		Fade::fadeIn([&,l_kazu]() {
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
		wchar_t num[2];
		swprintf_s(num, L"%d", Kazu);
		m_font.Begin(rc);

		CVector2 pos;
		pos.x = sprite_num->getNowPos().x;
		pos.y = sprite_num->getNowPos().y;

		m_font.Draw(
			L"player",
			pos + CVector2(-190, 30),
			{ 0.0f, 0.0f, 1.0f, 1.0f },
			0.0f,
			1.5f,
			{ 0.0f ,0.5f }
		);

		m_font.Draw(
			num,
			pos + CVector2(160, 30),
			{ 0.0f, 0.0f, 1.0f, 1.0f },
			0.0f,
			1.5f
		);
		m_font.End(rc);
	}
}
