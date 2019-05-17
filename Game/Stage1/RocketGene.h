#pragma once
class Rocket;

class RocketGene : public IGameObject {
public:
	void OnDestroy() override;
	void Update() override;

	Rocket* const* getArray(){
		return rocketArray;
	}

	static constexpr int getArrayNum() {
		return arrayNum;
	}

private:
	static constexpr float interval = 2.0f;
	float timer = 0.0f;

	static constexpr int arrayNum = 3;
	Rocket* rocketArray[arrayNum] = {};
};


