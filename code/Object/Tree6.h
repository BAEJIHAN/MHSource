#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CTree6 :
	public CGameObject
{
	friend class CScene;

protected:
	CTree6();
	CTree6(const CTree6& obj);
	virtual ~CTree6();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CTree6* Clone();
};

