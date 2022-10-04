#pragma once

#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CSmallStone1 :
    public CGameObject
{
	friend class CScene;

protected:
	CSmallStone1();
	CSmallStone1(const CSmallStone1& obj);
	virtual ~CSmallStone1();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CSmallStone1* Clone();
};

