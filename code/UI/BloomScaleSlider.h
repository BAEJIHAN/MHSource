
#pragma once
#include "Widget/Slider.h"
class CBloomScaleSlider : public CSlider
{
	friend class CWidgetWindow;

protected:
	CBloomScaleSlider();
	CBloomScaleSlider(const CBloomScaleSlider& widget);
	virtual ~CBloomScaleSlider();

	

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CSlider* Clone();

public:
	void SetInitPos(const float BloomScale);



};



