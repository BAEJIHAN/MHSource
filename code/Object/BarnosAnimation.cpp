#include "BarnosAnimation.h"


CBarnosAnimation::CBarnosAnimation()
{
	SetTypeID<CBarnosAnimation>();
}

CBarnosAnimation::CBarnosAnimation(const CBarnosAnimation& Anim) :
	CAnimationSequenceInstance(Anim)
{
}

CBarnosAnimation::~CBarnosAnimation()
{
}

/*

*/

bool CBarnosAnimation::Init()
{
	if (!CAnimationSequenceInstance::Init())
		return false;

	AddAnimation("barnosmain", "barnosmain", true, 2.f);
	AddAnimation("barnos1", "barnosidle1", true, 1.5f);
	AddAnimation("barnos2", "barnosfly1", true, 1.5f);
	AddAnimation("barnos3", "barnosgliding", true, 1.5f);
	AddAnimation("barnos4", "barnosfly2", true, 1.5f);
	AddAnimation("barnos5", "barnosattack1", true, 1.5f);
	AddAnimation("barnos6", "barnosidle2", true, 1.5f);
	AddAnimation("barnos7", "barnosascending", true, 1.7f);
	AddAnimation("barnos8", "barnos8", true, 1.5f);
	AddAnimation("barnos9", "barnos9", true, 1.5f);
	AddAnimation("barnos10", "barnos10", true, 1.5f);
	AddAnimation("barnos11", "barnos11", true, 1.5f);
	AddAnimation("barnos12", "barnosattack2", true, 2.6f);
	AddAnimation("barnos13", "barnosroll", true, 2.f);
	AddAnimation("barnos14", "barnosdead", false, 2.f);
	AddAnimation("barnos15", "barnoshit", true, 1.5f);
	AddAnimation("barnos16", "barnoshitdead", true, 0.9f);
	AddAnimation("barnos17", "barnos17", true, 1.5f);
	AddAnimation("barnos18", "barnosscream", true, 3.f);
	AddAnimation("barnos19", "barnosattack3", true, 3.f);
	


	return true;
}

CBarnosAnimation* CBarnosAnimation::Clone()
{
	return new CBarnosAnimation(*this);
}
