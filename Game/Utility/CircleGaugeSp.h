#pragma once
class CircleGaugeSp : public CSprite{
public:
	void Init(CShaderResourceView& tex, float w, float h, bool clockwise = true);
	void setFillAmount(float amount);

private:
	struct SSimpleVertex {
		CVector4 pos;
		CVector2 tex;
	};
	static constexpr int vNum = 7;
	SSimpleVertex vertices[vNum];
	bool clockwise = false;
};

