#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CBrokenTree1 :
	public CGameObject
{
	friend class CScene;

protected:
	CBrokenTree1();
	CBrokenTree1(const CBrokenTree1& obj);
	virtual ~CBrokenTree1();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBrokenTree1* Clone();
};

