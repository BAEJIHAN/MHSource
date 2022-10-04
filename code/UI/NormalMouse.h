#pragma once

#include "Widget/WidgetWindow.h"

class CNormalMouse :
    public CWidgetWindow
{
	friend class CViewport;
	friend class CWidgetComponent;
	friend class CEngine;

protected:
	CNormalMouse();
	CNormalMouse(const CNormalMouse& window);
	virtual ~CNormalMouse();

private:
	CSharedPtr<class CImage>	m_MouseImage;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
};

