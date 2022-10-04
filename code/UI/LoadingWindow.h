#pragma once

#include "Widget/WidgetWindow.h"

class CLoadingWindow :
	public CWidgetWindow
{
	friend class CViewport;

protected:
	CLoadingWindow();
	virtual ~CLoadingWindow();

private:
	std::vector<CSharedPtr<class CImage>>	m_vecLoadIcon;
	CSharedPtr<class CImage>		m_BackImage;
	CSharedPtr<class CProgressBar>	m_LoadingBar;

private:
	int			m_Count;
	float		m_SwitchingTimeAcc;
	float		m_SwitchingTime;
	float		m_Angle;

public:
	void SetLoadingPercent(float Percent);
	bool IsFadeOutCompleted();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CLoadingWindow* Clone();

private:
	void Callbk();
};

