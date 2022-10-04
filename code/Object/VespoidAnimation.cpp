
#include "VespoidAnimation.h"

CVespoidAnimation::CVespoidAnimation()
{
	SetTypeID<CVespoidAnimation>();
}

CVespoidAnimation::CVespoidAnimation(const CVespoidAnimation& Anim) :
	CAnimationSequenceInstance(Anim)
{
}

CVespoidAnimation::~CVespoidAnimation()
{
}


bool CVespoidAnimation::Init()
{
	if (!CAnimationSequenceInstance::Init())
		return false;

	AddAnimation("vespoid1", "vespoidfly1", true, 2.f);
	AddAnimation("vespoid2", "vespoidfly2", true, 2.f);
	AddAnimation("vespoid3", "vespoid3", true, 2.f);
	AddAnimation("vespoid4", "vespoid4", true, 2.f);
	AddAnimation("vespoid5", "vespoididle2", true, 2.f);
	AddAnimation("vespoid6", "vespoidscream", true, 2.f);
	AddAnimation("vespoid7", "vespoidfly3", true, 2.f);
	AddAnimation("vespoid8", "vespoidlegup", true, 1.5f);
	AddAnimation("vespoid9", "vespoididle1", true, 6.f);
	AddAnimation("vespoid10", "vespoid10", true, 2.f);
	AddAnimation("vespoid11", "vespoidattack1", true, 3.f);
	AddAnimation("vespoid12", "vespoidattack2", true, 5.f);
	AddAnimation("vespoid13", "vespoidhit1", true, 2.f);
	AddAnimation("vespoid14", "vespoiddeath1", true, 0.5f);
	AddAnimation("vespoid15", "vespoiddeath2", false, 2.f);
	AddAnimation("vespoid16", "vespoid16", true, 2.f);
	AddAnimation("vespoid17", "vespoid17", true, 2.f);
	AddAnimation("vespoid18", "vespoiddeath3", true, 2.f);
	

	

	return true;
}

CVespoidAnimation* CVespoidAnimation::Clone()
{
	return new CVespoidAnimation(*this);
}
