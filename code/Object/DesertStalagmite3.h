#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CDesertStalagmite3 :
	public CGameObject
{
	friend class CScene;

protected:
	CDesertStalagmite3();
	CDesertStalagmite3(const CDesertStalagmite3& obj);
	virtual ~CDesertStalagmite3();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CDesertStalagmite3* Clone();
};

