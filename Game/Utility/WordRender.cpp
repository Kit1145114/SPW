#include "stdafx.h"
#include "WordRender.h"
#include "MoveSprite.h"

void WordRender::Init
(const wchar_t * word, MoveSprite* moveSprite, const CVector3& pos, const CVector4& col, float sc) {
	m_word = word;
	moveSp = moveSprite;
	position = pos;
	color = col;
	scale = sc;
}

void WordRender::PostRender(CRenderContext & rc) {
	font.Begin(rc);
	CVector3 p = moveSp->getNowPos() + position;
	CVector2 p2;
	p2.x = p.x;
	p2.y = p.y;
	font.Draw(m_word, p2, {0,0,0,1}, 0, scale);
	p2.x += 10;
	p2.y += 10;
	font.Draw(m_word, p2, color, 0, scale);
	font.End(rc);
}
