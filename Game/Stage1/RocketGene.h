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
	static constexpr float interval = 5.0f;
	float timer = 0.0f;

	static constexpr int arrayNum = 5;
	Rocket* rocketArray[arrayNum] = {};
};


