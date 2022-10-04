
#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CBox1 :
    public CGameObject
{
	friend class CScene;

protected:
	CBox1();
	CBox1(const CBox1& obj);
	virtual ~CBox1();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>			m_ColliderBox;

private:
	float	m_XLength;
	float	m_YLength;
	float	m_ZLength;


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBox1* Clone();
};

