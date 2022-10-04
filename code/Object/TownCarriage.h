#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CTownCarriage :
    public CGameObject
{
	friend class CScene;

protected:
	CTownCarriage();
	CTownCarriage(const CTownCarriage& obj);
	virtual ~CTownCarriage();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>			m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CTownCarriage* Clone();
};

