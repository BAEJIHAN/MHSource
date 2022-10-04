
#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CGrassRock5 :
    public CGameObject
{
	friend class CScene;

protected:
	CGrassRock5();
	CGrassRock5(const CGrassRock5& obj);
	virtual ~CGrassRock5();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>			m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CGrassRock5* Clone();
};

