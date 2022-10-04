#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CSmallTree1 :
	public CGameObject
{
	friend class CScene;

protected:
	CSmallTree1();
	CSmallTree1(const CSmallTree1& obj);
	virtual ~CSmallTree1();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CSmallTree1* Clone();
};

