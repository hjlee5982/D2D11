#pragma once

class Transform : public Component, public std::enable_shared_from_this<Transform>
{
	REFLECTION(Transform);
public:
	virtual void MakeJson() override;
	virtual void LoadJson(const nlohmann::json& json) override;
public:
	virtual void Update()     override;
public:
	Vector3    GetLocalPosition() { return _localPosition; }
	Vector3    GetLocalScale()    { return _localScale;    }
	Quaternion GetLocalRotation() { return _localRotation; }
	void       SetLocalPosition(const Vector3&    localPosition) { _localPosition = localPosition; Update(); }
	void       SetLocalScale   (const Vector3&    localScale   ) { _localScale    = localScale;    Update(); }
	void       SetLocalRotation(const Quaternion& localRotation) { _localRotation = localRotation; Update(); }
public:
	Vector3    GetPosition() { return _position; }
	Vector3    GetScale()	 { return _scale;	 }
	Quaternion GetRotation() { return _rotation; }
	void       SetPosition(const Vector3&    worldPosition);
	void       SetScale   (const Vector3&    worldScale   );
	void       SetRotation(const Quaternion& worldRotation);
public:
	Matrix  GetWorldMatrix() { return _worldMatrix;     	}
	Vector3 GetRight()       { return _worldMatrix.Right(); }
	Vector3 GetUp()          { return _worldMatrix.Up();	}
	Vector3 GetLook()        { return _worldMatrix.Look();  }
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

public:
	void SetParent(sptr<Transform> p)
	{
		if (_parent.lock() != nullptr)
		{
			auto& siblings = _parent.lock()->_children;

			auto it = std::find_if(siblings.begin(), siblings.end(), [this]
			(const sptr<Transform>& child)
				{
					return child.get() == this;
				});

			if (it != siblings.end())
			{
				siblings.erase(it);
			}
		}

		_parent = p;

		if (p != nullptr)
		{
			p->_children.push_back(shared_from_this());
		}
	}
private:
	// 부모는 weak로 들고있어야 순환참조가 걸리지 않음
	//sptr<Transform> _parent;
	wptr<Transform> _parent;
	List<sptr<Transform>> _children;
};