#pragma once

#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CVine5 :
    public CGameObject
{
	friend class CScene;

protected:
	CVine5();
	CVine5(const CVine5& obj);
	virtual ~CVine5();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CVine5* Clone();
};

