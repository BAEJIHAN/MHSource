#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CDesertMountain1 :
    public CGameObject
{
	friend class CScene;

protected:
	CDesertMountain1();
	CDesertMountain1(const CDesertMountain1& obj);
	virtual ~CDesertMountain1();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CDesertMountain1* Clone();
};

