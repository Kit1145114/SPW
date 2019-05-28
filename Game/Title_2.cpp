#include "stdafx.h"
#include "Title_2.h"
#include "GameWait.h"
#include "Fade.h"

Title_2::Title_2()
{
}


Title_2::~Title_2()
{
	DeleteGO(sprite_line);
	DeleteGO(m_background);
	DeleteGO(m_bgm);
	DeleteGO(m_Draw);

	for (int i = 0; i < sentenceNum; i++) {
		DeleteGO(sentence[i]);
	}

	DeleteGO(flush);
}

bool Title_2::Start()
{
	m_background = NewGO<prefab::CSpriteRender>(0);
	m_background->Init(L"sprite/dummy.dds", MainCamera2D().GetWidth(), MainCamera2D().GetHeight());
	m_background->SetMulColor({ 0, 0, 0, 1 });

	sprite_line = NewGO<prefab::CSpriteRender>(1);
	sprite_line->Init(L"sprite/Title_Line.dds", 1280.0f, 60.0f);
	sprite_line->SetPosition({ 0, 150, 0});

	m_bgm = NewGO<prefab::CSoundSource>(0);
	m_bgm->Init(L"sound/OP.wav");
	m_bgm->Play(true);
	m_bgm->SetVolume(0.3f);
	m_Draw = NewGO<GamenDraw>(3, "GamenDraw");

	ID3D11Device* device = Engine().GetGraphicsEngine().GetD3DDevice();
	dxFont = std::make_unique<DirectX::SpriteFont>(device, L"font/bigfont.spritefont");
	m_font.SetFont(dxFont.get());

	CVector3 pos = {-450, 205, 0};
	for (int i = 0; i < sentenceNum; i++) {
		sentence[i] = NewGO<MoveCharacter>(2);
		sentence[i]->Init(titleName[i], &m_font);
		sentence[i]->Pos().setTargetPos(pos);
		sentence[i]->Pos().setNowPos({ 0,-400,0 });
		sentence[i]->Pos().setWaitTime(i * 0.2f);
		sentence[i]->Pos().setSpeed(4.0f, 8.0f);
		if (i == 4) {
			pos.x += 200;
		} else if (i == 5) {
			pos.x += 120;
		} else {
			pos.x += 95;
		}
	}

	Fade::fadeOut();
	return true;
}

void Title_2::Update()
{
	if (mode == 0 && Pad(0).IsTrigger(enButtonA) == true)
	{
		Fade::fadeIn([&]() {
		DeleteGO(this);
		//NewGO<SansenGamen>(1,"SansenGamen");
#ifdef UseNetwork
		NewGO<GameWait>(1);
#else
		NewGO<SansenGamen>(1);
#endif
		}, m_bgm);
	}
	else if (mode == 1&& Pad(0).IsTrigger(enButtonA) == true)
	{
		Fade::fadeIn([&]() {
			DeleteGO(this);
			NewGO<SetumeiGamen>(0, "SetumeiGamen");
		});
	}

	if (flush == nullptr) {
		flushWait -= GameTime().GetFrameDeltaTime();
		if (flushWait < 0.0f) {
			flush = NewGO<Flush>(2);
			flush->Init(&m_background);
		}
	}
}

void MoveCharacter::PostRender(CRenderContext & rc) {
	pos.Update();
	
	m_font->Begin(rc);

	CVector2 p;
	p.x = pos.getNowPos().x;
	p.y = pos.getNowPos().y;

	m_font->Draw(ch, p, CVector4::White, 0.0f, 1.0f);

	m_font->End(rc);
}

void Flush::Update() {
	if (!end) {
		float delta = GameTime().GetFrameDeltaTime();
		if (in) {
			alpha += delta*2;
			if (alpha > 1.0f) {
				in = false;
				(*back)->Init(L"sprite/Title_A.dds", MainCamera2D().GetWidth(), MainCamera2D().GetHeight());
				(*back)->SetMulColor(CVector4::White);
			}
		} else {
			alpha -= delta;
			if (alpha < 0.0f) {
				alpha = 0.0f;
				end = true;
			}
		}
		sprite.SetMulColor({ 1,1,1,alpha });
	}
}
