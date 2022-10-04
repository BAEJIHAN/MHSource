#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/Image.h"

class CJoomMouse :
    public CWidgetWindow
{
	friend class CViewport;
	friend class CWidgetComponent;
	friend class CEngine;

protected:
	CJoomMouse();
	CJoomMouse(const CJoomMouse& window);
	virtual ~CJoomMouse();

private:
	CSharedPtr<CImage>	m_MouseImage;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
};

