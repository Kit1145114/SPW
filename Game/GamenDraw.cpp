#include "stdafx.h"
#include "GamenDraw.h"

GamenDraw::GamenDraw()
{
	//m_push = NewGO<prefab::CSoundSource>(0);
	//m_push->Init(L"sound/tugihe.wav");
	tl2 = FindGO<Title_2>("Title_2");
}


GamenDraw::~GamenDraw()
{
	
}


void GamenDraw::Update()
{
	if (Pad(0).IsPress(enButtonUp) == true)
	{
		if (mode == 1) {
			GemenDrawSound(0);
		}
		mode = 0;
		tl2->Setmode(mode);
	}
	else if (Pad(0).IsPress(enButtonDown) == true)
	{
		if (mode == 0) {
			GemenDrawSound(0);
		}
		mode = 1;
		tl2->Setmode(mode);
	}

	if (mode == 0 && Pad(0).IsPress(enButtonA) == true){
		//DeleteGO(this);
		GemenDrawSound(1);
	}
	if (mode == 1 && Pad(0).IsPress(enButtonA) == true) {
		//DeleteGO(this);
		GemenDrawSound(1);
		//NewGO<SetumeiGamen>(0, "SetumeiGamen");
	}

	//�I�����̑傫��
	for (int i = 0; i < 2; i++) {
		int sign = (mode == i) ? 1 : -1;//���[�h�������Ɠ����Ȃ�(�������I������Ă�����)���₷�B�t�͌��炷�B

		wordScale[i] += GameTime().GetFrameDeltaTime()*sign;

		if (wordScale[i] < wordMinScale) {
			wordScale[i] = wordMinScale;
		}else if (wordScale[i] > wordMaxScale) {
			wordScale[i] = wordMaxScale;
		}
	}
}
//��ʂɕ`�ʁB
void GamenDraw::PostRender(CRenderContext& rc) {
	wchar_t text[2506];

	swprintf_s(text, L"game play\n");
	m_font.Begin(rc);

	{
		CVector4 color = {0.0f, 0.0f, 0.0f, 1.0f};
		CVector2 pos = { 0.0f, -105.0f };
		//�t�H���g�̉e�̂��߂�2��draw����
		for (int i = 0; i < 2; i++) {
			m_font.Draw(text, pos, color, 0.0f, wordScale[0]);
			pos.x -= 3.0f;
			pos.y += 3.0f;
			//�I�����(mode == 0)�ł͐F���ς��
			if (mode == 0) {
				color = { 0.0f, 1.0f, 1.0f, 1.0f };
			} else if (mode == 1) {
				color = { 0.0f, 0.0f, 1.0f, 1.0f };
			}
		}
	}

	swprintf_s(text, L"manual\n");

	{
		CVector4 color = { 0.0f, 0.0f, 0.0f, 1.0f };
		CVector2 pos = { 0.0f, -200.0f };
		//�t�H���g�̉e�̂��߂�2��draw����
		for (int i = 0; i < 2; i++) {
			m_font.Draw(text, pos, color, 0.0f, wordScale[1]);
			pos.x -= 3.0f;
			pos.y += 3.0f;
			//�I�����(mode == 1)�ł͐F���ς��
			if (mode == 0) {
				color = { 0.0f, 0.0f, 1.0f, 1.0f };
			} else if (mode == 1) {
				color = { 0.0f, 1.0f, 1.0f, 1.0f };
			}
		}
	}
	m_font.End(rc);
}

void GamenDraw::GemenDrawSound(int SoundNum)
{
	if (SoundNum == 0) {
		m_push = NewGO<prefab::CSoundSource>(0);
		m_push->Init(L"sound/piko.wav");
		m_push->Play(false);
		m_push->SetVolume(0.8f);
	}
	if(SoundNum ==1){
		m_push = NewGO<prefab::CSoundSource>(0);
		m_push->Init(L"sound/tugihe.wav");
		m_push->Play(false);
		m_push->SetVolume(0.5f);
	}
}
