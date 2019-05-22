#pragma once

class ResultDraw : public IGameObject
{
public:
	ResultDraw();
	~ResultDraw();
	bool Start();
	void Update();
	void PostRender(CRenderContext& rc) override;
	void SetJuni(int junban)
	{
		Juni = junban;
	}
	void SetPlayer(int num)
	{
		P = num;
	}
	void SetPadKazu(int num)
	{
		PadKazu = num;
	}
private:
	CFont m_font;
	CVector2 m_position = CVector2::Zero;
	int Juni = 0;
	int P = 0;
	int PadKazu = 0;
	prefab::CSpriteRender* P1_spriteRender = nullptr;
	prefab::CSpriteRender* P2_spriteRender = nullptr;
	prefab::CSpriteRender* P3_spriteRender = nullptr;
	prefab::CSpriteRender* P4_spriteRender = nullptr;
	CVector3 N1position = { 0.0f,205.0f,0.0f };
	CVector3 N2position = { 0.0f,55.0f,0.0f };
	CVector3 N3position = { 0.0f,-95.0f,0.0f };
	CVector3 N4position = { 0.0f,-245.0f,0.0f };

	const wchar_t* draw_P = nullptr;
};

