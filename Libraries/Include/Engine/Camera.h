#pragma once

class Camera : public Component
{
public:
	virtual ~Camera() = default;
public:
	virtual void SetOwner(sptr<class GameObject> owner) override;
public:
	void Update();
public:
	f32 GetNear() { return _near; }
	f32 GetFar()  { return _far;  }
	f32 GetFov()  { return _fov;  }
public:
	void SetCameraOption(f32 Near, f32 Far, f32 fov);
public:
	void SetNear(f32 Near) { _near = Near; }
	void SetFar(f32 Far)   { _far = Far;   }
	void SetFov(f32 fov)   { _fov = fov;   }
private:
	f32 _near;
	f32 _far;
	f32 _fov;
	f32 _width;
	f32 _height;
public:
	static Matrix ViewMatrix;
	static Matrix ProjMatrix;	
};

