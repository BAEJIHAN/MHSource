#include "Vespoid.h"
#include "Engine.h"
#include "Player.h"
#include "Resource/ResourceManager.h"
#include "Scene/SceneManager.h"
#include "EventManager.h"
#include "../ClientManager3D.h"
#include "../Scene/MainSceneMode.h"

void CVespoid::IDLEStart()
{

	
	IdleTime = 0;
	if (IsChase)
	{
		RotateTo(FindPlayerAroundPos());
	}
	m_Mesh->GetAnimationInstance()->ChangeAnimation("vespoididle1");
	ChaseIdleTime = (float)(rand() % 10) / 5.2f + 2.0f;
	

	Vector3 Dist = pPlayer->GetWorldPos() - GetWorldPos();
	if (Dist.Length() < 60.f)
	{
		WingSound->Play();
	}
	
}

void CVespoid::IDLEStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	IdleTime += DeltaTime;

	if (IsChase)
	{
		
		if (IdleTime >= ChaseIdleTime)
		{
			FSM.ChangeState("Chase");
		}
	}
	else
	{
		if (IdleTime >= 5.f)
		{
			FSM.ChangeState("Move");
		}
	}
}

void CVespoid::IDLEEnd()
{
	IdleTime = 0;
	if (WingSound->IsPlay())
		WingSound->Stop();
	
}



void CVespoid::MOVEStart()
{
	if (MoveDist >= 10)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("vespoidlegup");
	}
	else
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("vespoidfly1");
	}
	IsMoving = true;
	DestMovePoint = FindNextMovePoint();
	RotateTo(DestMovePoint);

	Vector3 Dist = pPlayer->GetWorldPos() - GetWorldPos();
	if (Dist.Length() < 60.f)
	{
		WingSound->Play();
	}
}

void CVespoid::MOVEStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	Move(DestMovePoint);
	CurSpeed = MoveSpeed;
	if (false == IsMoving)
		FSM.ChangeState("Idle");
	
	

}

void CVespoid::MOVEEnd()
{
	IsMoving = false;
	CurSpeed = 0;
	if (WingSound->IsPlay())
	{
		WingSound->Stop();
	}
}

void CVespoid::SCREAMStart()
{
	CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::MonsterBattle);
	MoveSpeed = 20;
	IsIdle = false;
	IsChase = true;
	m_Mesh->GetAnimationInstance()->ChangeAnimation("vespoidscream");
	RotateTo(pPlayer->GetWorldPos());

	CResourceManager::GetInst()->SoundPlay("VespoidScream", this);
	CEventManager::GetInst()->CallEvent("PlayerMonsterContant");
	CClientManager3D::GetInst()->GetMainScene()->AddMonsterAggro();
}

void CVespoid::SCREAMStay()
{
}

void CVespoid::SCREAMEnd()
{
}



void CVespoid::ATTACKStart()
{
	CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::MonsterBattle);
	

	AttackTime = 0;
	
	RotateTo(pPlayer->GetWorldPos());
	attacktype = rand() % 3;
	
	if (0 == attacktype)
	{
		StartAttackTime = 2.2f;
		EndAttackTime = 2.8f;
		m_Mesh->GetAnimationInstance()->ChangeAnimation("vespoidattack2");
		CResourceManager::GetInst()->SoundPlay("VespoidAttack2", this);
		
	}
	else
	{
		StartAttackTime = 1.0f;
		EndAttackTime = 1.5f;
		m_Mesh->GetAnimationInstance()->ChangeAnimation("vespoidattack1");
		CResourceManager::GetInst()->SoundPlay("VespoidAttack1", this);
	}
	
	
}

void CVespoid::ATTACKStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	AttackTime += DeltaTime;
	if (AttackTime >= StartAttackTime)
	{
		IsAttacking = true;
	}

	if (AttackTime >= EndAttackTime)
	{
		IsAttacking = false;
	}
}

void CVespoid::ATTACKEnd()
{
	IsAttacking = false;
	if (0 == attacktype)
	{
		
		CResourceManager::GetInst()->SoundStop("VespoidAttack1");
	}
	else
	{
	
		CResourceManager::GetInst()->SoundStop("VespoidAttack2");
	}
}

