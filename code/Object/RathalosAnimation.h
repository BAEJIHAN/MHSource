
#pragma once

#include "Animation/AnimationSequenceInstance.h"

class CRathalosAnimation :
    public CAnimationSequenceInstance
{
public:
	CRathalosAnimation();
	CRathalosAnimation(const CRathalosAnimation& Anim);
	~CRathalosAnimation();

public:
	virtual bool Init();

};

