#pragma once

class Player;

class ResultCamera : public IGameObject{
public:
	bool Start() override;
	void Update() override;

	void Init(const Player* go, const CVector3 & nowCamera, const CVector3 & nowLook);

private:
	const Player* player;

	CVector3 lookPos;
	CVector3 cameraPos;

	static constexpr float speed = 10.0f;
};

