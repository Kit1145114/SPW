#pragma once
class MoveSprite;

class WordRender : public IGameObject{
public:
	void Init(const wchar_t* word, MoveSprite* moveSp, const CVector3& pos, const CVector4& color, float scale);
	void PostRender(CRenderContext& rc) override;
private:
	const wchar_t* m_word;
	CFont font;
	MoveSprite* moveSp = nullptr;
	CVector3 position;
	CVector4 color;
	float scale;
};

