#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CDesertStone4 :
	public CGameObject
{
	friend class CScene;

protected:
	CDesertStone4();
	CDesertStone4(const CDesertStone4& obj);
	virtual ~CDesertStone4();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CDesertStone4* Clone();
};

