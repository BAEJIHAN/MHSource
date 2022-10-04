#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CSmallTree3 :
    public CGameObject
{
	friend class CScene;

protected:
	CSmallTree3();
	CSmallTree3(const CSmallTree3& obj);
	virtual ~CSmallTree3();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CSmallTree3* Clone();
};

