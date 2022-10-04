
#include "ArrowLightEffect.h"
#include "ParticleAnimation.h"
#include "Scene/Scene.h"

CArrowLightEffect::CArrowLightEffect()	:
	m_FadeTime(1.f)
{
}

CArrowLightEffect::CArrowLightEffect(const CArrowLightEffect& obj)
{
}

CArrowLightEffect::~CArrowLightEffect()
{
}

void CArrowLightEffect::Start()
{
	CGameObject::Start();

}

bool CArrowLightEffect::Init()
{
	m_Billboard = CreateComponent<CBillboardComponent>("ArrowLightEffect");

	SetRootComponent(m_Billboard);

	m_Billboard->SetMaterial("Billboard");
	m_Billboard->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "LightHitPoint", TEXT("Billboard/LightHitPoint2.dds"));
	m_Billboard->SetWorldScale(10.f, 10.f, 1.f);


	return true;
}

void CArrowLightEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_FadeTime -= DeltaTime;

	m_Billboard->SetOpacity(m_FadeTime);

	if (m_FadeTime <= 0.f)
	{
		Destroy();
	}
}

CArrowLightEffect* CArrowLightEffect::Clone()
{
	return new CArrowLightEffect(*this);
}