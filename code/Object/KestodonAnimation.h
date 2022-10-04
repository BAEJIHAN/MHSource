#pragma once

#include "Animation\AnimationSequenceInstance.h"

class CKestodonAnimation :
	public CAnimationSequenceInstance
{
public:
	CKestodonAnimation();
	CKestodonAnimation(const CKestodonAnimation& Anim);
	~CKestodonAnimation();

public:
	virtual bool Init();
	virtual CKestodonAnimation* Clone();
};

