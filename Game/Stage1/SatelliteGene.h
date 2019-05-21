#pragma once

class Satellite;

class SatelliteGene : public IGameObject{
public:
	void OnDestroy() override;
	void Update() override;

	Satellite * const* getArray() {
		return satelliteArray;
	}

	static constexpr int getArrayNum() {
		return arrayNum;
	}

private:
	static constexpr float interval = 3.0f;
	float timer = 0.0f;

	static constexpr int arrayNum = 4;
	Satellite* satelliteArray[arrayNum] = {};
};

