#pragma once

class Camera : public Component
{
public:
	virtual void MakeJson() override;
	virtual void LoadJson() override;
public:
	virtual void Awake()      override;
	virtual void Update()     override;
public:
	f32 GetNear() { return _near; }
	f32 GetFar()  { return _far;  }
	f32 GetFov()  { return _fov;  }
public:
	void SetNear(f32 Near) { _near = Near; }
	void SetFar(f32 Far)   { _far  = Far;  }
	void SetFov(f32 fov)   { _fov  = fov;  }
private:
	f32 _near;
	f32 _far;
	f32 _fov;
	f32 _width;
	f32 _height;
};

