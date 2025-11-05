#pragma once

class Transform : public Component
{
public:
	virtual ~Transform() = default;
public:
	virtual void Update()     override;
private:
	void UpdateLocalMatrix();
public:
	Matrix     GetLocalMatrix()   { return _localMatrix;   }
	Vector3    GetLocalPosition() { return _localPosition; }
	Vector3	   GetLocalScale()    { return _localScale;    }
	Quaternion GetLocalRotation() { return _localRotation; }
public:
	void SetLocalMatrix  (const Matrix&     localMatrix  );
	void SetLocalPosition(const Vector3&    localPosition);
	void SetLocalScale   (const Vector3&    localScale   );
	void SetLocalRotaion (const Quaternion& localRotation);
public:
	Matrix     GetWorldMatrix()	{ return _worldMatrix;	}
	Vector3    GetPosition()	{ return _position;		}
	Vector3    GetScale()	    { return _scale;	    }
	Quaternion GetRotation()    { return _rotation;		}
public:
	void SetWorldMatrix(const Matrix&     worldMatrix);
	void SetPosition   (const Vector3&    position   );
	void SetScale      (const Vector3&    scale      );
	void SetRotation   (const Quaternion& rotation   );
public:
	Vector3 GetRight() { return _right; }
	Vector3 GetUp()    { return _up;	}
	Vector3 GetLook()  { return _look;  }
public:
	void Translation(const Vector3& dir, float speed);
private:
	Matrix     _localMatrix   = Matrix::Identity;
	Vector3    _localPosition = Vector3::Zero;
	Vector3    _localScale    = Vector3::One;
	Quaternion _localRotation = Quaternion::Identity;
private:
	Matrix     _worldMatrix = Matrix::Identity;
	Vector3    _position    = Vector3::Zero;
	Vector3    _scale       = Vector3::One;
	Quaternion _rotation    = Quaternion::Identity;
private:
	Vector3 _right = Vector3(1.f, 0.f, 0.f);
	Vector3 _up    = Vector3(0.f, 1.f, 0.f);
	Vector3 _look  = Vector3(0.f, 0.f, 1.f);
};