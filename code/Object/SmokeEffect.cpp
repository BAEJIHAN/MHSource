#include "SmokeEffect.h"
#include "ParticleAnimation.h"
#include "Scene/Scene.h"

CSmokeEffect::CSmokeEffect()
{
	SetTypeID<CSmokeEffect>();
}

CSmokeEffect::CSmokeEffect(const CSmokeEffect& obj) :
	CGameObject(obj)
{
}

CSmokeEffect::~CSmokeEffect()
{
}

void CSmokeEffect::Start()
{
	CGameObject::Start();
}

bool CSmokeEffect::Init()
{
	if (!CGameObject::Init())
	{
		return false;
	}

	m_Billboard = CreateComponent<CBillboardComponent>("SmokeBillboard");

	m_Billboard->CreateAnimationInstance<CParticleAnimation>();
	m_Billboard->GetAnimationInstance()->ChangeAnimation("SmokeBillboard4");
	m_Billboard->SetWorldScale(40.f, 40.f, 1.f);
	m_Billboard->SetOpacity(0.f);
	m_Billboard->SetFadeState(Fade_State::FadeIn);
	m_Billboard->SetFadeInTime(1.0f);
	m_Billboard->SetDuration(0.1f);
	m_Billboard->SetFadeOutTime(2.5f);

	return true;
}

void CSmokeEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CSmokeEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}
