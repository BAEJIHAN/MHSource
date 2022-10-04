#include "BurnedDecal.h"	
#include "FireEffect.h"
#include "Scene/Scene.h"	

CBurnedDecal::CBurnedDecal()
{
	SetTypeID<CBurnedDecal>();
}

CBurnedDecal::CBurnedDecal(const CBurnedDecal& obj)
{
}

CBurnedDecal::~CBurnedDecal()
{
}

void CBurnedDecal::PresetToExplosive()
{
	SetWorldScale(10.f, 1.f, 10.f);

	m_Decal->SetMaterial(m_Scene->GetResource()->FindMaterial("ShortBurntDecal"));

	CFireEffect* Fire = m_Scene->CreateGameObject<CFireEffect>("FireEffect");

	Fire->SetWorldPos(GetWorldPos());
}

void CBurnedDecal::PresetToGroundBurnt()
{
	SetWorldScale(10.f, 1.f, 70.f);

	m_Decal->SetMaterial(m_Scene->GetResource()->FindMaterial("BurntDecal"));
}

void CBurnedDecal::Start()
{
	CGameObject::Start();
}

bool CBurnedDecal::Init()
{
	if(!CGameObject::Init())
		return false;

	m_Decal = CreateComponent<CDecalComponent>("Decal");

	m_Decal->SetTransformState(Transform_State::Ground);
	m_Decal->SetFadeInTime(0.8f);
	m_Decal->SetDuration(10.f);
	m_Decal->SetFadeOutTime(3.f);
		
	SetWorldScale(10.f, 1.f, 10.f);

	return true;
}

void CBurnedDecal::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBurnedDecal::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}
