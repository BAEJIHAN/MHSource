
#include "DesertPebble.h"

CDesertPebble::CDesertPebble()
{
	SetTypeID<CDesertPebble>();

	m_X = 1.f;
	m_Y = 1.f;
	m_Z = 1.f;
}

CDesertPebble::CDesertPebble(const CDesertPebble& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("DesertPebbleBox");
}

CDesertPebble::~CDesertPebble()
{
}

bool CDesertPebble::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("DesertPebbleBox");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->Set3DExtent(10.f);
	m_ColliderBox->SetRelativePos(0.f, 0.f, m_ColliderBox->GetInfo().Length.z);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("DesertPebble1");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CDesertPebble::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_X -= 0.1f;

	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_X += 0.1f;

	}


	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_Y -= 0.1f;

	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_Y += 0.1f;
	}

	if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
	{
		m_Z -= 0.1f;

	}

	if (GetAsyncKeyState(VK_NUMPAD9) & 0x8000)
	{
		m_Z += 0.1f;

	}

	//m_ColliderBox->Set3DExtent(m_X, m_Y, m_Z);
}

void CDesertPebble::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDesertPebble* CDesertPebble::Clone()
{
	return DBG_NEW CDesertPebble(*this);
}
