#include "TestObj.h"
#include "Input.h"


CTestObj::CTestObj()
{
	SetTypeID<CTestObj>();
}

CTestObj::CTestObj(const CTestObj& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("testmesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("testcollider");
}

CTestObj::~CTestObj()
{
}

bool CTestObj::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("testmesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("testcollider");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(11.f, 16.f, 11.f);
	m_ColliderBox->SetOffset(0.f, 10.f, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("testdummy");

	m_Mesh->SetRelativeScale(0.03f, 0.03f, 0.03f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);



	return true;
}

void CTestObj::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CTestObj::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTestObj* CTestObj::Clone()
{
	return new CTestObj(*this);
}
