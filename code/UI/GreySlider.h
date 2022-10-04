#pragma once
#include "Widget/Slider.h"
class CGreySlider : public CSlider
{
	friend class CWidgetWindow;

protected:
	CGreySlider();
	CGreySlider(const CGreySlider& widget);
	virtual ~CGreySlider();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CSlider* Clone();

public:
	void SetInitPos(const float Grey);
	
};



