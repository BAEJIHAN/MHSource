#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CBrokenTree3 :
    public CGameObject
{
	friend class CScene;

protected:
	CBrokenTree3();
	CBrokenTree3(const CBrokenTree3& obj);
	virtual ~CBrokenTree3();

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
	virtual CBrokenTree3* Clone();
};

