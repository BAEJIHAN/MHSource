#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CDesertStone5 :
	public CGameObject
{
	friend class CScene;

protected:
	CDesertStone5();
	CDesertStone5(const CDesertStone5& obj);
	virtual ~CDesertStone5();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CDesertStone5* Clone();
};

