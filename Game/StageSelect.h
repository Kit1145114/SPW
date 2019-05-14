#pragma once

class StageIcon {
public:
	StageIcon() = default;

	void Init(const wchar_t* image, CVector3 position) {
		texture.CreateFromDDSTextureFromFile(image);
		sprite.Init(texture, 250, 150);
		m_pos = position;
		sprite.Update(m_pos, CQuaternion::Identity, CVector3::One);
		m_pos.y += 15;//セレクターを合わせるための調整
	};

	void draw(CRenderContext& rc) {
		sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	}

	CVector3 getPos() {
		return m_pos;
	}

	void goStage() {
		newStageFunc();
	}

	void setStageFunc(std::function<void()> func) {
		newStageFunc = func;
	}

private:
	std::function<void()> newStageFunc;
	CShaderResourceView texture;
	CSprite sprite;
	CVector3 m_pos;
	int sansenKazu;
};


class StageSelect : public IGameObject{
public:
	StageSelect() = default;
	~StageSelect();

	void setSansenKazu(int kazu) {
		sansenKazu = kazu;
	}

	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& rc) override;
	void Sound(int SoundNum);

private:
	int sansenKazu = 0;

	int selectNumber = 0;
	static constexpr int iconNum = 5;
	StageIcon iconArray[iconNum];

	CShaderResourceView backTexture;
	CSprite backSprite;

	CShaderResourceView selectTexture;
	CSprite selectSprite;

	prefab::CSoundSource* m_push = nullptr;//BGM用のサウンドソース。
};

