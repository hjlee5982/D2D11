#pragma once

#include "IExecute.h"

class FlappyBird : public IExecute
{
public:
	void Awake() override;
	void Start() override;
	void Update() override;
	void LateUpdate() override;
private:
	sptr<class GameObject> _camera;
	sptr<class GameObject> _bg;
};

