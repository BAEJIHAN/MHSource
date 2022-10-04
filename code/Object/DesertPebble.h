#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CDesertPebble :
	public CGameObject
{
	friend class CScene;

protected:
	CDesertPebble();
	CDesertPebble(const CDesertPebble& obj);
	virtual ~CDesertPebble();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

private:
	float	m_X;
	float	m_Y;
	float	m_Z;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CDesertPebble* Clone();
};

