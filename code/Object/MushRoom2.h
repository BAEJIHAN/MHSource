#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CMushRoom2 :
	public CGameObject
{
	friend class CScene;

protected:
	CMushRoom2();
	CMushRoom2(const CMushRoom2& obj);
	virtual ~CMushRoom2();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CMushRoom2* Clone();
};

