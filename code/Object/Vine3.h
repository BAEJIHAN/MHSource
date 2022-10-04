#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CVine3 :
	public CGameObject
{
	friend class CScene;

protected:
	CVine3();
	CVine3(const CVine3& obj);
	virtual ~CVine3();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CVine3* Clone();
};

