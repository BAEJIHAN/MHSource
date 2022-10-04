#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CTownPassage :
    public CGameObject
{
	friend class CScene;

protected:
	CTownPassage();
	CTownPassage(const CTownPassage& obj);
	virtual ~CTownPassage();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>			m_ColliderBox1;
	CSharedPtr<CColliderBox3D>			m_ColliderBox2;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CTownPassage* Clone();
};

