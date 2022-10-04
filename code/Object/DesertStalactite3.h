#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CDesertStalactite3 :
	public CGameObject
{
	friend class CScene;

protected:
	CDesertStalactite3();
	CDesertStalactite3(const CDesertStalactite3& obj);
	virtual ~CDesertStalactite3();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CDesertStalactite3* Clone();
};

