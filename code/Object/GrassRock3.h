
#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CGrassRock3 :
    public CGameObject
{
	friend class CScene;

protected:
	CGrassRock3();
	CGrassRock3(const CGrassRock3& obj);
	virtual ~CGrassRock3();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>			m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CGrassRock3* Clone();
};

