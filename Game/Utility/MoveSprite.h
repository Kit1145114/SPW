#pragma once
class MoveSprite : public IGameObject{
public:
	MoveSprite();
	~MoveSprite();

	void Init(const wchar_t* texFilePath, float w, float h) {
		tex.CreateFromDDSTextureFromFile(texFilePath);
		sprite.Init(tex, w, h);
	}

	void setNowPos(const CVector3& pos) {
		nowPos = pos;
		state = speedSave;
	}

	CVector3 getNowPos() {
		return nowPos;
	}

	void setTargetPos(const CVector3& pos) {
		targetPos = pos;
		state = speedSave;
	}

	void setSpeed(float go, float back) {
		goSpeed = go;
		backSpeed = back;
	}

	void Update() override;

	void PostRender(CRenderContext& rc) override;

private:
	enum State{
		speedSave,
		goTarget,
		spring,
		moveEnd
	};

	State state = speedSave;

	float goSpeed = 4.0f;
	float backSpeed = 8.0f;

	CVector3 springPower;
	CVector3 speed;

	CVector3 nowPos;
	CVector3 targetPos;

	CShaderResourceView tex;
	CSprite sprite;
};

