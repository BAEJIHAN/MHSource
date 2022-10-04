#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CTownShadeScreen :
    public CGameObject
{
	friend class CScene;

protected:
	CTownShadeScreen();
	CTownShadeScreen(const CTownShadeScreen& obj);
	virtual ~CTownShadeScreen();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>			m_ColliderBox1;
	CSharedPtr<CColliderBox3D>			m_ColliderBox2;
	CSharedPtr<CColliderBox3D>			m_ColliderBox3;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CTownShadeScreen* Clone();
};

