#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CGrass9 :
    public CGameObject
{
	friend class CScene;

protected:
	CGrass9();
	CGrass9(const CGrass9& obj);
	virtual ~CGrass9();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CGrass9* Clone();
};

