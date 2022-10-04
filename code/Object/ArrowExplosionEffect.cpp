
#include "ArrowExplosionEffect.h"
#include "ParticleAnimation.h"
#include "Scene/Scene.h"

CArrowExplosionEffect::CArrowExplosionEffect() :
	m_CollisionEnable(false),
	m_Time(1.f)
{
}

CArrowExplosionEffect::CArrowExplosionEffect(const CArrowExplosionEffect& obj)
{
}

CArrowExplosionEffect::~CArrowExplosionEffect()
{
}

bool CArrowExplosionEffect::Init()
{
	m_Billboard = CreateComponent<CBillboardComponent>("ArrowExplosionEffect");
	//m_Particle = CreateComponent<CParticleComponent>("ArrowExplosionEffect");

	//m_Billboard->AddChild(m_Particle);

	SetRootComponent(m_Billboard);

	m_Billboard->CreateAnimationInstance<CParticleAnimation>();
	m_Billboard->GetAnimationInstance()->ChangeAnimation("ExplosionBillboard1");

	m_Billboard->GetAnimationInstance()->SetEndFunction<CArrowExplosionEffect>("ExplosionBillboard1", this, &CArrowExplosionEffect::SetEndNotify);

	m_Billboard->SetWorldScale(13.f, 13.f, 1.f);

	return true;
}

void CArrowExplosionEffect::Update(float DeltaTime)
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

CArrowExplosionEffect* CArrowExplosionEffect::Clone()
{
	return new CArrowExplosionEffect(*this);
}

void CArrowExplosionEffect::SetEndNotify()
{
	m_CollisionEnable = true;
}
