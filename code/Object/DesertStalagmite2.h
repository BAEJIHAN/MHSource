#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CDesertStalagmite2 :
	public CGameObject
{
	friend class CScene;

protected:
	CDesertStalagmite2();
	CDesertStalagmite2(const CDesertStalagmite2& obj);
	virtual ~CDesertStalagmite2();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CDesertStalagmite2* Clone();
};

