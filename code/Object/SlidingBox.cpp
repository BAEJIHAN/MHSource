
#include "SlidingBox.h"
#include "Scene/Scene.h"

CSlidingBox::CSlidingBox()
{
	SetTypeID<CSlidingBox>();
}

CSlidingBox::CSlidingBox(const CSlidingBox& obj)
{
	m_ColliderBox = (CColliderBox3D*)FindComponent("SlidingBoxBox");
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
}

CSlidingBox::~CSlidingBox()
{
}

bool CSlidingBox::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("SlidingBoxBox");

	m_Mesh->AddChild(m_ColliderBox);
	m_Mesh->SetMesh("Blank");
	
	m_ColliderBox->Set3DExtent(3.f, 3.f, 3.f);
	m_ColliderBox->SetWorldPos(0.f, m_ColliderBox->GetInfo().Length.z, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CSlidingBox::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CSlidingBox::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CSlidingBox* CSlidingBox::Clone()
{
	return DBG_NEW CSlidingBox(*this);
}
