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
	const wchar_t* draw_P = nullptr;
};

