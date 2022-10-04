
#include "WeaponAnimation.h"

CWeaponAnimation::CWeaponAnimation()
{
	SetTypeID<CWeaponAnimation>();
}

CWeaponAnimation::CWeaponAnimation(const CWeaponAnimation& Anim) :
	CAnimationSequenceInstance(Anim)
{
}

CWeaponAnimation::~CWeaponAnimation()
{
}

bool CWeaponAnimation::Init()
{
	if (!CAnimationSequenceInstance::Init())
		return false;

	AddAnimation("BowBack", "BowBack", false, 1.7f);
	AddAnimation("BowOpen", "BowOpen", false, 0.9f);
	AddAnimation("BowClose", "BowClose", false, 0.9f);
	AddAnimation("BowShot", "BowShot", false, 0.9f);
	AddAnimation("BowChargingLoop", "BowChargingLoop", true, 0.9f);
	AddAnimation("BowChargingStart", "BowChargingStart", false, 2.1f);
	AddAnimation("BowChargingToIdle", "BowChargingToIdle", false, 0.9f);

	return true;
}

CWeaponAnimation* CWeaponAnimation::Clone()
{
	return new CWeaponAnimation(*this);
}
