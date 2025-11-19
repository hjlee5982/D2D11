#pragma once

class UIRenderer : public Singleton<UIRenderer>
{
public:
	void Render();
private:
	List<wptr<class UIObject>> _uiObjects;
};

