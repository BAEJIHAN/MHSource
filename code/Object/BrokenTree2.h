#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CBrokenTree2 :
	public CGameObject
{
	friend class CScene;

protected:
	CBrokenTree2();
	CBrokenTree2(const CBrokenTree2& obj);
	virtual ~CBrokenTree2();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBrokenTree2* Clone();
};

