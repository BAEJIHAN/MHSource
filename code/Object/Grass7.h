#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CGrass7 :
    public CGameObject
{
	friend class CScene;

protected:
	CGrass7();
	CGrass7(const CGrass7& obj);
	virtual ~CGrass7();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CGrass7* Clone();
};

