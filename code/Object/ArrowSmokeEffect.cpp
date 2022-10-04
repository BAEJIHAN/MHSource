
#include "ArrowSmokeEffect.h"
#include "ParticleAnimation.h"
#include "Scene/Scene.h"

CArrowSmokeEffect::CArrowSmokeEffect()	:
	m_CollisionEnable(false),
	m_Time(1.f)
{
}

CArrowSmokeEffect::CArrowSmokeEffect(const CArrowSmokeEffect& obj)
{
}

CArrowSmokeEffect::~CArrowSmokeEffect()
{
}

bool CArrowSmokeEffect::Init()
{
	m_Billboard = CreateComponent<CBillboardComponent>("ArrowSmokeEffect");

	SetRootComponent(m_Billboard);

	m_Billboard->CreateAnimationInstance<CParticleAnimation>();
	m_Billboard->GetAnimationInstance()->ChangeAnimation("SmokeBillboard1");

	m_Billboard->GetAnimationInstance()->SetEndFunction<CArrowSmokeEffect>("SmokeBillboard1", this, &CArrowSmokeEffect::SetEndNotify);

	m_Billboard->SetWorldScale(13.f, 13.f, 1.f);

	return true;
}

void CArrowSmokeEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_CollisionEnable)
	{
		m_Time -= DeltaTime;
		m_Billboard->SetOpacity(m_Time);

		if (m_Time <= 0.f)
			Destroy();
	}
}

CArrowSmokeEffect* CArrowSmokeEffect::Clone()
{
	return new CArrowSmokeEffect(*this);
}

void CArrowSmokeEffect::SetEndNotify()
{
	m_CollisionEnable = true;
	//Destroy();
}
