#include "Mernos.h"
#include "Engine.h"
#include "Player.h"
#include "Resource/ResourceManager.h"
#include "Scene/SceneManager.h"
#include "TownSign.h"


void CMernos::IDLEStart()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("mernosidle");
}

void CMernos::IDLEStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	ActTime += DeltaTime;
	FSM.ChangeState("Descend");
	//FSM.ChangeState("Arrive");
}

void CMernos::IDLEEnd()
{
	ActTime = 0;
}

void CMernos::DESCENDStart()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("mernosgliding");
	ActTime = 0;
	IsMoving = true;
	PlayerTime = 0.f;
	Vector3 Dir = pPlayer->GetWorldAxis(AXIS_Z) * -1.f;
	Vector3 PlayerPos = pPlayer->GetWorldPos();
	DestMovePoint = PlayerPos + Vector3(0.f, 13.f, 0.f) + Dir * 3.f;
	RotateTo(PlayerPos);
	Vector3 PlayerRot = pPlayer->GetWorldRot();
	PlayerRot += 180.f;

	m_Mesh->SetWorldRotation(PlayerRot);


	CResourceManager::GetInst()->SoundPlay("MernosVoice1", this);

	CTownSign* Sign = (CTownSign*)m_Scene->FindObject("TownSign1");

	if (Sign)
	{
		int Count = ((CStaticMeshComponent*)Sign->GetRootComponent())->GetMaterialSlotCount();

		for (int i = 0; i < Count; ++i)
		{
			((CStaticMeshComponent*)Sign->GetRootComponent())->SetOpacity(0.f, i);
		}
	}
	//((CStaticMeshComponent*)Sign->GetRootComponent())->SetLayerName("Effect");
}

void CMernos::DESCENDStay()
{
	float DeltaTime= CEngine::GetInst()->GetDeltaTime();
	ActTime += DeltaTime * 2.f;
	Move(DestMovePoint);
	Vector3 Dir = pPlayer->GetWorldAxis(AXIS_Z) * -1.f;

	Dir.y = 1.f;

	PlayerTime += DeltaTime;

	if (PlayerTime >= 1.f)
	{
		((CAnimationMeshComponent*)pPlayer->GetRootComponent())->GetAnimationInstance()->ChangeAnimation("BHUp1");
		pPlayer->AddWorldPos(Dir * 5.f * DeltaTime);
		pPlayer->SetIsJump(true);
	}
	if (false == IsMoving)
	{
		FSM.ChangeState("Pickup");
	}
}

void CMernos::DESCENDEnd()
{
	PlayerTime = 0.f;
	ActTime = 0;
	CResourceManager::GetInst()->SoundStop("MernosWing");
}

void CMernos::PICKUPStart()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("mernospickup");
	ActTime = 0;
	pPlayer->SetTransformState(Transform_State::None);
}

void CMernos::PICKUPStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	Vector3 Dir = pPlayer->GetWorldAxis(AXIS_Z);
	Dir *= -1.f;
	Dir.y = 1.f;
	pPlayer->AddWorldPos(Dir * DeltaTime * 10.f);
	AddWorldPos(Dir * DeltaTime * 10.f);
}

void CMernos::PICKUPEnd()
{
	ActTime = 0;
}

void CMernos::ASCENDStart()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("mernosascend");
	ActTime = 0;
	Vector3 Dir = pPlayer->GetWorldAxis(AXIS_Z) * -1.f;
	Dir.y = 1.f;
	DestMovePoint = pPlayer->GetWorldPos() + Dir * 15.f;
	IsMoving = true;
	RotateTo(DestMovePoint);
	CResourceManager::GetInst()->SoundPlay("MernosWing", this);
}

void CMernos::ASCENDStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	ActTime += DeltaTime;
	//Move(DestMovePoint);
	//pPlayer->SetWorldPos(Vector3(GetWorldPos() + Vector3(0.f, -10.f, 0.f)));
}

void CMernos::ASCENDEnd()
{
	ActTime = 0;
}

void CMernos::ARRIVEStart()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("mernosgliding");
	ActTime = 0;
	IsMoving = true;
	DestMovePoint = Vector3(20.f, 10.f, 20.f);
	RotateTo(m_MoveStartPoint);
	pPlayer->SetTransformState(Transform_State::None);
	((CAnimationMeshComponent*)pPlayer->GetRootComponent())->GetAnimationInstance()->ChangeAnimation("BHDown1");
}

void CMernos::ARRIVEStay()
{
	Move(m_MoveStartPoint);
	pPlayer->SetWorldPos(Vector3(GetWorldPos() + Vector3(0.f, -10.f, 0.f)));
	if (false == IsMoving)
	{
		FSM.ChangeState("Leave");
	}
	
}

void CMernos::ARRIVEEnd()
{
	pPlayer->SetTransformState(Transform_State::Ground);
}

void CMernos::LEAVEStart()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("mernosascend");
	ActTime = 0;
	Vector3 Dir = pPlayer->GetWorldAxis(AXIS_Z) * -1.f;

	Vector3 PlayerPos = pPlayer->GetWorldPos();

	DestMovePoint = PlayerPos + Dir * 50.f;;

	DestMovePoint.y += 100.f;

	IsMoving = true;
	RotateTo(DestMovePoint);
	CResourceManager::GetInst()->SoundPlay("MernosVoice2", this);
	CResourceManager::GetInst()->SoundPlay("MernosWing", this);

	((CAnimationMeshComponent*)pPlayer->GetRootComponent())->GetAnimationInstance()->ChangeAnimation("BHDown3");
}

void CMernos::LEAVEStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	ActTime += DeltaTime;
	Move(DestMovePoint);
	if (ActTime > 3.f)
	{
		FSM.ChangeState("Fadeout");
	}
}

void CMernos::LEAVEEnd()
{
}

void CMernos::FADEOUTStart()
{
	m_Mesh->SetLayerName("Effect");
}

void CMernos::FADEOUTStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	FadeOpacity -= (float)(DeltaTime * 0.4);
	m_Mesh->SetOpacity(FadeOpacity, 0);
	m_Mesh->SetOpacity(FadeOpacity, 1);
	m_Mesh->SetOpacity(FadeOpacity, 2);
	m_Mesh->SetOpacity(FadeOpacity, 3);
	m_Mesh->SetOpacity(FadeOpacity, 4);
	m_Mesh->SetOpacity(FadeOpacity, 5);



	if (FadeOpacity <= 0.1f)
	{
		Destroy();
	}
}

void CMernos::FADEOUTEnd()
{
}
