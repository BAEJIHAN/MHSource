#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CDesertStone1 :
	public CGameObject
{
	friend class CScene;

protected:
	CDesertStone1();
	CDesertStone1(const CDesertStone1& obj);
	virtual ~CDesertStone1();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CDesertStone1* Clone();
};

