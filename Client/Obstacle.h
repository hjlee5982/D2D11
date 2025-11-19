#pragma once

class Obstacle : public Component
{
public:
	virtual void Update() override;
public:
	void SetGenerator(sptr<class ObstacleGenerator> generator)
	{
		_generator = generator;
	}
private:
	f32 _speed = 3.f;
private:
	wptr<class ObstacleGenerator> _generator;
};

