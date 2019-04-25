#include "stdafx.h"
#include "ResultDraw.h"


ResultDraw::ResultDraw()
{
}


ResultDraw::~ResultDraw()
{
}


void ResultDraw::Update()
{
	if (Pad(0).IsPress(enButtonSelect) == true)
	{
		DeleteGO(this);
	}
}

void ResultDraw::PostRender(CRenderContext& rc)
{
	wchar_t text[2506];
	if (Juni == 1) {
		swprintf_s(text, L"No.1\n");
	}
	else if (Juni == 2)
	{
		swprintf_s(text, L"No.2\n");
	}
	else if (Juni == 3) {
		swprintf_s(text, L"No.3\n");
	}
	else if (Juni == 4) {
		swprintf_s(text, L"No.4\n");
	}
		m_font.Begin(rc);
		if (P == 1) {
			m_font.Draw(
				text,
				{ -240.0f, 220.0f },
				{ 1.0f, 0.0f, 0.0f, 1.0f },
				0.0f,
				1.5f
			);
		}
		else if (P == 2) {
			m_font.Draw(
				text,
				{ 210.0f, 220.0f },
				{ 0.0f, 0.0f, 1.0f, 1.0f },
				0.0f,
				1.5f
			);
		}
		else if (P == 3) {
			m_font.Draw(
				text,
				{ -240.0f, -90.0f },
				{ 0.0f, 1.0f, 0.0f, 1.0f },
				0.0f,
				1.5f
			);
		}
		else if (P == 4) {
			m_font.Draw(
				text,
				{ 210.0f, -90.0f },
				{ 1.0f, 1.0f, .0f, 1.0f },
				0.0f,
				1.5f
			);
		}
		m_font.End(rc);
	}
