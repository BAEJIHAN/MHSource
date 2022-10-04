
#include "Box1.h"


CBox1::CBox1()
{
	SetTypeID<CBox1>();

	m_XLength = 0.f;
	m_YLength = 0.f;
	m_ZLength = 0.f;
}

CBox1::CBox1(const CBox1& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Box1");
}

CBox1::~CBox1()
{
}

bool CBox1::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Box1Collider");

	m_Mesh->SetMesh("Box1");
	m_Mesh->SetRelativeScale(0.04f, 0.04f, 0.04f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(6.f, 6.f, 6.f);
	m_ColliderBox->SetOffset(0.f, 1.f, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->AddChild(m_ColliderBox);

	return true;
}

void CBox1::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);



	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_XLength -= 0.1f;

	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_XLength += 0.1f;
	}


	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_YLength -= 0.1f;

	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_YLength += 0.1f;
	}

	if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
	{
		m_ZLength -= 0.1f;

	}

	if (GetAsyncKeyState(VK_NUMPAD9) & 0x8000)
	{
		m_ZLength += 0.1f;
	}

	m_ColliderBox->Set3DExtent(m_XLength, m_YLength, m_ZLength);
}

void CBox1::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBox1* CBox1::Clone()
{
	return DBG_NEW CBox1(*this);
}
