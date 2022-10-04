#include "ExplosionEffect.h"
#include "ParticleAnimation.h"
#include "Scene/Scene.h"

CExplosionEffect::CExplosionEffect() :
	m_LightOffTime(0.1f)
{
	SetTypeID<CExplosionEffect>();
}

CExplosionEffect::CExplosionEffect(const CExplosionEffect& obj) :
	CGameObject(obj)
{
}

CExplosionEffect::~CExplosionEffect()
{
}

void CExplosionEffect::Start()
{
	CGameObject::Start();
}

bool CExplosionEffect::Init()
{
	if (!CGameObject::Init())
	{
		return false;
	}

	m_Billboard = CreateComponent<CBillboardComponent>("ExplosionBillboard");
	m_Light = CreateComponent<CLightComponent>("PointLight");

	m_Billboard->CreateAnimationInstance<CParticleAnimation>();
	m_Billboard->GetAnimationInstance()->ChangeAnimation("ExplosionBillboard1");
	m_Billboard->SetWorldScale(30.f, 30.f, 1.f);
	m_Billboard->SetBaseColor(3.f, 3.f, 3.f, 1.f);
	m_Billboard->SetDuration(0.4f);
	m_Billboard->SetFadeOutTime(0.4f);

	m_Light->SetLightType(Light_Type::Point);
	m_Light->SetDistance(150.f);
	m_Light->SetAtt3(0.02f);
	m_Light->SetColor(Vector4(1.f, 0.71f, 0.f, 1.f));


	m_Billboard->AddChild(m_Light);

	return true;
}

void CExplosionEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_LightOffTime -= DeltaTime;

	if (m_LightOffTime <= 0.f)
	{
		m_Light->Enable(false);
	}
}

void CExplosionEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}