
#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CStonej2 :
	public CGameObject
{
	friend class CScene;

protected:
	CStonej2();
	CStonej2(const CStonej2& obj);
	virtual ~CStonej2();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CStonej2* Clone();
};

