#pragma once

#include "Animation/AnimationSequenceInstance.h"

class CAnjanathAnimation :
    public CAnimationSequenceInstance
{
public:
	CAnjanathAnimation();
	CAnjanathAnimation(const CAnjanathAnimation& Anim);
	~CAnjanathAnimation();

public:
	virtual bool Init();

};

