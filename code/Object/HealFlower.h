#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CHealFlower :
	public CGameObject
{
	friend class CScene;

protected:
	CHealFlower();
	CHealFlower(const CHealFlower& obj);
	virtual ~CHealFlower();

private:
	CSharedPtr<CStaticMeshComponent>    m_Mesh;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;

    bool    m_DestroyEnable;
    float   m_Opacity;

public:
    void SetDestroyEnable(bool Enable)
    {
        m_DestroyEnable = Enable;
    }

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CHealFlower* Clone();
};

