
#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CGrassRock9 :
    public CGameObject
{
	friend class CScene;

protected:
	CGrassRock9();
	CGrassRock9(const CGrassRock9& obj);
	virtual ~CGrassRock9();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>			m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CGrassRock9* Clone();
};

