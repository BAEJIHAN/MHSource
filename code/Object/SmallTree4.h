#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CSmallTree4 :
    public CGameObject
{
	friend class CScene;

protected:
	CSmallTree4();
	CSmallTree4(const CSmallTree4& obj);
	virtual ~CSmallTree4();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CSmallTree4* Clone();
};

