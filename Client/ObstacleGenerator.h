#pragma once

class ObstacleGenerator : public Component
{
public:
	virtual void Update() override;
private:
	void Generate();
private:
	f32 _elapsed = 0.f;
};

