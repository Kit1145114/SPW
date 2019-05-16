#pragma once
class Rocket;

class RocketGene : public IGameObject {
public:
	~RocketGene();

	void Update();

private:
	static constexpr float interval = 5.0f;
	float timer = 0.0f;

	static constexpr int arrayNum = 3;
	Rocket* RocketArray[arrayNum] = {};
};


