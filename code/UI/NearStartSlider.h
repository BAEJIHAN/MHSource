
#pragma once
#include "Widget/Slider.h"
class CNearStartSlider : public CSlider
{
	friend class CWidgetWindow;

protected:
	CNearStartSlider();
	CNearStartSlider(const CNearStartSlider& widget);
	virtual ~CNearStartSlider();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CSlider* Clone();

public:
	void SetInitPos(const float NearStaert);

};



