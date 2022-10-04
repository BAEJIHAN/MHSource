

#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CStonej21 :
	public CGameObject
{
	friend class CScene;

protected:
	CStonej21();
	CStonej21(const CStonej21& obj);
	virtual ~CStonej21();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CStonej21* Clone();
};

