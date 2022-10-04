
#pragma once

#include "Animation\AnimationSequenceInstance.h"

class CMernosAnimation :
	public CAnimationSequenceInstance
{
public:
	CMernosAnimation();
	CMernosAnimation(const CMernosAnimation& Anim);
	~CMernosAnimation();

public:
	virtual bool Init();
	virtual CMernosAnimation* Clone();
};

