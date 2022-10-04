#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CTree9 :
    public CGameObject
{
	friend class CScene;

protected:
	CTree9();
	CTree9(const CTree9& obj);
	virtual ~CTree9();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

private:
	float	m_XLength;
	float	m_YLength;
	float	m_ZLength;


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CTree9* Clone();
};

