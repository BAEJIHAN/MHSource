#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CDesertSmallStone :
	public CGameObject
{
	friend class CScene;

protected:
	CDesertSmallStone();
	CDesertSmallStone(const CDesertSmallStone& obj);
	virtual ~CDesertSmallStone();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CDesertSmallStone* Clone();
};

