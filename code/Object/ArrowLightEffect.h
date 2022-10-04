#pragma once

#include "GameObject/GameObject.h"
#include "Component/BillboardComponent.h"

class CArrowLightEffect :
	public CGameObject
{
    friend class CScene;

protected:
    CArrowLightEffect();
    CArrowLightEffect(const CArrowLightEffect& obj);
    virtual ~CArrowLightEffect();

private:
    CSharedPtr<CBillboardComponent>    m_Billboard;

    float       m_FadeTime;


public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual CArrowLightEffect* Clone();
};

