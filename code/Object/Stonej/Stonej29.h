

#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CStonej29 :
	public CGameObject
{
	friend class CScene;

protected:
	CStonej29();
	CStonej29(const CStonej29& obj);
	virtual ~CStonej29();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CStonej29* Clone();
};

