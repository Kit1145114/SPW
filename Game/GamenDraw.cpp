#include "stdafx.h"
#include "GamenDraw.h"


GamenDraw::GamenDraw()
{
}


GamenDraw::~GamenDraw()
{
	
}


void GamenDraw::Update()
{

}
void GamenDraw::PostRender(CRenderContext& rc) {
	wchar_t text[256];

	swprintf_s(text, L"Å`PLEASE EN BUTTONÅ`\n");
	m_font.Begin(rc);

	m_font.Draw(
		text,
		{ 0.0f, -200.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f },
		0.0f,
		1.5f
	);
	m_font.End(rc);
}