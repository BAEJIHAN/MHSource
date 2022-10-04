#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CSmallTree2 :
	public CGameObject
{
	friend class CScene;

protected:
	CSmallTree2();
	CSmallTree2(const CSmallTree2& obj);
	virtual ~CSmallTree2();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CSmallTree2* Clone();
};

