#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CTownCheckPoint :
    public CGameObject
{
	friend class CScene;

protected:
	CTownCheckPoint();
	CTownCheckPoint(const CTownCheckPoint& obj);
	virtual ~CTownCheckPoint();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>			m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CTownCheckPoint* Clone();
};

