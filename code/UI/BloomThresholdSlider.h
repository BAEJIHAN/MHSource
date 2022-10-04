#pragma once
#include "Widget/Slider.h"
class CBloomThresholdSlider : public CSlider
{
	friend class CWidgetWindow;

protected:
	CBloomThresholdSlider();
	CBloomThresholdSlider(const CBloomThresholdSlider& widget);
	virtual ~CBloomThresholdSlider();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CSlider* Clone();

public:
	void SetInitPos(const float BloomThreshhold);
};



