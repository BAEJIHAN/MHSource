
#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CGrassRock8 :
    public CGameObject
{
	friend class CScene;

protected:
	CGrassRock8();
	CGrassRock8(const CGrassRock8& obj);
	virtual ~CGrassRock8();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>			m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CGrassRock8* Clone();
};

