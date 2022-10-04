#include "FireEffect.h"
#include "ParticleAnimation.h"
#include "Scene/Scene.h"

CFireEffect::CFireEffect()
{
	SetTypeID<CFireEffect>();
}

CFireEffect::CFireEffect(const CFireEffect& obj) :
	CGameObject(obj)
{
}

CFireEffect::~CFireEffect()
{
}

void CFireEffect::Start()
{
	CGameObject::Start();
}

bool CFireEffect::Init()
{
	if (!CGameObject::Init())
	{
		return false;
	}

	m_Billboard = CreateComponent<CBillboardComponent>("FireBillboard");

	m_Billboard->CreateAnimationInstance<CParticleAnimation>();
	m_Billboard->GetAnimationInstance()->ChangeAnimation("FireBillboard6");
	m_Billboard->SetWorldScale(15.f, 10.f, 1.f);
	m_Billboard->SetBaseColor(3.f, 3.f, 3.f, 1.f);
	m_Billboard->SetOpacity(1.0f);
	m_Billboard->SetDuration(4.0f);
	m_Billboard->SetFadeOutTime(1.2f);

	return true;
}

void CFireEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CFireEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}
