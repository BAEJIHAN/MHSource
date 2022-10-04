#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/Image.h"

class CChargingJoomMouse :
    public CWidgetWindow
{
	friend class CViewport;
	friend class CWidgetComponent;
	friend class CEngine;

protected:
	CChargingJoomMouse();
	CChargingJoomMouse(const CChargingJoomMouse& window);
	virtual ~CChargingJoomMouse();

private:
	CSharedPtr<CImage>	m_MouseImage;
	CSharedPtr<CImage>	m_ChargingImage;
	class CPlayer* m_Player;

	float m_Time;
	int		m_Count;

public:
	void SetJoomTime(float Time)
	{
		m_Time = Time;
	}

	void SetPlayerNull()
	{
		m_Player = nullptr;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
};

