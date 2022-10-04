#pragma once

#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CWreck1 :
	public CGameObject
{
	friend class CScene;

protected:
	CWreck1();
	CWreck1(const CWreck1& obj);
	virtual ~CWreck1();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CWreck1* Clone();
};

