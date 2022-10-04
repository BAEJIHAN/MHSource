#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CMushRoom3 :
	public CGameObject
{
	friend class CScene;

protected:
	CMushRoom3();
	CMushRoom3(const CMushRoom3& obj);
	virtual ~CMushRoom3();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CMushRoom3* Clone();
};

