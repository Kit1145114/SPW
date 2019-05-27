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
	DeleteGO(num_arrow[0]);
	DeleteGO(num_arrow[1]);
}

bool SansenGamen::Start() {
	if (sprite_back == nullptr) {
		sprite_back = NewGO<prefab::CSpriteRender>(0);
		sprite_back->Init(L"sprite/BackTile.dds", 1280.0f, 720.0f);
	}

	sprite_player = NewGO<MoveSprite>(0);
	sprite_player->Init(L"sprite/Sansen_Player.dds", 1280.0f, 241.2f);
	sprite_player->setNowPos({ 0.0f, 500.0f ,0.0f});
	sprite_player->setTargetPos({ 0.0f, 200.0f ,0.0f });
	sprite_player->setSpeed(4.0f, 4.0f);

	sprite_num = NewGO<MoveSprite>(0);
	sprite_num->Init(L"sprite/Sansen_Number.dds", 1280.0f, 110.4f);
	sprite_num->setNowPos({ 0.0f, -500, 0.0f});
	sprite_num->setTargetPos({ 0.0f, -280, 0.0f });
	sprite_num->setSpeed(4.0f, 4.0f);

	for (int i = 0; i < 2; i++) {
		num_arrow[i] = NewGO<ArrowRender>(3);
		num_arrow[i]->Init(L"sprite/Sansen_arrow.dds", 40, 40);

		CVector3 offset;
		offset.x = 167.0f;
		offset.y = 13.0f + 65.0f - i * 65.0f * 2;
		num_arrow[i]->setOffsetPos(offset);

		CQuaternion rot;
		rot.SetRotation(CVector3::AxisZ, CMath::PI*i);

		num_arrow[i]->setPR(sprite_num->getNowPos(), rot);
	}

	Fade::fadeOut();
	return true;
}


void SansenGamen::Update() {
	if (waitStageSelect > 0.0f) {
		waitStageSelect -= GameTime().GetFrameDeltaTime();
		if (waitStageSelect <= 0.0f) {
			DeleteGO(this);
			GameStart = true;
			m_push->Play(false);
			StageSelect* stSel = NewGO<StageSelect>(2);
			stSel->setSansenKazu(Kazu);
			stSel->setBackGround(sprite_back);
			sprite_back = nullptr;
		}
		return;
	}

	if(Pad(0).IsTrigger(enButtonB)) {
		sprite_player->setTargetPos({ 0.0f, 500.0f ,0.0f });
		sprite_num->setTargetPos({ 0,-500,0 });
		prefab::CSoundSource* se = NewGO<prefab::CSoundSource>(0);
		se->Init(L"sound/Kettei.wav");
		se->Play(false);
		Fade::fadeIn([&]() {
			NewGO<Title_2>(0, "Title_2");
			DeleteGO(this);
		});
	}
	if (GameStart == false) {
		if (Pad(0).IsTrigger(enButtonUp)) {
			if (Kazu < MaxKazu) {
				Kazu++;
			}
			m_push = NewGO<prefab::CSoundSource>(0);
			m_push->Init(L"sound/piko.wav");
			m_push->Play(false);
			num_arrow[0]->push();

		} else if (Pad(0).IsTrigger(enButtonDown)) {
			if (Kazu > MinKazu) {
				Kazu--;
			}
			m_push = NewGO<prefab::CSoundSource>(0);
			m_push->Init(L"sound/piko.wav");
			m_push->Play(false);
			num_arrow[1]->push();
		}
	}
	if (Pad(0).IsTrigger(enButtonA)) {
		waitStageSelect = 0.3f;
		sprite_player->setTargetPos({ 0.0f, 500.0f ,0.0f });
		sprite_num->setTargetPos({ 0,-500,0 });
		m_push = NewGO<prefab::CSoundSource>(0);
		m_push->Init(L"sound/tugihe.wav");
		m_push->Play(false);
	}
}

void SansenGamen::PostUpdate() {
	num_arrow[0]->setPos(sprite_num->getNowPos());
	num_arrow[1]->setPos(sprite_num->getNowPos());
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
			{ 0.7f, 0.7f, 0.7f, 1.0f },
			0.0f,
			1.5f
		);
		m_font.End(rc);
	}
}

void ArrowRender::PostRender(CRenderContext & rc) {
	sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	int i = 0;
}
