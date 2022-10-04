#pragma once

#include "Widget/WidgetWindow.h"

class CClickMouse :
    public CWidgetWindow
{
	friend class CViewport;
	friend class CWidgetComponent;
	friend class CEngine;

protected:
	CClickMouse();
	CClickMouse(const CClickMouse& window);
	virtual ~CClickMouse();

private:
	CSharedPtr<class CImage>	m_MouseImage;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
};

