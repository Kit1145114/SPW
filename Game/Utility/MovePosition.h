#pragma once

class MovePosition {
public:
	MovePosition() = default;
	~MovePosition() = default;

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

	CVector3 getTargetPos() {
		return targetPos;
	}

	void setSpeed(float go, float back) {
		goSpeed = go;
		backSpeed = back;
	}

	void setWaitTime(float sec) {
		waitTime = sec;
	}

	void Update();

private:
	enum State {
		speedSave,
		goTarget,
		spring,
		moveEnd
	};

	State state = speedSave;

	float goSpeed = 1.0f;
	float backSpeed = 1.0f;

	float waitTime = 0.0f;

	CVector3 springPower;
	CVector3 speed;

	CVector3 nowPos;
	CVector3 targetPos;
};

