#pragma once

#include "Animation\AnimationSequenceInstance.h"

class CJagrasAnimation :
	public CAnimationSequenceInstance
{
public:
	CJagrasAnimation();
	CJagrasAnimation(const CJagrasAnimation& Anim);
	~CJagrasAnimation();

public:
	virtual bool Init();
	virtual CJagrasAnimation* Clone();
};

