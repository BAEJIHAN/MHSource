#pragma once

#include "GameObject\GameObject.h"
#include "Component/LandScape.h"

class CLandScapeObj :
    public CGameObject
{
    friend class CScene;

protected:
    CLandScapeObj();
    CLandScapeObj(const CLandScapeObj& obj);
    virtual ~CLandScapeObj();

private:
    CSharedPtr<CLandScape>      m_LandScape;
    int							m_CountX;
    int							m_CountZ;
    bool						m_First;

public:
    void SetCountX(int X)
    {
        m_CountX = X;
    }

    void SetCountZ(int Z)
    {
        m_CountZ = Z;
    }

public:
    int GetCountX()	const
    {
        return m_CountX;
    }

    int GetCountZ()	const
    {
        return m_CountZ;
    }

    CLandScape* GetLandScape() const
    {
        return m_LandScape;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CLandScapeObj* Clone();
    virtual void Load(FILE* File);
};

