#pragma once

#include "Widget/WidgetWindow.h"

class CDebugWindow :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CDebugWindow();
    CDebugWindow(const CDebugWindow& Window);
    virtual ~CDebugWindow();

private:
    CSharedPtr<class CText>     m_DebugText1;
    CSharedPtr<class CText>     m_DebugNumber1;
    CSharedPtr<class CText>     m_DebugText2;
    CSharedPtr<class CText>     m_DebugText2Result;    
    CSharedPtr<class CText>     m_DebugText3;
    CSharedPtr<class CText>     m_DebugText3Result;
    CSharedPtr<class CText>     m_DebugText4;
    CSharedPtr<class CText>     m_DebugText4Result;
    CSharedPtr<class CText>     m_DebugText4Result2;
    CSharedPtr<class CText>     m_DebugText5;
    CSharedPtr<class CText>     m_DebugText5Result;
    CSharedPtr<class CText>     m_DebugText5Result2;
    CSharedPtr<class CText>     m_DebugText6;
    CSharedPtr<class CText>     m_DebugText6Result;

public:
    void SetDebugText(const TCHAR* Text);
    void SetDebugText2(const TCHAR* Text);
    void SetDebugText2Result(const TCHAR* Text);
    void SetDebugNumber(int Number);
    void SetDebugText3(const TCHAR* Text);
    void SetDebugText3Result(int Number);
    void SetDebugText4(const TCHAR* Text);
    void SetDebugText4Result(float Number);
    void SetDebugText4Result2(float Number);
    void SetDebugText5(const TCHAR* Text);
    void SetDebugText5Result(float Number);
    void SetDebugText5Result2(float Number);
    void SetDebugText6(const TCHAR* Text);
    void SetDebugText6Result(float Number);

//private:
//    std::unordered_map<CSharedPtr<class CText>, CSharedPtr<class CNumber>>    m_mapWidget;
//
//public:
//    void SetDebugText(const std::string& WidgetName, const TCHAR* Text, );
//    void SetDebugNumber(const TCHAR* Text);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
};