void CVespoid::CHASEStart()
{
	ChaseAccTime = 0;
	IsMoving = true;

	if (MoveDist >= 10)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("vespoidlegup");
	}
	else
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("vespoidfly1");
	}
	DestMovePoint = FindPlayerAroundPos();
	RotateTo(DestMovePoint);

	Vector3 Dist = pPlayer->GetWorldPos() - GetWorldPos();
	if (Dist.Length() < 60.f)
	{
		WingSound->Play();
	}
}

void CVespoid::CHASEStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	ChaseAccTime += DeltaTime;
	Move(DestMovePoint);
	CurSpeed = MoveSpeed;
	if (false == IsMoving)
	{		
		Vector3 Dist = pPlayer->GetWorldPos() - GetWorldPos();
		if (Dist.Length() > 10.f)
		{
			DestMovePoint = FindPlayerAroundPos();
			RotateTo(DestMovePoint);
			IsMoving = true;
		}
		else
		{
			FSM.ChangeState("Attack");
		}

		
	}
	if (ChaseAccTime >= 3.f)
	{
		DestMovePoint = FindPlayerAroundPos();
		RotateTo(DestMovePoint);
		ChaseAccTime = 0;
	}
}

void CVespoid::CHASEEnd()
{
	if (WingSound->IsPlay())
	{
		WingSound->Stop();
	}
	
	ChaseAccTime = 0;
}

void CVespoid::GETHITStart()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("vespoidhit1");
	CResourceManager::GetInst()->SoundPlay("VespoidHit", this);
	IsStun = true;
}

void CVespoid::GETHITStay()
{
}

void CVespoid::GETHITEnd()
{
	IsStun = false;
}

void CVespoid::DEATHStart()
{
	IsDead = true;

	Vector3 DestVec = GetWorldPos();
	DestVec.y = 0;
	DeathYpos = m_Scene->GetNavigation3DManager()->GetY(DestVec);
	CurYPos = GetWorldPos().y;

	m_Mesh->GetAnimationInstance()->ChangeAnimation("vespoiddeath1");
	CResourceManager::GetInst()->SoundPlay("VespoidDeath", this);


	m_Mesh->DeleteChild(ColliderUpperBody);
	m_Mesh->DeleteChild(ColliderLowerBody);
	m_Mesh->DeleteChild(ColliderAttack);

	ColliderUpperBody->Destroy();
	ColliderLowerBody->Destroy();
	ColliderAttack->Destroy();

	ColliderCarving->Enable(true);
	
	CEventManager::GetInst()->CallEvent("PlayerMonsterRelease");
	CClientManager3D::GetInst()->GetMainScene()->SubMonsterAggro();
}

void CVespoid::DEATHStay()
{
	if (DeathYpos < CurYPos)
	{
		float DeltaTime = CEngine::GetInst()->GetDeltaTime();
		CurYPos -= DeltaTime * 10;
		Vector3 t = GetWorldPos();
		t.y = CurYPos;
		SetWorldPos(t);
	}

	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	DeathTime += DeltaTime;
	if (IsCarved)
	{
		FSM.ChangeState("FadeOut");
	}
	if (DeathTime > 30.f)
	{
		FSM.ChangeState("FadeOut");
	}
}

void CVespoid::DEATHEnd()
{
	DeathTime = 0;
}

void CVespoid::FADEOUTStart()
{
	m_Mesh->SetLayerName("Effect");
	IsFading = true;
}

void CVespoid::FADEOUTStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	FadeOpacity -= (float)(DeltaTime * 0.1);
	m_Mesh->SetOpacity(FadeOpacity, 0);
	m_Mesh->SetOpacity(FadeOpacity, 1);
	m_Mesh->SetOpacity(FadeOpacity, 2);
	m_Mesh->SetOpacity(FadeOpacity, 3);
	m_Mesh->SetOpacity(FadeOpacity, 4);
	m_Mesh->SetOpacity(FadeOpacity, 5);
	m_Mesh->SetOpacity(FadeOpacity, 6);
	m_Mesh->SetOpacity(FadeOpacity, 7);
	m_Mesh->SetOpacity(FadeOpacity, 8);

	


	if (FadeOpacity <= 0.1f)
	{
		Destroy();
	}
}

void CVespoid::FADEOUTEnd()
{
}


