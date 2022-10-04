
#include "ParticleAnimation.h"

CParticleAnimation::CParticleAnimation()
{
}

CParticleAnimation::CParticleAnimation(const CParticleAnimation& Anim) :
	CAnimationSequence2DInstance(Anim)
{
}

CParticleAnimation::~CParticleAnimation()
{
}

bool CParticleAnimation::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

	AddAnimation("SmokeBillboard1", "SmokeBillboard1", true, 1.f);
	AddAnimation("SmokeBillboard2", "SmokeBillboard2", true, 1.f);
	AddAnimation("SmokeBillboard3", "SmokeBillboard3", true, 2.f);
	AddAnimation("SmokeBillboard4", "SmokeBillboard4", true, 2.f);
	AddAnimation("SmokeBillboard5", "SmokeBillboard5", true, 2.f);
	AddAnimation("SmokeBillboard6", "SmokeBillboard6", true, 2.f);
	AddAnimation("SmokeBillboard7", "SmokeBillboard7", true, 1.f);
	AddAnimation("SmokeBillboard8", "SmokeBillboard8", true, 2.f);
	AddAnimation("SmokeBillboard9", "SmokeBillboard9", true, 2.f);

	AddAnimation("LiquidBillboard1", "LiquidBillboard1", false, 1.f);
	AddAnimation("LiquidBillboard2", "LiquidBillboard2", false, 1.f);
	AddAnimation("LiquidBillboard3", "LiquidBillboard3", false, 2.f);
	AddAnimation("LiquidBillboard4", "LiquidBillboard4", false, 2.f);
	AddAnimation("LiquidBillboard5", "LiquidBillboard5", false, 2.f);
	AddAnimation("LiquidBillboard6", "LiquidBillboard6", false, 2.f);
	AddAnimation("LiquidBillboard7", "LiquidBillboard7", false, 2.f);
	AddAnimation("LiquidBillboard8", "LiquidBillboard8", false, 2.f);
	AddAnimation("LiquidBillboard9", "LiquidBillboard9", false, 2.f);
	AddAnimation("LiquidBillboard10", "LiquidBillboard10", false, 0.3f);

	AddAnimation("ElecBillboard1", "ElecBillboard1", true, 1.f);

	AddAnimation("SparkBillboard1", "SparkBillboard1", false, 0.5f);
	AddAnimation("SparkBillboard2", "SparkBillboard2", true, 0.3f);
	AddAnimation("SparkBillboard3", "SparkBillboard3", false, 0.5f);
	AddAnimation("SparkBillboard4", "SparkBillboard4", false, 0.3f);
	AddAnimation("SparkBillboard5", "SparkBillboard5", false, 0.3f);
	AddAnimation("SparkBillboard6", "SparkBillboard6", false, 0.3f);
	AddAnimation("SparkBillboard7", "SparkBillboard7", false, 0.3f);

	AddAnimation("EtcBillboard1", "EtcBillboard1", true, 1.8f);
	AddAnimation("FlameBillboard1", "FlameBillboard1", true, 1.8f);

	AddAnimation("FireBillboard1", "FireBillboard1", true, 1.0f);
	AddAnimation("FireBillboard2", "FireBillboard2", true, 1.0f);
	AddAnimation("FireBillboard3", "FireBillboard3", true, 1.0f);
	AddAnimation("FireBillboard4", "FireBillboard4", true, 1.0f);
	AddAnimation("FireBillboard5", "FireBillboard5", true, 1.0f);
	AddAnimation("FireBillboard6", "FireBillboard6", true, 1.0f);
	AddAnimation("FireBillboard7", "FireBillboard7", true, 1.0f);
	AddAnimation("FireBillboard8", "FireBillboard8", true, 1.0f);
	AddAnimation("FireBillboard9", "FireBillboard9", true, 1.0f);
	AddAnimation("FireBillboard10", "FireBillboard10", true, 1.0f);
	AddAnimation("FireBillboard11", "FireBillboard11", true, 3.0f);
	AddAnimation("FireBillboard12", "FireBillboard12", true, 1.0f);

	AddAnimation("HitBreath", "HitBreath", true, 2.5f);

	AddAnimation("ExplosionBillboard1", "ExplosionBillboard1", false, 0.7f);

	return true;
}

CParticleAnimation* CParticleAnimation::Clone()
{
	return new CParticleAnimation(*this);
}
