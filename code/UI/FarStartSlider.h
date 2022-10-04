
#pragma once
#include "Widget/Slider.h"
class CFarStartSlider : public CSlider
{
	friend class CWidgetWindow;

protected:
	CFarStartSlider();
	CFarStartSlider(const CFarStartSlider& widget);
	virtual ~CFarStartSlider();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CSlider* Clone();

public:
	void SetInitPos(const float FarStart);

};



