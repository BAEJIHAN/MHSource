#include "SparkEffect.h"
#include "ParticleAnimation.h"
#include "Scene/Scene.h"

CSparkEffect::CSparkEffect()
{
	SetTypeID<CSparkEffect>();
}

CSparkEffect::CSparkEffect(const CSparkEffect& obj) :
	CGameObject(obj)
{
}

CSparkEffect::~CSparkEffect()
{
}

void CSparkEffect::Start()
{
	CGameObject::Start();
}

bool CSparkEffect::Init()
{
	if (!CGameObject::Init())
	{
		return false;
	}

	m_Billboard = CreateComponent<CBillboardComponent>("SparkBillboard");

	m_Billboard->CreateAnimationInstance<CParticleAnimation>();
	m_Billboard->GetAnimationInstance()->ChangeAnimation("SparkBillboard5");
	m_Billboard->SetWorldScale(20.f, 20.f, 1.f);
	m_Billboard->SetBaseColor(1.f, 1.f, 1.f, 1.f);
	m_Billboard->SetOpacity(1.0f);
	m_Billboard->SetDuration(0.5f);

	
	return true;
}

void CSparkEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CSparkEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}