#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CDesertStalactite1 :
	public CGameObject
{
	friend class CScene;

protected:
	CDesertStalactite1();
	CDesertStalactite1(const CDesertStalactite1& obj);
	virtual ~CDesertStalactite1();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CDesertStalactite1* Clone();
};

