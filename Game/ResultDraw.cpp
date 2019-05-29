#include "stdafx.h"
#include "ResultDraw.h"


ResultDraw::ResultDraw()
{
}


ResultDraw::~ResultDraw()
{
}

bool ResultDraw::Start()
{
	return true;
}

void ResultDraw::Update()
{
}

void ResultDraw::PostRender(CRenderContext& rc)
{
	wchar_t text[10];
	if (P == 1) {
		swprintf_s(text, L"1th\n");
		m_font.Begin(rc);
		m_font.Draw(
			text,
			{ -285.0f, 195.0f },
			{ 1.0f, 0.95f, 0.0f, 1.0f },
			0.0f,
			1.675f
		);
	}
	else if (P == 2)
	{
		swprintf_s(text, L"2th\n");
		m_font.Begin(rc);
		m_font.Draw(
		text,
		{ -300.0f, 55.0f },
		{ 0.9f, 0.9f, 0.9f, 1.0f },
			0.0f,
			1.675f
			);
	}
	else if (P == 3) {
		swprintf_s(text, L"3th\n");
		m_font.Begin(rc);
		m_font.Draw(
			text,
			{ -300.0f, -95.0f },
			{ 1.0f, 0.2f, 0.0f, 1.0f },
			0.0f,
			1.675f
		);
	}
	else if (P == 4) {
		swprintf_s(text, L"4th\n");
		m_font.Begin(rc);
		m_font.Draw(
			text,
			{ -300.0f, -245.0f },
			{ 0.75f, 0.0f, 0.75f, 1.0f },
			0.0f,
			1.675f
		);
	}
	else
	{

	}
	m_font.End(rc);
}