
#include "FieldObj.h"
#include "PlayerAnimation.h"
#include "Input.h"
#include "Resource/Animation/AnimationSequence.h"

CFieldObj::CFieldObj()
{
	SetTypeID<CFieldObj>();
}

CFieldObj::CFieldObj(const CFieldObj& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("FieldObjBox");
}

CFieldObj::~CFieldObj()
{
}

bool CFieldObj::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("FieldObjBox");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(3.f, 4.f, 3.f);
	m_ColliderBox->SetOffset(0.f, 4.f, 0.f);

	m_Mesh->SetMesh("Obj1");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(-3.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CFieldObj::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CFieldObj::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CFieldObj* CFieldObj::Clone()
{
	return new CFieldObj(*this);
}
