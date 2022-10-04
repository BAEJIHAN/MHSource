
#include "AnjanathAnimation.h"
#include "Component/AnimationMeshComponent.h"
#include "Scene/Scene.h"

CAnjanathAnimation::CAnjanathAnimation()
{
	SetTypeID<CAnjanathAnimation>();
}

CAnjanathAnimation::CAnjanathAnimation(const CAnjanathAnimation& Anim) :
	CAnimationSequenceInstance(Anim)
{
}

CAnjanathAnimation::~CAnjanathAnimation()
{
}

bool CAnjanathAnimation::Init()
{
	if (!CAnimationSequenceInstance::Init())
		return false;

	AddAnimation("AnjanathNormalIdle", "NormalIdle", true, 1.f);
	AddAnimation("AnjanathNormalTurnLeft", "NormalTurnLeft", false, 1.f);
	AddAnimation("AnjanathNormalTurnRight", "NormalTurnRight", false, 1.f);
	AddAnimation("AnjanathNormalTurnBack", "NormalTurnBack", true, 1.f);
	AddAnimation("AnjanathNormalMoveStart", "NormalMoveStart", false, 3.f);
	AddAnimation("AnjanathNormalMoveLoop", "NormalMoveLoop", true, 4.f);
	AddAnimation("AnjanathNormalMoveEnd", "NormalMoveEnd", false, 1.f);
	AddAnimation("AnjanathNormalMoveStartToLeft", "NormalMoveStartToLeft", false, 2.f);
	AddAnimation("AnjanathNormalMoveStartToRight", "NormalMoveStartToRight", false, 2.f);
	AddAnimation("AnjanathRoaring", "Roaring", false, 7.f);

	AddAnimation("AnjanathAgressiveIdle", "AgressiveIdle", true, 1.f);
	AddAnimation("AnjanathAgressiveMoveStart", "AgressiveMoveStart", false, 3.f);
	AddAnimation("AnjanathAgressiveTurnLeft", "AgressiveTurnLeft", false, 1.1f);
	AddAnimation("AnjanathAgressiveTurnRight", "AgressiveTurnRight", false, 1.1f);
	AddAnimation("AnjanathAgressiveTurnEnd", "AgressiveTurnEnd", false, 1.0f);

	AddAnimation("AnjanathAttackDashStart", "AttackDashStart", false, 2.f);
	AddAnimation("AnjanathAttackDashEnd", "AttackDashEnd", false, 1.f);

	AddAnimation("AnjanathTripleBiteStart", "TripleBiteStart", false, 1.f);
	AddAnimation("AnjanathTripleBite1", "TripleBite1", false, 1.f);
	AddAnimation("AnjanathTripleBite2", "TripleBite2", false, 1.f);
	AddAnimation("AnjanathTripleBiteV2End", "TripleBiteEndV2", false, 4.f);
	AddAnimation("AnjanathTripleBiteEnd", "TripleBiteEnd", false, 2.0f);

	AddAnimation("AnjanathCriticalDamaged", "CriticalDamaged", false, 3.0f);
	AddAnimation("AnjanathCriticalDamaged2", "CriticalDamaged2", false, 3.0f);
	AddAnimation("AnjanathCriticalDamagedInAttack", "CriticalDamagedInAttack", false, 3.5f);

	AddAnimation("AnjanathBreathReady", "BreathReady", false, 1.8f);
	AddAnimation("AnjanathBreathAttack", "BreathAttack", false, 4.f);

	AddAnimation("AnjanathDeath", "Dead", false, 5.f);

	return true;
}
