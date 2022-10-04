
#include "PlayerAnimation.h"

CPlayerAnimation::CPlayerAnimation()
{
	SetTypeID<CPlayerAnimation>();
}

CPlayerAnimation::CPlayerAnimation(const CPlayerAnimation& Anim) :
	CAnimationSequenceInstance(Anim)
{
}

CPlayerAnimation::~CPlayerAnimation()
{
}

bool CPlayerAnimation::Init()
{
	if (!CAnimationSequenceInstance::Init())
		return false;

	//AddAnimation("BHTest1Run", "BHTest1Run", true, 2.f);

	AddAnimation("BHIdle", "BHIdle", true, 2.f);
	AddAnimation("BHWalk", "BHWalk", true, 2.f);
	AddAnimation("BHWalkEnd", "BHWalkEnd", false, 1.f);
	AddAnimation("BHShot", "BHShot", true);
	AddAnimation("TestIdle", "TestIdle", false);
	AddAnimation("BHRunStart", "BHRunStart", false, 1.0f);
	AddAnimation("BHRun", "BHRun", true, 0.8f);
	AddAnimation("BHRunQuick", "BHRunQuick", true, 0.7f);
	AddAnimation("BHRunEnd", "BHRunEnd", false, 0.5f);
	AddAnimation("BHEvade", "BHEvade", false, 1.1f);

	// wp
	AddAnimation("BHKick", "BHKick", false, 1.3f);
	AddAnimation("BHShot", "BHShot", false, 1.3f);
	AddAnimation("BHAimChargingWalkFront", "BHAimChargingWalkFront", true, 1.3f);
	AddAnimation("BHAimChargingWalkBack", "BHAimChargingWalkBack", true, 1.3f);
	AddAnimation("BHAimChargingWalkLeft", "BHAimChargingWalkLeft", true, 1.3f);
	AddAnimation("BHAimChargingWalkRight", "BHAimChargingWalkRight", true, 1.3f);
	AddAnimation("BHAimIdle", "BHAimIdle", true, 1.3f);
	AddAnimation("BHAimIdleToSlingerAim", "BHAimIdleToSlingerAim", false, 1.3f);
	AddAnimation("BHAimIdleToIdle", "BHAimIdleToIdle", false, 1.3f);
	AddAnimation("BHAimLoopArcShot", "BHAimLoopArcShot", false, 1.3f);
	AddAnimation("BHAimStartArcShot", "BHAimStartArcShot", false, 1.3f);
	AddAnimation("BHAimWalkFront", "BHAimWalkFront", true, 1.3f);
	AddAnimation("BHAimWalkBack", "BHAimWalkBack", true, 1.3f);
	AddAnimation("BHAimWalkLeft", "BHAimWalkLeft", true, 1.3f);
	AddAnimation("BHAimWalkRight", "BHAimWalkRight", true, 1.3f);
	AddAnimation("BHAimWalkLeftEnd", "BHAimWalkLeftEnd", false, 1.3f);
	AddAnimation("BHAimWalkRightEnd", "BHAimWalkRightEnd", false, 1.3f);
	AddAnimation("BHChargedShotIdle", "BHChargedShotIdle", false, 1.f);
	AddAnimation("BHChargingFrontStep", "BHChargingFrontStep", false, 1.3f);
	AddAnimation("BHChargingFrontStepShot", "BHChargingFrontStepShot", false, 1.3f);
	AddAnimation("BHChargingBackStep", "BHChargingBackStep", false, 1.3f);
	AddAnimation("BHChargingBackStepShot", "BHChargingBackStepShot", false, 1.3f);
	AddAnimation("BHChargingIdleToChargingWalk", "BHChargingIdleToChargingWalk", false, 1.3f);
	AddAnimation("BHChargingLeftStep", "BHChargingLeftStep", false, 1.3f);
	AddAnimation("BHChargingLeftStepShot", "BHChargingLeftStepShot", false, 1.3f);
	AddAnimation("BHChargingRightStep", "BHChargingRightStep", false, 1.3f);
	AddAnimation("BHChargingRightStepShot", "BHChargingRightStepShot", false, 1.3f);
	AddAnimation("BHChargingStartIdle", "BHChargingStartIdle", false, 1.1f);
	AddAnimation("BHChargingStartIdleFirst", "BHChargingStartIdleFirst", false, 1.1f);
	AddAnimation("BHChargingWalk", "BHChargingWalk", true, 0.9f);
	AddAnimation("BHChargingWalkEnd", "BHChargingWalkEnd", false, 1.f);
	AddAnimation("BHChargingWalkLeftEnd", "BHChargingWalkLeftEnd", false, 1.3f);
	AddAnimation("BHChargingWalkRightEnd", "BHChargingWalkRightEnd", false, 1.3f);
	AddAnimation("BHFullChargingIdleLoop", "BHFullChargingIdleLoop", true, 1.f);
	AddAnimation("BHFullChargedShotIdle", "BHFullChargedShotIdle", false, 1.1f);
	AddAnimation("BHPowerShot", "BHPowerShot", false, 1.3f);
	AddAnimation("BHQuickShot", "BHQuickShot", false, 1.3f);

	// Drawed
	AddAnimation("BHDrawedBackStep", "BHDrawedBackStep", false, 1.3f);
	AddAnimation("BHDrawedEvade", "BHDrawedEvade", false, 1.15f);
	AddAnimation("BHDrawedEvadeToDrawedWalkStart", "BHDrawedEvadeToDrawedWalkStart", false, 0.7f);
	AddAnimation("BHDrawedEvadeToDrawedWalk", "BHDrawedEvadeToDrawedWalk", false, 0.9f);
	AddAnimation("BHDrawedIdle", "BHDrawedIdle", true, 1.1f);
	AddAnimation("BHDrawedWalk", "BHDrawedWalk", true, 0.9f);
	AddAnimation("BHDrawedWalkAndSheathe", "BHDrawedWalkAndSheathe", false, 1.3f);
	AddAnimation("BHDrawedWalkEnd", "BHDrawedWalkEnd", false, 1.3f);
	AddAnimation("BHDrawedWalkStart", "BHDrawedWalkStart", false, 2.f);
	AddAnimation("BHDrawnEvadeFront", "BHDrawnEvadeFront", false, 1.3f);
	AddAnimation("BHDrawnHitFront", "BHDrawnHitFront", false, 1.3f);
	AddAnimation("BHDrawWeapon", "BHDrawWeapon", false, 1.3f);
	AddAnimation("BHWalkAndDrawWeapon", "BHWalkAndDrawWeapon", false, 0.8f);
	AddAnimation("BHDrawedWeaponToCharging", "BHDrawedWeaponToCharging", false, 0.7f);
	AddAnimation("BHDrawedToChargingStart", "BHDrawedToChargingStart", false, 1.f);
	AddAnimation("BHDrawnWalkToChargingStart", "BHDrawnWalkToChargingStart", false, 1.7f);

	// Dragon
	AddAnimation("BHDragonShotStart", "BHDragonShotStart", false, 4.f);
	AddAnimation("BHDragonShot", "BHDragonShot", false, 1.5f);

	AddAnimation("BHSheathe", "BHSheathe", false, 1.f);

	AddAnimation("BHCoating", "BHCoating", false, 2.f);

	// Carving
	AddAnimation("BHCarvingStart", "BHCarvingStart", false, 3.f);
	AddAnimation("BHCarvingLoop", "BHCarvingLoop", false, 2.f);
	AddAnimation("BHCarvingEnd", "BHCarvingEnd", false, 2.f);

	// Hit
	AddAnimation("BHTrippingByFront", "BHTrippingByFront", false, 1.5f);
	AddAnimation("BHTrippingToIdle", "BHTrippingToIdle", false, 1.8f);
	AddAnimation("BHRollByFrontStart", "BHRollByFrontStart", false, 1.f);
	AddAnimation("BHRollByFrontEnd", "BHRollByFrontEnd", false, 1.f);
	AddAnimation("BHRollOverToIdle", "BHRollOverToIdle", false, 1.5f);
	AddAnimation("BHRollOverLoop", "BHRollOverLoop", true, 2.f);
	AddAnimation("BHRollOverByFrontEnd", "BHRollOverByFrontEnd", false, 2.f);

	AddAnimation("BHPlugEarsStart", "BHPlugEarsStart", false, 2.f);
	AddAnimation("BHPlugEarsLoop", "BHPlugEarsLoop", true, 5.f);
	AddAnimation("BHPlugEarsToIdle", "BHPlugEarsToIdle", false, 1.5f);

	// 메르노스
	AddAnimation("BHDown1", "BHDown1", false, 1.5f);
	AddAnimation("BHDown2", "BHDown2", false, 1.5f);
	AddAnimation("BHDown3", "BHDown3", false, 2.2f);
	AddAnimation("BHUp1", "BHUp1", false, 0.5f);

	AddAnimation("TestIdle", "TestIdle");

	return true;
}

CPlayerAnimation* CPlayerAnimation::Clone()
{
	return new CPlayerAnimation(*this);
}
