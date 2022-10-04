#include "GameObject/GameObject.h"

#pragma once
class CMonster : public CGameObject
{
    friend class CScene;

protected:
 
    bool IsMoving = false;
    bool IsDead = false;
    bool IsAttacking = false;
    bool IsCarved = false;
    bool IsFading = false;
    bool IsStun = false;
    bool IsOnFieldCol = false;
    bool IsChase = false;
    bool IsIdle = true;

    float CurYRot = 180.f;
    float MoveSpeed = 10.f;
    float CurSpeed = 0.f;
    float FadeOpacity = 1.0f;
    float CurYPos = 0.f;
    float DeathYpos = 0.f;
    float HP = 100.f;
    float ArrowDamage = 0.f;
    float AccDamage = 100.f;
    float Threshold = 100.f;
    float DeathTime =   0.f;

    float ScreamThreshold = 10.f;
    float CurScreamTime = 0, f;
     
    static int KestodonCount;
    static int BarnosCount;
    static int VespoidCount;

    Box3DInfo FieldColInfo;
    CGameObject* pFieldObj = nullptr;
    char	m_FieldObjName[32] = {};
    Vector3	m_SlidingVec = Vector3(0.f, 0.f, 0.f);
    Vector3 DestMovePoint = Vector3(0.f, 0.f, 0.f);

    Transform_State m_State = Transform_State::None;
protected:
    float CalAngle(Vector3 V)
    {
        return V.Angle(Vector3(0, 0, -1));
    }

    void Move(Vector3 Dest);
    void RotateTo(Vector3 v);  
    static bool SortPos(const CollisionBoxInfo& Begin, const CollisionBoxInfo& End);

public:
    bool GetIsDead()
    {
        return IsDead;
    }

    void SetIsDead(bool b)
    {
        IsDead = b;
    }

    bool GetIsAttacking()
    {
        return IsAttacking;
    }

    void SetIsAttacking(bool b)
    {
        IsAttacking = b;
    }

    bool GetIsCarved()  const
    {
        return IsCarved;
    }

    void SetIsCarved(bool b)
    {
        IsCarved = b;
    }

    bool GetIsFading()  const
    {
        return IsFading;
    }

    void SetIsFading(bool b)
    {
        IsFading = b;
    }

    void SetDamage(float Damage)
    {
        HP -= Damage;

        ArrowDamage = Damage;
        AccDamage += Damage;
    }

};

