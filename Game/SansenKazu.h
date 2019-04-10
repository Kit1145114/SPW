#pragma once
class SansenKazu: public IGameObject
{
public:
	SansenKazu();
	~SansenKazu();
	bool Start();
	void Update();
	void PostRender(CRenderContext& rc) override;
	void DeathCount(bool a)
	{
		Death = a;
	}
	int GetKazu()
	{
		return Kazu;
	}
private:
	CFont m_font;
	CVector2 m_position = CVector2::Zero;
	int Kazu = 1;
	int MaxKazu = 4;
	int MinKazu = 1;
	bool GameStart = false;
	bool Death = false;
};

