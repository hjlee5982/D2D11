#pragma once

class ObstacleGenerator : public Component, public std::enable_shared_from_this<ObstacleGenerator>
{
public:
	virtual void Start() override;
	virtual void Update() override;
public:
	void ReturnPool(sptr<class GameObject> obstacle);
private:
	void Generate();
private:
	std::queue<sptr<class GameObject>> _obstacles;
private:
	f32 _elapsed   = 0.f;
	f32 _frequency = 2.f;
	i32 _poolSize  = 4;
};

