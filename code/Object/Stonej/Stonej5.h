

#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CStonej5 :
	public CGameObject
{
	friend class CScene;

protected:
	CStonej5();
	CStonej5(const CStonej5& obj);
	virtual ~CStonej5();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CStonej5* Clone();
};

