#pragma once
class Meteo;
class MeteoGene : public IGameObject
{
public:
	~MeteoGene();
	void Update();
private:
	float timer = 0;
	float Inittime = 3.0f;
};

