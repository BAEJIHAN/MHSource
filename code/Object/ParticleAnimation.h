#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class CParticleAnimation :
    public CAnimationSequence2DInstance
{
public:
	CParticleAnimation();
	CParticleAnimation(const CParticleAnimation& Anim);
	~CParticleAnimation();

public:
	virtual bool Init();
	virtual CParticleAnimation* Clone();
};

