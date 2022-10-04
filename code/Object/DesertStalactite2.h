#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CDesertStalactite2 :
	public CGameObject
{
	friend class CScene;

protected:
	CDesertStalactite2();
	CDesertStalactite2(const CDesertStalactite2& obj);
	virtual ~CDesertStalactite2();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CDesertStalactite2* Clone();
};

