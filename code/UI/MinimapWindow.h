
#pragma once

#include "Widget/WidgetWindow.h"

class CMinimapWindow :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CMinimapWindow();
    virtual ~CMinimapWindow();

private:
    CSharedPtr<class CMinimap>        m_Minimap;
    CSharedPtr<class CImage>          m_MinimapFrame;
    CSharedPtr<class CImage>          m_PlayerIcon;
    CSharedPtr<class CImage>          m_PlayerViewImage;
    CSharedPtr<class CImage>          m_NorthIcon;
    CSharedPtr<class CImage>          m_ContantRing;

private:
    std::vector<CSharedPtr<class CGameObject>> m_vecMonsterObj;
    std::vector<CSharedPtr<class CImage>> m_vecMonsterUI;
    class CGameObject* m_PlayerObj;
    class CArm* m_CameraArm;

private:
    unsigned short         m_Count;  // Monster Contant Count 

public:
    void SetMapSize(Vector2 Size);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();

private:
    void CreateWidgets(Vector2 WindowSize);

private:
    void CalcMonsters();

private:
    void PlayerContantSpotted();
    void PlayerContantRelease();
};

