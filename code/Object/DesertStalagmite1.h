#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CDesertStalagmite1 :
	public CGameObject
{
	friend class CScene;

protected:
	CDesertStalagmite1();
	CDesertStalagmite1(const CDesertStalagmite1& obj);
	virtual ~CDesertStalagmite1();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CDesertStalagmite1* Clone();
};

