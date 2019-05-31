#pragma once

class ResultDraw : public IGameObject
{
public:
	void PostRender(CRenderContext& rc) override;
	void SetJuni(int junban)
	{
		Juni = junban;
	}
	void Inactivate() {
		active = false;
	}
private:
	CFont m_font;
	int Juni = 0;
	bool active = true;
};

