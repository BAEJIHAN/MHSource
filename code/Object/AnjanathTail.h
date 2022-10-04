#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CAnjanathTail :
    public CGameObject
{
	friend class CScene;

protected:
	CAnjanathTail();
	CAnjanathTail(const CAnjanathTail& obj);
	virtual ~CAnjanathTail();

private:
	CSharedPtr<CStaticMeshComponent>	m_Mesh;
	CSharedPtr<CColliderBox3D>			m_ColliderBox;
	

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CAnjanathTail* Clone();

private:
	void OnCollisionBegin(const CollisionResult& result);
};

