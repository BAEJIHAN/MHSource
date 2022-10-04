#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CGrass5 :
	public CGameObject
{
	friend class CScene;

protected:
	CGrass5();
	CGrass5(const CGrass5& obj);
	virtual ~CGrass5();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CGrass5* Clone();
};

