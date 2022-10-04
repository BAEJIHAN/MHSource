#pragma once

#include "Scene/SceneMode.h"
#include "../UI/LoadingWindow.h"

class CLoadingSceneMode :
    public CSceneMode
{
public:
    CLoadingSceneMode();
    ~CLoadingSceneMode();

private:
    CSharedPtr<CLoadingWindow> m_LoadingWidget;
    class CLoadingThread* m_LoadingThread;

private:
    bool    m_IsComplete;

public:
    CLoadingThread* GetLoadingThread() const
    {
        return m_LoadingThread;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

