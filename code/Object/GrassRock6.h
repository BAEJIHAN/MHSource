
#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CGrassRock6 :
    public CGameObject
{
	friend class CScene;

protected:
	CGrassRock6();
	CGrassRock6(const CGrassRock6& obj);
	virtual ~CGrassRock6();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>			m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CGrassRock6* Clone();
};

