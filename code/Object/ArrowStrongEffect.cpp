
#include "ArrowStrongEffect.h"
#include "ParticleAnimation.h"
#include "Scene/Scene.h"

CArrowStrongEffect::CArrowStrongEffect() :
	m_CollisionEnable(false),
	m_Time(0.9f)
{
}

CArrowStrongEffect::CArrowStrongEffect(const CArrowStrongEffect& obj)
{
}

CArrowStrongEffect::~CArrowStrongEffect()
{
}

bool CArrowStrongEffect::Init()
{
	m_Billboard = CreateComponent<CBillboardComponent>("ArrowStrongEffect");
	//m_Particle = CreateComponent<CParticleComponent>("ArrowStrongEffect");

	//m_Billboard->AddChild(m_Particle);

	SetRootComponent(m_Billboard);

	m_Billboard->CreateAnimationInstance<CParticleAnimation>();
	m_Billboard->GetAnimationInstance()->ChangeAnimation("SmokeBillboard4");

	m_Billboard->GetAnimationInstance()->SetEndFunction<CArrowStrongEffect>("SmokeBillboard4", this, &CArrowStrongEffect::SetEndNotify);

	m_Billboard->SetWorldScale(11.f, 11.f, 1.f);
	m_Billboard->SetOpacity(m_Time);

	return true;
}

void CArrowStrongEffect::Update(float DeltaTime)
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

CArrowStrongEffect* CArrowStrongEffect::Clone()
{
	return new CArrowStrongEffect(*this);
}

void CArrowStrongEffect::SetEndNotify()
{
	m_CollisionEnable = true;
}
