#pragma once

#include "Animation\AnimationSequenceInstance.h"

class CVespoidAnimation :
	public CAnimationSequenceInstance
{
public:
	CVespoidAnimation();
	CVespoidAnimation(const CVespoidAnimation& Anim);
	~CVespoidAnimation();

public:
	virtual bool Init();
	virtual CVespoidAnimation* Clone();
};

