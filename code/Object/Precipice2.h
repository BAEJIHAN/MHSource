#pragma once
#include "GameObject\GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"
class CPrecipice2 :
	public CGameObject
{
	friend class CScene;

protected:
	CPrecipice2();
	CPrecipice2(const CPrecipice2& obj);
	virtual ~CPrecipice2();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CPrecipice2* Clone();
};

