#include "Mernos.h"
#include "MernosAnimation.h"
#include "Input.h"
#include "Resource/Animation/AnimationSequence.h"
#include "Engine.h"
#include "Scene/SceneManager.h"
#include "Player.h"
#include "Arrow.h"
#include "DragonArrow.h"
#include "ObjectManager.h"
#include "../ClientManager3D.h"
#include "EventManager.h"

CMernos::CMernos()	:
	PlayerTime(0.f),
	m_CheckType(Check_Type::StageToLoading)
{
	SetTypeID<CMernos>();

	CurYRot = 180.f;
	pPlayer = nullptr;
	MoveSpeed = 25.f;

	DestMovePoint = Vector3(0.f, 0.f, 0.f);
	ActTime = 0.f;
	FadeOpacity = 1.0f;
	IsDead = false;
	IsAttacking = false;
}

CMernos::CMernos(const CMernos& obj)
{
	m_Mesh = (CAnimationMeshComponent*)FindComponent("Mesh");

}

CMernos::~CMernos()
{
}


void CMernos::SetCheckToPointType(const Check_Type& Type)
{
	m_CheckType = Type;
}

bool CMernos::Init()
{
	m_Mesh = CreateComponent<CAnimationMeshComponent>("Mesh");

	SetRootComponent(m_Mesh);
	m_Mesh->SetTransformState(Transform_State::None);
	m_State = Transform_State::None;
	m_Mesh->SetMesh("MernosMesh");
	m_Mesh->CreateAnimationInstance<CMernosAnimation>();

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(10.f, 10.f, 10.f);
	m_Mesh->SetRelativeRotation(Vector3(250.f, 180.f, 180.f));

	SetNotify();

	//fsm에 함수포인터를 이용해 상태 생성 
	FSM.CreateState("Idle", this, &CMernos::IDLEStay, &CMernos::IDLEStart, &CMernos::IDLEEnd);
	FSM.CreateState("Descend", this, &CMernos::DESCENDStay, &CMernos::DESCENDStart, &CMernos::DESCENDEnd);
	FSM.CreateState("Pickup", this, &CMernos::PICKUPStay, &CMernos::PICKUPStart, &CMernos::PICKUPEnd);
	FSM.CreateState("Ascend", this, &CMernos::ASCENDStay, &CMernos::ASCENDStart, &CMernos::ASCENDEnd);
	FSM.CreateState("Arrive", this, &CMernos::ARRIVEStay, &CMernos::ARRIVEStart, &CMernos::ARRIVEEnd);
	FSM.CreateState("Leave", this, &CMernos::LEAVEStay, &CMernos::LEAVEStart, &CMernos::LEAVEEnd);
	FSM.CreateState("Fadeout", this, &CMernos::FADEOUTStay, &CMernos::FADEOUTStart, &CMernos::FADEOUTEnd);


	// 메르노스가 어떤 상태인지 매니저를 통해서 넘겨받는다.
	CObjectManager::GetInst()->LoadCheckToPointFunc(this);

	this;

	return true;
}

void CMernos::Start()
{
	CGameObject::Start();

	pPlayer = (CPlayer*)CSceneManager::GetInst()->GetScene()->GetPlayerObject();

	switch (m_CheckType)
	{
	case Check_Type::None:
		FSM.ChangeState("Idle");
		break;
	case Check_Type::StageToLoading:
		FSM.ChangeState("Descend");
		break;
	case Check_Type::LoadingToStage:
	{
		FSM.ChangeState("Arrive");

		m_MoveStartPoint = pPlayer->GetWorldPos();
		m_MoveStartPoint.y += 10.f;

		CClientManager3D::GetInst()->BGMSoundStop();

		switch (CEventManager::GetInst()->GetLoadStageType())
		{
		case Stage_Type::Stage1:
			CResourceManager::GetInst()->SoundPlay("Stage1Join");
			CResourceManager::GetInst()->SoundPlay("Stage1Env");
			break;
		case Stage_Type::Stage2:
			CResourceManager::GetInst()->SoundPlay("Stage2Join");
			CResourceManager::GetInst()->SoundPlay("2StageSound");
			break;
		}
	}
		break;
	}
	//상태 변경
}

void CMernos::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	

	//Vector3 Dist = pPlayer->GetWorldPos() - GetWorldPos();

	//if (Dist.Length() < 50.f && IsIdle && !IsDead)
	//{
	//	FSM.ChangeState("Scream");
	//}


	FSM.Update();//Update에서 매 프레임마다 fsm 상태 갱신

	//if (!IsDead)
	//{
	//	YPosCorrection();
	//}

}

void CMernos::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);




}

CMernos* CMernos::Clone()
{
	return new CMernos(*this);
}



void CMernos::YPosCorrection()
{
	Vector3 DestVec = GetWorldPos();
	DestVec.y = 0;
	float y = m_Scene->GetNavigation3DManager()->GetY(DestVec);
	if (GetWorldPos().y < y)
	{
		SetWorldPos(Vector3(GetWorldPos()) + Vector3(0.f, y, 0.f));
	}
}

void CMernos::SetNotify()
{
	
	m_Mesh->GetAnimationInstance()->SetEndFunction<CMernos>("mernospickup", this, &CMernos::PickUpNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CMernos>("mernosascend", this, &CMernos::AscendNotify);
}

void CMernos::PickUpNotify()
{
	FSM.ChangeState("Ascend");
	
}

void CMernos::AscendNotify()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("mernosgliding");
}




