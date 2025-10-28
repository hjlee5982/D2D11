#pragma once

#include "IScene.h"

class FlappyBird : public IScene
{
public:
	void InitializeScene() override;
private:
	sptr<class GameObject> _camera;
	sptr<class GameObject> _bgL;
	sptr<class GameObject> _bgR;
};

