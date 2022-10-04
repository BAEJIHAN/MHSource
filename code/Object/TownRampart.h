#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CTownRampart :
    public CGameObject
{
	friend class CScene;

protected:
	CTownRampart();
	CTownRampart(const CTownRampart& obj);
	virtual ~CTownRampart();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>			m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CTownRampart* Clone();
};

