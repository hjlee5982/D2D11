#pragma once

#include "IExecute.h"

class FlappyBird : public IExecute
{
	void Awake() override;
	void Start() override;
	void Update() override;
	void LateUpdate() override;
};

