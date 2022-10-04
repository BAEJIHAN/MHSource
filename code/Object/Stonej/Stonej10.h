

#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CStonej10 :
	public CGameObject
{
	friend class CScene;

protected:
	CStonej10();
	CStonej10(const CStonej10& obj);
	virtual ~CStonej10();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CStonej10* Clone();
};

