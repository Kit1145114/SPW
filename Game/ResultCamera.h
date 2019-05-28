#pragma once

class Player;

class ResultCamera : public IGameObject{
public:
	ResultCamera();

	bool Start() override;
	void Update() override;

	void Init(const Player** go, int goNum,const CVector3 & nowCamera, const CVector3 & nowLook);

private:
	int playerNum = 0;
	const Player* player[4] = {};

	float tiesMoveWait;//���_1�ʃ��[�v�I���܂ŕ��ϓ_�͋��߂Ȃ��B

	CVector3 lookPos;
	CVector3 cameraPos;

	static constexpr float speed = 10.0f;
};

