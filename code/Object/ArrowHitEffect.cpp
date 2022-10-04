
#include "ArrowHitEffect.h"
#include "ParticleAnimation.h"
#include "Scene/Scene.h"

CArrowHitEffect::CArrowHitEffect()
{
}

CArrowHitEffect::CArrowHitEffect(const CArrowHitEffect& obj)
{
}

CArrowHitEffect::~CArrowHitEffect()
{
}

bool CArrowHitEffect::Init()
{
	m_Billboard = CreateComponent<CBillboardComponent>("ArrowHitEffect");
	//m_Particle = CreateComponent<CParticleComponent>("ArrowHitEffect");

	//m_Billboard->AddChild(m_Particle);

	SetRootComponent(m_Billboard);

	m_Billboard->CreateAnimationInstance<CParticleAnimation>();
	m_Billboard->GetAnimationInstance()->ChangeAnimation("SparkBillboard5");

	m_Billboard->GetAnimationInstance()->SetEndFunction<CArrowHitEffect>("SparkBillboard5", this, &CArrowHitEffect::SetEndNotify);

	m_Billboard->SetWorldScale(10.f, 10.f, 1.f);

	return true;
}

void CArrowHitEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

CArrowHitEffect* CArrowHitEffect::Clone()
{
	return new CArrowHitEffect(*this);
}

void CArrowHitEffect::SetEndNotify()
{
	Destroy();
}
