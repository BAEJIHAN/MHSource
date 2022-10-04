#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CDesertStalactite4 :
	public CGameObject
{
	friend class CScene;

protected:
	CDesertStalactite4();
	CDesertStalactite4(const CDesertStalactite4& obj);
	virtual ~CDesertStalactite4();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CDesertStalactite4* Clone();
};

