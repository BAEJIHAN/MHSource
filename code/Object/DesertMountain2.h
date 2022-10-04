#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CDesertMountain2 :
    public CGameObject
{
	friend class CScene;

protected:
	CDesertMountain2();
	CDesertMountain2(const CDesertMountain2& obj);
	virtual ~CDesertMountain2();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CDesertMountain2* Clone();
};

