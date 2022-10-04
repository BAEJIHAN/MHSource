
#include "BrokenTree2.h"

CBrokenTree2::CBrokenTree2()
{
	SetTypeID<CBrokenTree2>();
}

CBrokenTree2::CBrokenTree2(const CBrokenTree2& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("BrokenTree2Box");
}

CBrokenTree2::~CBrokenTree2()
{
}

bool CBrokenTree2::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("BrokenTree2Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(6.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, 0.f);
	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("BrokenTree2");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CBrokenTree2::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CBrokenTree2::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBrokenTree2* CBrokenTree2::Clone()
{
	return DBG_NEW CBrokenTree2(*this);
}
