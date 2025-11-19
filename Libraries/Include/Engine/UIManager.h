#pragma once

class UIManager : public Singleton<UIManager>
{
public:
	virtual void Awake() override;
public:
	void Update();
public:
	void AddUIObject(sptr<class UIObject> ui);
private:
	sptr<class Camera> _uiCamera;
private:
	List<sptr<class UIObject>> _uiObjects;
};

