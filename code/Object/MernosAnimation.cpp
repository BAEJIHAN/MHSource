#include "MernosAnimation.h"

CMernosAnimation::CMernosAnimation()
{
	SetTypeID<CMernosAnimation>();
}

CMernosAnimation::CMernosAnimation(const CMernosAnimation& Anim) :
	CAnimationSequenceInstance(Anim)
{
}

CMernosAnimation::~CMernosAnimation()
{
}


bool CMernosAnimation::Init()
{
	if (!CAnimationSequenceInstance::Init())
		return false;
		
	AddAnimation("mernos1", "mernosidle", true, 2.f);
	AddAnimation("mernos2", "mernosascend", true, 2.f);
	AddAnimation("mernos3", "mernosleave", true, 2.f);
	AddAnimation("mernos4", "mernosgliding", true, 2.f);
	AddAnimation("mernos5", "mernospickup", true, 2.f);




	return true;
}

CMernosAnimation* CMernosAnimation::Clone()
{
	return new CMernosAnimation(*this);
}
