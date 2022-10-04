#pragma once

#include "Animation/AnimationSequenceInstance.h"

class CWeaponAnimation :
    public CAnimationSequenceInstance
{
public:
	CWeaponAnimation();
	CWeaponAnimation(const CWeaponAnimation& Anim);
	~CWeaponAnimation();

public:
	virtual bool Init();
	virtual CWeaponAnimation* Clone();
};

