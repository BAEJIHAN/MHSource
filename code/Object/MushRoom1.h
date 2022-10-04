#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CMushRoom1 :
	public CGameObject
{
	friend class CScene;

protected:
	CMushRoom1();
	CMushRoom1(const CMushRoom1& obj);
	virtual ~CMushRoom1();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CMushRoom1* Clone();
};

