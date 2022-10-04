#include "NormalArrowBillboard.h"
#include "ParticleAnimation.h"
#include "Scene/Scene.h"

CNormalArrowBillboard::CNormalArrowBillboard()
{
	SetTypeID<CNormalArrowBillboard>();
}

CNormalArrowBillboard::CNormalArrowBillboard(const CNormalArrowBillboard& obj) :
	CGameObject(obj)
{
}

CNormalArrowBillboard::~CNormalArrowBillboard()
{
}

void CNormalArrowBillboard::Start()
{
	CGameObject::Start();
}

bool CNormalArrowBillboard::Init()
{
	if (!CGameObject::Init())
	{
		return false;
	}

	m_Billboard = CreateComponent<CBillboardComponent>("NormalArrowBillboard");

	m_Billboard->CreateAnimationInstance<CParticleAnimation>();
	m_Billboard->GetAnimationInstance()->ChangeAnimation("FireBillboard11");
	m_Billboard->SetWorldScale(10.f, 10.f, 1.f);
	m_Billboard->SetBaseColor(1.f, 1.f, 1.f, 1.f);
	//m_Billboard->SetBaseColor(0.5f, 0.5f, 0.5f, 1.f);
	m_Billboard->SetOpacity(1.0f);
	m_Billboard->SetDuration(2.f);
	//m_Billboard->SetFadeInTime(2.f);
	m_Billboard->SetFadeOutTime(1.f);
	m_Billboard->SetBaseColor(1.f, 1.f, 1.f, 1.f);

	return true;
}

void CNormalArrowBillboard::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CNormalArrowBillboard::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}
