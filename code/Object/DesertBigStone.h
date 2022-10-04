#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CDesertBigStone :
	public CGameObject
{
	friend class CScene;

protected:
	CDesertBigStone();
	CDesertBigStone(const CDesertBigStone& obj);
	virtual ~CDesertBigStone();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CDesertBigStone* Clone();
};

