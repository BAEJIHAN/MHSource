#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CSmallTree5 :
    public CGameObject
{
	friend class CScene;

protected:
	CSmallTree5();
	CSmallTree5(const CSmallTree5& obj);
	virtual ~CSmallTree5();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CSmallTree5* Clone();
};

