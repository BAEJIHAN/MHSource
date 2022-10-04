#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CDesertStone6 :
	public CGameObject
{
	friend class CScene;

protected:
	CDesertStone6();
	CDesertStone6(const CDesertStone6& obj);
	virtual ~CDesertStone6();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CDesertStone6* Clone();
};

