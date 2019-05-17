#pragma once

class Satellite;

class SatelliteGene : public IGameObject{
public:
	void OnDestroy() override;
	void Update() override;

private:
	static constexpr float interval = 5.0f;
	float timer = 0.0f;

	static constexpr int arrayNum = 3;
	Satellite* satelliteArray[arrayNum] = {};
};

