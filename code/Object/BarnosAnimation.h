
#pragma once

#include "Animation\AnimationSequenceInstance.h"

class CBarnosAnimation :
	public CAnimationSequenceInstance
{
public:
	CBarnosAnimation();
	CBarnosAnimation(const CBarnosAnimation& Anim);
	~CBarnosAnimation();

public:
	virtual bool Init();
	virtual CBarnosAnimation* Clone();
};

