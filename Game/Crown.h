#pragma once
class Crown : public IGameObject{
public:
	~Crown();

	void Awake() override;
	void Update() override;

	void setPosition(CVector3 pos) {
		pos.y += upDown + offset;
		model->SetPosition(pos);
	}

private:
	float speed = 0.0f;
	static constexpr float offset = 2000.0f;
	float upDown = 400;
	CQuaternion rot;
	prefab::CSkinModelRender* model = nullptr;
};

