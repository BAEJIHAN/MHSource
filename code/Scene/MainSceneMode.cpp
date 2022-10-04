
#include "MainSceneMode.h"
#include "../ClientManager3D.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Scene/Viewport.h"
#include "../Object/Player.h"
#include "../Object/FieldObj.h"
#include "../Object/EventManager.h"
#include "GameObject/LightObj.h"
#include "Resource/Material/Material.h"
#include "../UI/MainWindow.h"
#include "../UI/ExplainWindow.h"
#include "../UI/ESCWindow.h"
#include "../UI/MinimapWindow.h"
#include "../UI/BottleSlotWindow.h"
#include "../UI/HDRWindow.h"
#include "../UI/QuestWindow.h"
#include "../Object/LandScapeObj.h"
#include "../Object/Vespoid.h"
#include "../Object/Barnos.h"
#include "../Object/Jagras.h"
#include "../Object/Kestodon.h"
#include "../Object/Mernos.h"
#include "../Object/Anjanath.h"
#include "../Object/Rathalos.h"
#include "../Object/ChargingParticle.h"
#include "../Object/HealFlower.h"
#include "../Object/HealObject.h"
#include "../Object/FlameEffect.h"
#include "../Object/Tree2.h"
#include "../Object/BrokenTree1.h"
#include "../Object/SmallTree1.h"
#include "../Object/SmallTree2.h"
#include "../Object/SmallTree3.h"
#include "../UI/DamageFont.h"
#include "../Object/ChargingParticle.h"
#include "../Object/SmokeEffect.h"
#include "../Object/SparkEffect.h"
#include "../Object/BurnedDecal.h"
#include "../Object/StrongArrowParticle.h"
#include "../Object/NormalArrowParticle.h"
#include "../Object/TestObj.h"
#include "../Object/HitBreathEffect.h"
#include "../Object/GrassRock1.h"
#include "../Object/GrassRock2.h"
#include "../Object/GrassRock3.h"
#include "../Object/GrassRock4.h"
#include "../Object/GrassRock5.h"
#include "../Object/GrassRock6.h"
#include "../Object/GrassRock7.h"
#include "../Object/GrassRock8.h"
#include "../Object/GrassRock9.h"
#include "../Object/Tent1.h"
#include "../Object/Tent2.h"
#include "../Object/Box1.h"
#include "../Object/Tree8.h"
#include "../Object/Tree9.h"
#include "../Object/BrokenTree3.h"
#include "Input.h"
#include "../Object/Stonej/Stonej1.h"
#include "../Object/Stonej/Stonej2.h"
#include "../Object/Stonej/Stonej3.h"
#include "../Object/Stonej/Stonej4.h"
#include "../Object/Stonej/Stonej5.h"
#include "../Object/Stonej/Stonej6.h"
#include "../Object/Stonej/Stonej7.h"
#include "../Object/Stonej/Stonej8.h"
#include "../Object/Stonej/Stonej9.h"
#include "../Object/Stonej/Stonej10.h"
#include "../Object/Stonej/Stonej11.h"
#include "../Object/Stonej/Stonej12.h"
#include "../Object/Stonej/Stonej13.h"
#include "../Object/Stonej/Stonej14.h"
#include "../Object/Stonej/Stonej15.h"
#include "../Object/Stonej/Stonej16.h"
#include "../Object/Stonej/Stonej17.h"
#include "../Object/Stonej/Stonej18.h"
#include "../Object/Stonej/Stonej19.h"
#include "../Object/Stonej/Stonej20.h"
#include "../Object/Stonej/Stonej21.h"
#include "../Object/Stonej/Stonej22.h"
#include "../Object/Stonej/Stonej23.h"
#include "../Object/Stonej/Stonej24.h"
#include "../Object/Stonej/Stonej25.h"
#include "../Object/Stonej/Stonej26.h"
#include "../Object/Stonej/Stonej27.h"
#include "../Object/Stonej/Stonej28.h"
#include "../Object/Stonej/Stonej29.h"
#include "../Object/Stonej/Stonej30.h"
#include "../Object/Stonej/Stonej31.h"
#include "../Object/Stonej/Stonej32.h"
#include "../Object/Stonej/Stonej33.h"
#include "../Object/Stonej/Stonej34.h"
#include "../Object/Stonej/Stonej35.h"
#include "../Object/Stonej/Stonej36.h"
#include "../Object/Stonej/Stonej37.h"
#include "../Object/SlidingBox.h"
#include "../Object/TownBarrel.h"
#include "../Object/TownCarriage.h"
#include "../Object/TownCheckPoint.h"
#include "../Object/TownDragonHead.h"
#include "../Object/TownPassage.h"
#include "../Object/TownPumpkinMan.h"
#include "../Object/TownRampart.h"
#include "../Object/TownShadeScreen.h"
#include "../Object/TownSign.h"
#include "../Object/TownStructure.h"
#include "../Object/TownSummerHouse.h"
#include "../Object/TownTunnel.h"
#include "../Object/DesertMountain1.h"
#include "../Object/DesertMountain2.h"
#include "../Object/ObjectManager.h"
#include "../UI/ChargingJoomMouse.h"

CMainSceneMode::CMainSceneMode() :
	m_BGMBattleType(BGM_Type::None),
	m_MonsterAggroCount(0),
	m_BGMFadeScale(0.035f),
	m_BGMFadeScale2(0.15f)
{
	SetTypeID<CMainSceneMode>();

	CEventManager::GetInst()->ClearAllCallback();
}

CMainSceneMode::~CMainSceneMode()
{
	size_t Size = m_vecObjectInfo.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecObjectInfo[i]);
	}
}

bool CMainSceneMode::Init()
{
	if (!CSceneMode::Init())
		return false;

	m_Scene->GetViewport()->CreateWidgetWindow<CExplainWindow>("ExplainWindow");
//	m_Scene->GetViewport()->CreateWidgetWindow<CMinimapWindow>("MinimapWindow");
	m_Scene->GetViewport()->CreateWidgetWindow<CBottleSlotWindow>("BottleSlotWindow");

	m_MainWindow = m_Scene->GetViewport()->CreateWidgetWindow<CMainWindow>("MainWindow");

	LoadMesh();

	CreateMaterial();

	CreateAnimationSequence();

	CreateBillboardSequence();

	CreateParticle();

	AddWeaponSocket();

	AddMonsterSocket();

	AddLargeMonsterSocket();


	if (m_LoadingFunction)
		m_LoadingFunction(false, 0.9f);

	// 마우스의 경우 플레이어를 업데이트 쪽에서 null일경우 한 번만 플레이어를 탐색하게 되는데
	// 씬을 전환해도 마우스는 제거되지 않기때문에 씬 전환할때 플레이어를 강제로 널로 초기화해야
	// 새로운 씬에서의 새로운 플레이어를 넘겨받을 수 있다.
	CChargingJoomMouse* MouseWindow = (CChargingJoomMouse*)CEngine::GetInst()->GetMouseWidget(Mouse_State::State2);

	MouseWindow->SetPlayerNull();

	SetPlayerObject(nullptr);
	
	
	
	if (!GetPlayerObject())
	{
		CPlayer* Player = m_Scene->CreateGameObject<CPlayer>("Player");
		Player->SetWorldPos(0.f, 0.f, 0.f);
		SetPlayerObject(Player);
	}

	for (int i = 0; i < 18; ++i)
	{
		char NormalName[32] = {};
		char StrongName[32] = {};
	
		sprintf_s(NormalName, "NormalParticle%d", i);
	
		sprintf_s(StrongName, "StrongParticle%d", i);
	
		CNormalArrowParticle* NormalParticle = m_Scene->CreateGameObject<CNormalArrowParticle>(NormalName);
		NormalParticle->Disable();
		CStrongArrowParticle* StrongParticle = m_Scene->CreateGameObject<CStrongArrowParticle>(StrongName);
		StrongParticle->Disable();
	
	}

	m_MonsterAggroCount = 0;


	CJagras* jagras1 = m_Scene->CreateGameObject<CJagras>("jagras1");
	jagras1->SetWorldPos(80.f, 0.f, 80.f);

	CJagras* jagras2 = m_Scene->CreateGameObject<CJagras>("jagras2");
	jagras2->SetWorldPos(70.f, 0.f, 30.f);

	CKestodon* kestodon1 = m_Scene->CreateGameObject<CKestodon>("kestodon1");
	kestodon1->SetWorldPos(150.f, 0.f, 60.f);

	CKestodon* kestodon2 = m_Scene->CreateGameObject<CKestodon>("kestodon2");
	kestodon2->SetWorldPos(135.f, 0.f, 40.f);

	CVespoid* vespoid1 = m_Scene->CreateGameObject<CVespoid>("vespoid1");
	vespoid1->SetWorldPos(145.f, 10.f, 105.f);

	CVespoid* vespoid2 = m_Scene->CreateGameObject<CVespoid>("vespoid2");
	vespoid2->SetWorldPos(55.f, 10.f, 105.f);

	CBarnos* barnos1 = m_Scene->CreateGameObject<CBarnos>("barnos1");
	barnos1->SetWorldPos(40.f, 10.f, 120.f);

	CBarnos* barnos2 = m_Scene->CreateGameObject<CBarnos>("barnos2");
	barnos2->SetWorldPos(120.f, 10.f, 40.f);

	CGrassRock1* GrassRock= m_Scene->CreateGameObject<CGrassRock1>("GrassRock");
	GrassRock->SetWorldPos(100.f, 3.f, 100.f);


	CLandScapeObj* LandScape = m_Scene->CreateGameObject<CLandScapeObj>("LandScape");

	


	srand((unsigned int)time(0));
	return true;
}

void CMainSceneMode::Update(float DeltaTime)
{
	CSceneMode::Update(DeltaTime);

	if (m_MonsterAggroCount == 0)
	{
		float volume = 0.f;
		CResourceManager::GetInst()->GetVolume("MonsterBattleBGM", &volume);
		volume = volume - m_BGMFadeScale * DeltaTime;

		CResourceManager::GetInst()->SetVolume("MonsterBattleBGM", volume);

		if (volume <= 0.f)
		{
			volume = 0.f;
			CResourceManager::GetInst()->SoundStop("MonsterBattle");
			CResourceManager::GetInst()->SetVolume("MonsterBattleBGM", 0.f);
			return;
		}
	}

	else
	{
		float volume = 0.f;
		CResourceManager::GetInst()->GetVolume("MonsterBattleBGM", &volume);
		volume = volume + m_BGMFadeScale2 * DeltaTime;

		float OrigVol = MonsterBattleBGMVolume / 100.f;

		if (volume >= OrigVol)
			volume = OrigVol;

		CResourceManager::GetInst()->SetVolume("MonsterBattleBGM", volume);
	}
}

const CharacterInfo* CMainSceneMode::GetCharacterInfo(const std::string& CharacterName) const
{
	size_t Size = m_vecObjectInfo.size();

	for (size_t i = 0; i < Size; ++i)
	{
		auto	iter = m_vecObjectInfo[i]->CharacterInfoList.begin();
		auto	iterEnd = m_vecObjectInfo[i]->CharacterInfoList.end();

		for (; iter != iterEnd; ++iter)
		{
			if (!(*iter)->CharacterName.compare(CharacterName))
				return *iter;
		}
	}

	return nullptr;
}

void CMainSceneMode::LoadMesh()
{


	// 화살 통
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "BowBoxMesh",
		TEXT("BowHunter/Bow/HunterBowBox.msh"));

	// 화살
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "ArrowMesh",
		TEXT("BowHunter/Bow/Arrow.msh"));

	//무기
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Animation, "BowMesh",
		TEXT("BowHunter/Bow/BowBody.msh"));

	m_Scene->GetResource()->LoadSkeleton("BowSkeleton",
		TEXT("BowHunter/Bow/BowBody.bne"), MESH_PATH);

	m_Scene->GetResource()->SetMeshSkeleton("BowMesh", "BowSkeleton");

	m_Scene->GetResource()->LoadAnimationSequence(true, "BowBack",
		TEXT("BowHunter/Bow/BowBody.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BowOpen",
		TEXT("BowHunter/Bow/sqc/BowOpen.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BowClose",
		TEXT("BowHunter/Bow/sqc/BowClose.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BowShot",
		TEXT("BowHunter/Bow/sqc/BowShot.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BowChargingLoop",
		TEXT("BowHunter/Bow/sqc/BowChargingLoop.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BowChargingStart",
		TEXT("BowHunter/Bow/sqc/BowChargingStart.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BowChargingToIdle",
		TEXT("BowHunter/Bow/sqc/BowChargingToIdle.sqc"), MESH_PATH);

	// 활 vfx
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "BowVfxMesh",
		TEXT("BowHunter/Bow/md_wp11.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "BowVfxMesh2",
		TEXT("BowHunter/Bow/TestCharging.msh"));

	//플레이어	
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Animation, "PlayerMesh",
		TEXT("BowHunter/BodyVer4.msh"));

	m_Scene->GetResource()->LoadSkeleton("PlayerSkeleton",
		TEXT("BowHunter/BodyVer4.bne"), MESH_PATH);

	m_Scene->GetResource()->SetMeshSkeleton("PlayerMesh", "PlayerSkeleton");

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "PlayerFaceMesh",
		TEXT("BowHunter/BowHunterFace.msh"));

	/// <Test>
	//m_Scene->GetResource()->LoadMesh(Mesh_Type::Animation, "PlayerTestMesh",
	//	TEXT("Player_Default.msh"));

	//m_Scene->GetResource()->LoadSkeleton("PlayerTestSkeleton",
	//	TEXT("Player_Default.bne"), MESH_PATH);

	//m_Scene->GetResource()->SetMeshSkeleton("PlayerTestMesh", "PlayerTestSkeleton");

	///*m_Scene->GetResource()->LoadAnimationSequence(true, "BHTestRun",
	//	TEXT("sqc_RunLoop.sqc"), MESH_PATH);*/

	//m_Scene->GetResource()->LoadAnimationSequence(true, "BHTest1Run",
	//	TEXT("Player_Default.sqc"), MESH_PATH);

	// 시퀀스
	m_Scene->GetResource()->LoadAnimationSequence(true, "BHIdle",
		TEXT("BowHunter/co00/Hunter/HunterIdle.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHWalk",
		TEXT("BowHunter/co00/Hunter/HunterWalkLoop.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHWalkEnd",
		TEXT("BowHunter/co00/Hunter/HunterWalkEnd1.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHRunStart",
		TEXT("BowHunter/co00/Hunter/HunterRunStart.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHRun",
		TEXT("BowHunter/co00/Hunter/HunterRunLoop.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHRunQuick",
		TEXT("BowHunter/co00/Hunter/HunterRunQuickLoop.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHRunEnd",
		TEXT("BowHunter/co00/Hunter/HunterRunEnd1.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHEvade",
		TEXT("BowHunter/co00/Hunter/HunterEvade.sqc"), MESH_PATH);


	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Blank", TEXT("Object/Blank.msh"));

	//wp
	m_Scene->GetResource()->LoadAnimationSequence(true, "BHKick",
		TEXT("BowHunter/co00/Hunter/wp/HunterArcShot.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHShot",
		TEXT("BowHunter/co00/Hunter/wp/HunterArcShot.sqc"), MESH_PATH);

	// AimCharging
	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimChargingWalkFront",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimChargingWalkFront.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimChargingWalkBack",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimChargingWalkBack.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimChargingWalkLeft",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimChargingWalkLeft.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimChargingWalkRight",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimChargingWalkRight.sqc"), MESH_PATH);

	// Aim
	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimIdle",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimIdle.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimIdleToSlingerAim",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimIdleToDrawnSlingerAim.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimIdleToIdle",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimIdleToIdle.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimLoopArcShot",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimLoopArcShot.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimStartArcShot",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimStartArcShot.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimWalkFront",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimWalkFront.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimWalkBack",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimWalkBack.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimWalkLeft",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimWalkLeft.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimWalkLeftEnd",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimWalkLeftEnd.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimWalkRight",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimWalkRight.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHAimWalkRightEnd",
		TEXT("BowHunter/co00/Hunter/wp/HunterAimWalkRightEnd.sqc"), MESH_PATH);

	// Charging
	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargedShotIdle",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargedShotIdle.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingFrontStep",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingFrontStep.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingFrontStepShot",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingFrontStepShot.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingBackStep",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingBackStep.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingBackStepShot",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingBackStepShot.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingIdleToChargingWalk",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingIdleToChargingWalk.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingLeftStep",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingLeftStep.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingLeftStepShot",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingLeftStepShot.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingRightStep",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingRightStep.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingRightStepShot",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingRightStepShot.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingStartIdle",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingStartIdle.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingStartIdleFirst",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingStartIdleFirst.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingWalk",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingWalk.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingWalkEnd",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingWalkEnd.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingWalkLeftEnd",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingWalkLeftEnd.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHChargingWalkRightEnd",
		TEXT("BowHunter/co00/Hunter/wp/HunterChargingWalkRightEnd.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHFullChargingIdleLoop",
		TEXT("BowHunter/co00/Hunter/wp/HunterFullChargingIdleLoop.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHFullChargedShotIdle",
		TEXT("BowHunter/co00/Hunter/wp/HunterFullChargedShotIdle.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHPowerShot",
		TEXT("BowHunter/co00/Hunter/wp/HunterPowerShot.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHQuickShot",
		TEXT("BowHunter/co00/Hunter/wp/HunterQuickShot.sqc"), MESH_PATH);

	// Drawed
	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedBackStep",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedBackStep.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedEvade",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedEvade.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedEvadeToDrawedWalkStart",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedEvadeToDrawedWalkStart.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedEvadeToDrawedWalk",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedEvadeToDrawedWalk.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedIdle",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedIdle.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedWalk",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedWalk.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedWalkAndSheathe",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedWalkAndSheathe.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedWalkEnd",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedWalkEnd.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedWalkStart",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedWalkStart.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedWeaponToCharging",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedWeaponToCharging.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawedToChargingStart",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawedToChargingStart.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawnEvadeFront",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawnEvadeFront.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawnHitFront",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawnHitFront.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawWeapon",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawWeapon.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHWalkAndDrawWeapon",
		TEXT("BowHunter/co00/Hunter/wp/HunterWalkAndDrawWeapon.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDrawnWalkToChargingStart",
		TEXT("BowHunter/co00/Hunter/wp/HunterDrawnWalkToChargingStart.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDragonShotStart",
		TEXT("BowHunter/co00/Hunter/wp/HunterDragonPiercerStart.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDragonShot",
		TEXT("BowHunter/co00/Hunter/wp/HunterDragonPiercer.sqc"), MESH_PATH);

	// BowSheathe
	m_Scene->GetResource()->LoadAnimationSequence(true, "BHSheathe",
		TEXT("BowHunter/co00/Hunter/wp/HunterSheathe.sqc"), MESH_PATH);

	// Coating
	m_Scene->GetResource()->LoadAnimationSequence(true, "BHCoating",
		TEXT("BowHunter/co00/Hunter/wp/HunterCoating.sqc"), MESH_PATH);

	// Carving
	m_Scene->GetResource()->LoadAnimationSequence(true, "BHCarvingStart",
		TEXT("BowHunter/co00/Hunter/HunterCarvingStart.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHCarvingLoop",
		TEXT("BowHunter/co00/Hunter/HunterCarvingLoop.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHCarvingEnd",
		TEXT("BowHunter/co00/Hunter/HunterCarvingEnd.sqc"), MESH_PATH);

	// Hit
	m_Scene->GetResource()->LoadAnimationSequence(true, "BHTrippingByFront",
		TEXT("BowHunter/co00/Hunter/HunterTrippingByFront.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHTrippingToIdle",
		TEXT("BowHunter/co00/Hunter/HunterTrippingToIdle.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHRollByFrontStart",
		TEXT("BowHunter/co00/Hunter/HunterRollByFrontStart.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHRollByFrontEnd",
		TEXT("BowHunter/co00/Hunter/HunterRollByFrontEnd.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHRollOverToIdle",
		TEXT("BowHunter/co00/Hunter/HunterRollOverToIdle.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHRollOverLoop",
		TEXT("BowHunter/co00/Hunter/HunterRollOverLoop.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHRollOverByFrontEnd",
		TEXT("BowHunter/co00/Hunter/HunterRollOverByFrontEnd.sqc"), MESH_PATH);

	// PlugEars
	m_Scene->GetResource()->LoadAnimationSequence(true, "BHPlugEarsStart",
		TEXT("BowHunter/co00/Hunter/HunterPlugEarsStart.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHPlugEarsLoop",
		TEXT("BowHunter/co00/Hunter/HunterPlugEarsLoop.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHPlugEarsToIdle",
		TEXT("BowHunter/co00/Hunter/HunterPlugEarsToIdle.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDown1",
		TEXT("BowHunter/co00/Hunter/Playerdown1.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDown2",
		TEXT("BowHunter/co00/Hunter/Playerdown2.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHDown3",
		TEXT("BowHunter/co00/Hunter/Playerdown3.sqc"), MESH_PATH);

	m_Scene->GetResource()->LoadAnimationSequence(true, "BHUp1",
		TEXT("BowHunter/co00/Hunter/Playerup1.sqc"), MESH_PATH);


	if (m_LoadingFunction)
		m_LoadingFunction(false, 0.2f);

	// Field Obj

	// 환경 오브젝트 ex) 나무 돌 등등

	//m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Obj1", TEXT("Object/Obj1.msh"));

	//Town
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownBarrel", TEXT("TownObj/TownBarrel.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownCarriage", TEXT("TownObj/TownCarriage.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownCheckPoint", TEXT("TownObj/TownCheckPoint.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownDragonHead", TEXT("TownObj/TownDragonHead.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownPassage", TEXT("TownObj/TownPassage.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownPumpkinMan", TEXT("TownObj/TownPumpkinMan.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownRampart", TEXT("TownObj/TownRampart.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownShadeScreen", TEXT("TownObj/TownShadeScreen.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownSign", TEXT("TownObj/TownSign.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownStructure", TEXT("TownObj/TownStructure.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownSummerHouse", TEXT("TownObj/TownSummerHouse.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "TownTunnel", TEXT("TownObj/TownTunnel.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "SmallTree1", TEXT("Object/SmallTree1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "SmallTree2", TEXT("Object/SmallTree2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "SmallTree3", TEXT("Object/SmallTree3.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "SmallTree4", TEXT("Object/SmallTree4.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "SmallTree5", TEXT("Object/SmallTree5.msh"));
	
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tree1", TEXT("Object/Tree1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tree2", TEXT("Object/Tree2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tree3", TEXT("Object/Tree3.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tree4", TEXT("Object/Tree4.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tree5", TEXT("Object/Tree5.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tree6", TEXT("Object/Tree6.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tree7", TEXT("Object/Tree7.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tree8", TEXT("Object/Tree8.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tree9", TEXT("Object/Tree9.msh"));
	
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "BigTree1", TEXT("Object/BigTree1.msh"));
	
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "BrokenTree1", TEXT("Object/BrokenTree1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "BrokenTree2", TEXT("Object/BrokenTree2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "BrokenTree3", TEXT("Object/BrokenTree3.msh"));
	
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "MushRoom1", TEXT("Object/Mushroom1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "MushRoom2", TEXT("Object/Mushroom2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "MushRoom3", TEXT("Object/Mushroom3.msh"));
	
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Grass1", TEXT("Object/Grass1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Grass2", TEXT("Object/Grass2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Grass3", TEXT("Object/Grass3.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Grass4", TEXT("Object/Grass4.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Grass5", TEXT("Object/Grass5.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Grass6", TEXT("Object/Grass6.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Grass7", TEXT("Object/Grass7.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Grass8", TEXT("Object/Grass8.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Grass9", TEXT("Object/Grass9.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Grass10", TEXT("Object/Grass10.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "SmallGrass", TEXT("Object/SmallGrass.msh"));
	
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "SmallStone1", TEXT("Object/SmallStone1.msh"));
	
	// 바위 (이끼바위)
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "GrassRock1", TEXT("Object/GrassRock1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "GrassRock2", TEXT("Object/GrassRock2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "GrassRock3", TEXT("Object/GrassRock3.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "GrassRock4", TEXT("Object/GrassRock4.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "GrassRock5", TEXT("Object/GrassRock5.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "GrassRock6", TEXT("Object/GrassRock6.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "GrassRock7", TEXT("Object/GrassRock7.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "GrassRock8", TEXT("Object/GrassRock8.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "GrassRock9", TEXT("Object/GrassRock9.msh"));


	// 건축물 (텐트)
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tent1", TEXT("Object/Tent1.msh")); // 야영 텐트
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Tent2", TEXT("Object/Tent2.msh"));	// 마을용 텐트

	// 건축물 (상자박스)
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Box1", TEXT("Object/Box1.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Precipice1", TEXT("Object/Precipice1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Precipice2", TEXT("Object/Precipice2.msh"));
	
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Sculpture1", TEXT("Object/Sculpture1.msh"));
	
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Vine", TEXT("Object/Vine.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Vine2", TEXT("Object/Vine2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Vine3", TEXT("Object/Vine3.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Vine4", TEXT("Object/Vine4.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Vine5", TEXT("Object/Vine5.msh"));

	//m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Wreck", TEXT("Object/Wreck.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Wreck1", TEXT("Object/Wreck1.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "Far", TEXT("Object/Far.msh"));
	
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertBigStone1", TEXT("DesertObj/DesertBigStone1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertPebble1", TEXT("DesertObj/DesertPebble1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertRockWall", TEXT("DesertObj/DesertRockWall.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertSmallStone1", TEXT("DesertObj/DesertSmallStone1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStalactite1", TEXT("DesertObj/DesertStalactite1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStalactite2", TEXT("DesertObj/DesertStalactite2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStalactite3", TEXT("DesertObj/DesertStalactite3.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStalactite4", TEXT("DesertObj/DesertStalactite4.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStalagmite1", TEXT("DesertObj/DesertStalagmite1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStalagmite2", TEXT("DesertObj/DesertStalagmite2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStalagmite3", TEXT("DesertObj/DesertStalagmite3.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStone1", TEXT("DesertObj/DesertStone1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStone2", TEXT("DesertObj/DesertStone2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStone3", TEXT("DesertObj/DesertStone3.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStone4", TEXT("DesertObj/DesertStone4.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStone5", TEXT("DesertObj/DesertStone5.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertStone6", TEXT("DesertObj/DesertStone6.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertMountain1", TEXT("DesertObj/DesertMountain1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "DesertMountain2", TEXT("DesertObj/DesertMountain2.msh"));


	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej1", TEXT("stonej/stonej1.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej2", TEXT("stonej/stonej2.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej3", TEXT("stonej/stonej3.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej4", TEXT("stonej/stonej4.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej5", TEXT("stonej/stonej5.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej6", TEXT("stonej/stonej6.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej7", TEXT("stonej/stonej7.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej8", TEXT("stonej/stonej8.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej9", TEXT("stonej/stonej9.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej10", TEXT("stonej/stonej10.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej11", TEXT("stonej/stonej11.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej12", TEXT("stonej/stonej12.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej13", TEXT("stonej/stonej13.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej14", TEXT("stonej/stonej14.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej15", TEXT("stonej/stonej15.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej16", TEXT("stonej/stonej16.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej17", TEXT("stonej/stonej17.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej18", TEXT("stonej/stonej18.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej19", TEXT("stonej/stonej19.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej20", TEXT("stonej/stonej20.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej21", TEXT("stonej/stonej21.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej22", TEXT("stonej/stonej22.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej23", TEXT("stonej/stonej23.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej24", TEXT("stonej/stonej24.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej25", TEXT("stonej/stonej25.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej26", TEXT("stonej/stonej26.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej27", TEXT("stonej/stonej27.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej28", TEXT("stonej/stonej28.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej29", TEXT("stonej/stonej29.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej30", TEXT("stonej/stonej30.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej31", TEXT("stonej/stonej31.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej32", TEXT("stonej/stonej32.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej33", TEXT("stonej/stonej33.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej34", TEXT("stonej/stonej34.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej35", TEXT("stonej/stonej35.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej36", TEXT("stonej/stonej36.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "stonej37", TEXT("stonej/stonej37.msh"));


	if (m_LoadingFunction)
		m_LoadingFunction(false, 0.4f);

	// Boss
	//Anjanath (안자냐프)
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "AnjanathTailMesh", TEXT("Boss/Anjanath/EM100_Tail.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Animation, "AnjanathMesh", TEXT("Boss/Anjanath/Anjanath_NoScan.msh"));
	m_Scene->GetResource()->LoadSkeleton("AnjanathSkeleton", TEXT("Boss/Anjanath/Anjanath.bne"), MESH_PATH);
	m_Scene->GetResource()->SetMeshSkeleton("AnjanathMesh", "AnjanathSkeleton");

	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathNormalIdle", TEXT("Boss/Anjanath/em100_05_01_NormalIdle.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathNormalMoveStart", TEXT("Boss/Anjanath/EM100_NormalMoveStart.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathNormalMoveLoop", TEXT("Boss/Anjanath/EM100_NormalMoveLoop_V2.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathNormalMoveEnd", TEXT("Boss/Anjanath/EM100_NormalMoveEnd_V3.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathNormalTurnLeft", TEXT("Boss/Anjanath/EM100_NormalTurnLeft.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathNormalTurnRight", TEXT("Boss/Anjanath/EM100_NormalTurnRight.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathNormalTurnBack", TEXT("Boss/Anjanath/EM100_NormalTurnBackToLeft.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathRoaring", TEXT("Boss/Anjanath/EM100_NormalStateRoaring.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathAgressiveIdle", TEXT("Boss/Anjanath/EM100_AgressivelIdle.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathAgressiveTurnLeft", TEXT("Boss/Anjanath/EM100_AgressiveTurnLeft_NoRot.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathAgressiveTurnRight", TEXT("Boss/Anjanath/EM100_AgressiveTurnRight_NoRot.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathAgressiveTurnEnd", TEXT("Boss/Anjanath/EM100_AgressiveTurnedEnd.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathAttackDashStart", TEXT("Boss/Anjanath/EM100_Attack_DashStart_v1.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathAttackDashEnd", TEXT("Boss/Anjanath/EM100_Attack_DashEnd_v1.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathTripleBiteStart", TEXT("Boss/Anjanath/EM100_TripleBiteAttack_Start.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathTripleBite1", TEXT("Boss/Anjanath/EM100_TripleBiteAttack_P1.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathTripleBite2", TEXT("Boss/Anjanath/EM100_TripleBiteAttack_P2.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathTripleBiteV2End", TEXT("Boss/Anjanath/EM100_TripleBiteAttack_End.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathCriticalDamaged", TEXT("Boss/Anjanath/EM100_CriticalDamaged.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathCriticalDamaged2", TEXT("Boss/Anjanath/EM100_CriticalDamaged2.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathCriticalDamagedInAttack", TEXT("Boss/Anjanath/EM100_CriticalDamagedInAttack.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathBreathAttack", TEXT("Boss/Anjanath/EM100_BreathAttack.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "AnjanathBreathReady", TEXT("Boss/Anjanath/EM100_BreathReady.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(false, "AnjanathDeath", TEXT("Boss/Anjanath/EM100_Dead.sqc"), MESH_PATH);


	// Rathalos (리오레우스)
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "RathalosTailMesh", TEXT("Boss/Rathalos/RathalosTail_resize.msh"));
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Animation, "RathalosMesh", TEXT("Boss/Rathalos/Rathalos.msh"));
	m_Scene->GetResource()->LoadSkeleton("RathalosSkeleton", TEXT("Boss/Rathalos/Rathalos.bne"), MESH_PATH);
	m_Scene->GetResource()->SetMeshSkeleton("RathalosMesh", "RathalosSkeleton");

	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosNormalIdle", TEXT("Boss/Rathalos/Rathalos_Idle.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosNormalMoveStart", TEXT("Boss/Rathalos/Rathalos_WalkStart.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosNormalMoveLoop", TEXT("Boss/Rathalos/Rathalos_WalkLoop.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosRoaring", TEXT("Boss/Rathalos/Rathalos_Roaring.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosBiteStart", TEXT("Boss/Rathalos/Rathalos_BiteStart.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosBiteEnd", TEXT("Boss/Rathalos/Rathalos_BiteEnd.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosChargeStart", TEXT("Boss/Rathalos/Rathalos_ChargeStart.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosChargeEnd", TEXT("Boss/Rathalos/Rathalos_ChargeEnd.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosTailSpinAttack", TEXT("Boss/Rathalos/Rathalos_TailSpinAttack.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosAgressiveTurnLeft", TEXT("Boss/Rathalos/Rathalos_AgressiveTurnLeft.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosAgressiveTurnRight", TEXT("Boss/Rathalos/Rathalos_AgressiveTurnRight.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosFlyStart", TEXT("Boss/Rathalos/Rathalos_FlyStart.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosFlyToIdle", TEXT("Boss/Rathalos/Rathalos_FlyStartToFlyIdle.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosFlyIdle", TEXT("Boss/Rathalos/Rathalos_FlyIdle.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosLandStart", TEXT("Boss/Rathalos/Rathalos_LandingStart.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosLandEnd", TEXT("Boss/Rathalos/Rathalos_LandEnd.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosBreathStart", TEXT("Boss/Rathalos/Rathalos_BreathStart.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosBreath", TEXT("Boss/Rathalos/Rathalos_BreathAttack.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosFlyBreathStart", TEXT("Boss/Rathalos/Rathalos_FlyBreathStart.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosFlyBreath", TEXT("Boss/Rathalos/Rathalos_FlyBreath.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosDamaged", TEXT("Boss/Rathalos/Rathalos_Damaged.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "RathalosFlyDamaged", TEXT("Boss/Rathalos/Rathalos_FlyDamaged.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(false, "RathalosDead", TEXT("Boss/Rathalos/Rathalos_Dead.sqc"), MESH_PATH);


	if (m_LoadingFunction)
		m_LoadingFunction(false, 0.6f);
	// test
	/*m_Scene->GetResource()->LoadMesh(Mesh_Type::Animation, "TestMonsterMesh",
		TEXT("vespoid/vespoidmain.msh"));

	m_Scene->GetResource()->LoadSkeleton("TestSkeleton",
		TEXT("vespoid/vespoidmain.bne"), MESH_PATH);

	m_Scene->GetResource()->SetMeshSkeleton("TestMonsterMesh", "TestSkeleton");

	m_Scene->GetResource()->LoadAnimationSequence(true, "TestIdle",
		TEXT("vespoid/vespoidmain.sqc"), MESH_PATH);*/


		//몬스터

		//vespoid
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Animation, "VespoidMesh", TEXT("vespoid/vespoidmain.msh"));
	
	m_Scene->GetResource()->LoadSkeleton("VespoidSkeleton", TEXT("vespoid/vespoidmain.bne"), MESH_PATH);
	
	m_Scene->GetResource()->SetMeshSkeleton("VespoidMesh", "VespoidSkeleton");
	
	
	
	
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid1", TEXT("vespoid/vespoid1.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid2", TEXT("vespoid/vespoid2.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid3", TEXT("vespoid/vespoid3.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid4", TEXT("vespoid/vespoid4.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid5", TEXT("vespoid/vespoid5.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid6", TEXT("vespoid/vespoid6.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid7", TEXT("vespoid/vespoid7.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid8", TEXT("vespoid/vespoid8.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid9", TEXT("vespoid/vespoid9.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid10", TEXT("vespoid/vespoid10.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid11", TEXT("vespoid/vespoid11.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid12", TEXT("vespoid/vespoid12.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid13", TEXT("vespoid/vespoid13.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid14", TEXT("vespoid/vespoid14.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid15", TEXT("vespoid/vespoid15.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid16", TEXT("vespoid/vespoid16.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid17", TEXT("vespoid/vespoid17.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "vespoid18", TEXT("vespoid/vespoid18.sqc"), MESH_PATH);
	
	
	//barnos
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Animation, "BarnosMesh", TEXT("barnos/barnosmain.msh"));
	
	m_Scene->GetResource()->LoadSkeleton("BarnosSkeleton", TEXT("barnos/barnosmain.bne"), MESH_PATH);
	
	m_Scene->GetResource()->SetMeshSkeleton("BarnosMesh", "BarnosSkeleton");
	
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos1", TEXT("barnos/barnos1.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos2", TEXT("barnos/barnos2.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos3", TEXT("barnos/barnos3.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos4", TEXT("barnos/barnos4.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos5", TEXT("barnos/barnos5.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos6", TEXT("barnos/barnos6.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos7", TEXT("barnos/barnos7.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos8", TEXT("barnos/barnos8.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos9", TEXT("barnos/barnos9.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos10", TEXT("barnos/barnos10.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos11", TEXT("barnos/barnos11.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos12", TEXT("barnos/barnos12.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos13", TEXT("barnos/barnos13.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos14", TEXT("barnos/barnos14.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos15", TEXT("barnos/barnos15.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos16", TEXT("barnos/barnos16.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos17", TEXT("barnos/barnos17.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos18", TEXT("barnos/barnos18.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnos19", TEXT("barnos/barnos19.sqc"), MESH_PATH);
	
	m_Scene->GetResource()->LoadAnimationSequence(true, "barnosmain", TEXT("barnos/barnosmain.sqc"), MESH_PATH);
	
	//jagras
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Animation, "JagrasMesh", TEXT("jagras/jagrasmain.msh"));
	
	m_Scene->GetResource()->LoadSkeleton("JagrasSkeleton", TEXT("jagras/jagrasmain.bne"), MESH_PATH);
	
	m_Scene->GetResource()->SetMeshSkeleton("JagrasMesh", "JagrasSkeleton");
	
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras1", TEXT("jagras/jagras1.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras2", TEXT("jagras/jagras2.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras3", TEXT("jagras/jagras3.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras4", TEXT("jagras/jagras4.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras5", TEXT("jagras/jagras5.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras6", TEXT("jagras/jagras6.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras7", TEXT("jagras/jagras7.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras8", TEXT("jagras/jagras8.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras9", TEXT("jagras/jagras9.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras10", TEXT("jagras/jagras10.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras11", TEXT("jagras/jagras11.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras12", TEXT("jagras/jagras12.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras13", TEXT("jagras/jagras13.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras14", TEXT("jagras/jagras14.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras15", TEXT("jagras/jagras15.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras16", TEXT("jagras/jagras16.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras17", TEXT("jagras/jagras17.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras18", TEXT("jagras/jagras18.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras19", TEXT("jagras/jagras19.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras20", TEXT("jagras/jagras20.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras21", TEXT("jagras/jagras21.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras22", TEXT("jagras/jagras22.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras23", TEXT("jagras/jagras23.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras24", TEXT("jagras/jagras24.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras25", TEXT("jagras/jagras25.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras26", TEXT("jagras/jagras26.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras27", TEXT("jagras/jagras27.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras28", TEXT("jagras/jagras28.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras29", TEXT("jagras/jagras29.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras30", TEXT("jagras/jagras30.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras31", TEXT("jagras/jagras31.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras32", TEXT("jagras/jagras32.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras33", TEXT("jagras/jagras33.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras34", TEXT("jagras/jagras34.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagras35", TEXT("jagras/jagras35.sqc"), MESH_PATH);
	
	
	
	m_Scene->GetResource()->LoadAnimationSequence(true, "jagrasmain", TEXT("jagras/jagrasmain.sqc"), MESH_PATH);
	
	//kestodon
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Animation, "KestodonMesh", TEXT("kestodon/kestodonmain.msh"));
	
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon1", TEXT("kestodon/kestodon1.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon2", TEXT("kestodon/kestodon2.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon3", TEXT("kestodon/kestodon3.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon4", TEXT("kestodon/kestodon4.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon5", TEXT("kestodon/kestodon5.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon6", TEXT("kestodon/kestodon6.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon7", TEXT("kestodon/kestodon7.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon8", TEXT("kestodon/kestodon8.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon9", TEXT("kestodon/kestodon9.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon10", TEXT("kestodon/kestodon10.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon11", TEXT("kestodon/kestodon11.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon12", TEXT("kestodon/kestodon12.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon13", TEXT("kestodon/kestodon13.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon14", TEXT("kestodon/kestodon14.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon15", TEXT("kestodon/kestodon15.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon16", TEXT("kestodon/kestodon16.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon17", TEXT("kestodon/kestodon17.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon18", TEXT("kestodon/kestodon18.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon19", TEXT("kestodon/kestodon19.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon20", TEXT("kestodon/kestodon20.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon21", TEXT("kestodon/kestodon21.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon22", TEXT("kestodon/kestodon22.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon23", TEXT("kestodon/kestodon23.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon24", TEXT("kestodon/kestodon24.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon25", TEXT("kestodon/kestodon25.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon26", TEXT("kestodon/kestodon26.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon27", TEXT("kestodon/kestodon27.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon28", TEXT("kestodon/kestodon28.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodon29", TEXT("kestodon/kestodon29.sqc"), MESH_PATH);
	
	m_Scene->GetResource()->LoadSkeleton("KestodonSkeleton", TEXT("kestodon/kestodonmain.bne"), MESH_PATH);
	
	m_Scene->GetResource()->SetMeshSkeleton("KestodonMesh", "KestodonSkeleton");
	
	m_Scene->GetResource()->LoadAnimationSequence(true, "kestodonmain", TEXT("kestodon/kestodonmain.sqc"), MESH_PATH);
	
	//mernos
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Animation, "MernosMesh", TEXT("mernos/mernosmain.msh"));
	
	m_Scene->GetResource()->LoadSkeleton("MernosSkeleton", TEXT("mernos/mernosmain.bne"), MESH_PATH);
	
	m_Scene->GetResource()->SetMeshSkeleton("MernosMesh", "MernosSkeleton");
	
	m_Scene->GetResource()->LoadAnimationSequence(true, "mernos1", TEXT("mernos/mernos1.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "mernos2", TEXT("mernos/mernos2.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "mernos3", TEXT("mernos/mernos3.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "mernos4", TEXT("mernos/mernos4.sqc"), MESH_PATH);
	m_Scene->GetResource()->LoadAnimationSequence(true, "mernos5", TEXT("mernos/mernos5.sqc"), MESH_PATH);
	
	
	m_Scene->GetResource()->LoadAnimationSequence(true, "mernosmain", TEXT("mernos/mernosmain.sqc"), MESH_PATH);


	if (m_LoadingFunction)
		m_LoadingFunction(false, 0.8f);

	// 환경 오브젝트 ex) 나무 돌 등등
	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "SmallTreeMesh", TEXT("Object/SmallTree1.msh"));

	m_Scene->GetResource()->LoadMesh(Mesh_Type::Static, "testdummy", TEXT("Object/stm320_0.msh"));
}

void CMainSceneMode::CreateMaterial()
{
	m_Scene->GetResource()->CreateMaterial<CMaterial>("LandScape");

	CMaterial* Material = m_Scene->GetResource()->FindMaterial("LandScape");

	Material->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "LandScapeSplat1Dif", TEXT("LandScape/Sand/0_BML.dds"));
	Material->AddTexture(1, (int)Buffer_Shader_Type::Pixel, "LandScapeSplat1Nrm", TEXT("LandScape/Sand/0_NM.dds"));

	std::vector<TCHAR*>	vecSPLTexture, vecSPLNormal;

	vecSPLTexture.reserve(12);
	vecSPLNormal.reserve(12);

	AddLandScape(vecSPLTexture, TEXT("LandScape/Grass/1_BML.dds"));
	AddLandScape(vecSPLTexture, TEXT("LandScape/Grass/2_BML.dds"));
	AddLandScape(vecSPLTexture, TEXT("LandScape/Grass/3_BML.dds"));
	AddLandScape(vecSPLTexture, TEXT("LandScape/Grass/4_BML.dds"));

	AddLandScape(vecSPLNormal, TEXT("LandScape/Grass/1_NM.dds"));
	AddLandScape(vecSPLNormal, TEXT("LandScape/Grass/2_NM.dds"));
	AddLandScape(vecSPLNormal, TEXT("LandScape/Grass/3_NM.dds"));
	AddLandScape(vecSPLNormal, TEXT("LandScape/Grass/4_NM.dds"));

	AddLandScape(vecSPLTexture, TEXT("LandScape/Sand/1_BML.dds"));
	AddLandScape(vecSPLTexture, TEXT("LandScape/Sand/2_BML.dds"));
	AddLandScape(vecSPLTexture, TEXT("LandScape/Sand/3_BML.dds"));
	AddLandScape(vecSPLTexture, TEXT("LandScape/Sand/4_BML.dds"));
	AddLandScape(vecSPLTexture, TEXT("LandScape/Sand/5_BML.dds"));

	AddLandScape(vecSPLNormal, TEXT("LandScape/Sand/1_NM.dds"));
	AddLandScape(vecSPLNormal, TEXT("LandScape/Sand/2_NM.dds"));
	AddLandScape(vecSPLNormal, TEXT("LandScape/Sand/3_NM.dds"));
	AddLandScape(vecSPLNormal, TEXT("LandScape/Sand/4_NM.dds"));
	AddLandScape(vecSPLNormal, TEXT("LandScape/Sand/5_NM.dds"));

	AddLandScape(vecSPLTexture, TEXT("LandScape/Rock/1_BML.dds"));
	AddLandScape(vecSPLTexture, TEXT("LandScape/Rock/2_BML.dds"));
	AddLandScape(vecSPLTexture, TEXT("LandScape/Rock/3_BML.dds"));

	AddLandScape(vecSPLNormal, TEXT("LandScape/Rock/1_NM.dds"));
	AddLandScape(vecSPLNormal, TEXT("LandScape/Rock/2_NM.dds"));
	AddLandScape(vecSPLNormal, TEXT("LandScape/Rock/3_NM.dds"));

	SetLandScape(34, "SPLTexture", vecSPLTexture);
	SetLandScape(35, "SPLNormal", vecSPLNormal);

	Material->SetShader("LandScapeShader");

	Material->EnableBump();
	Material->EnableSpecularTex();
	Material->SetSpecularPower(2.5f);

	m_Scene->GetResource()->CreateMaterial<CMaterial>("ChargingParticle");
	Material = m_Scene->GetResource()->FindMaterial("ChargingParticle");

	Material->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "ChargingParticle", TEXT("Particle/ChargingParticle.png"));

	Material->SetShader("ParticleRenderShader");
	Material->SetRenderState("AlphaBlend");



	m_Scene->GetResource()->CreateMaterial<CMaterial>("RockParticle");
	Material = m_Scene->GetResource()->FindMaterial("RockParticle");

	Material->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "RockParticle", TEXT("Particle/Rocks.png"));

	Material->SetShader("ParticleRenderShader");
	Material->SetRenderState("AlphaBlend");


	m_Scene->GetResource()->CreateMaterial<CMaterial>("BurntDecal");
	Material = m_Scene->GetResource()->FindMaterial("BurntDecal");
	Material->SetShader("DecalShader");
	Material->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "BurntDecal", TEXT("Decal/BurntDecal.png"));
	Material->SetSpecularColor(Vector4().Black);

	m_Scene->GetResource()->CreateMaterial<CMaterial>("ShortBurntDecal");
	Material = m_Scene->GetResource()->FindMaterial("ShortBurntDecal");
	Material->SetShader("DecalShader");
	Material->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "ShortBurntDecal", TEXT("Decal/ShortBurntDecal.png"));
	Material->SetSpecularColor(Vector4().Black);


	m_Scene->GetResource()->CreateMaterial<CMaterial>("ArrowParticle");
	Material = m_Scene->GetResource()->FindMaterial("ArrowParticle");

	Material->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "StrongArrowParticle", TEXT("Particle/ChargingParticle.png"));

	Material->SetShader("ParticleRenderShader");
	Material->SetRenderState("AlphaBlend");

}

void CMainSceneMode::CreateAnimationSequence()
{
}

void CMainSceneMode::CreateBillboardSequence()
{
	CreateSequence("SmokeBillboard1", TEXT("Billboard/Smoke1.dds"), 8, 8, 256.f, 256.f);
	CreateSequence("SmokeBillboard2", TEXT("Billboard/Smoke2.dds"), 8, 8, 256.f, 256.f);
	CreateSequence("SmokeBillboard3", TEXT("Billboard/Smoke3.dds"), 8, 8, 256.f, 256.f);
	CreateSequence("SmokeBillboard4", TEXT("Billboard/Smoke4.png"), 8, 8, 128.f, 128.f);
	CreateSequence("SmokeBillboard5", TEXT("Billboard/Smoke5.dds"), 8, 8, 256.f, 256.f);
	CreateSequence("SmokeBillboard6", TEXT("Billboard/Smoke6.dds"), 8, 8, 256.f, 256.f);
	CreateSequence("SmokeBillboard7", TEXT("Billboard/Smoke7.dds"), 8, 8, 256.f, 256.f);
	CreateSequence("SmokeBillboard8", TEXT("Billboard/Smoke8.dds"), 8, 8, 256.f, 256.f);
	CreateSequence("SmokeBillboard9", TEXT("Billboard/Smoke9.dds"), 8, 8, 128.f, 128.f);

	CreateSequence("LiquidBillboard1", TEXT("Billboard/Liquid1.dds"), 8, 4, 256.f, 256.f);
	CreateSequence("LiquidBillboard2", TEXT("Billboard/Liquid2.dds"), 8, 4, 256.f, 256.f);
	CreateSequence("LiquidBillboard3", TEXT("Billboard/Liquid3.dds"), 8, 8, 64.f, 64.f);
	CreateSequence("LiquidBillboard4", TEXT("Billboard/Liquid4.dds"), 8, 8, 256.f, 256.f);
	CreateSequence("LiquidBillboard5", TEXT("Billboard/Liquid5.dds"), 8, 8, 256.f, 256.f);
	CreateSequence("LiquidBillboard6", TEXT("Billboard/Liquid6.dds"), 8, 8, 256.f, 256.f);
	CreateSequence("LiquidBillboard7", TEXT("Billboard/Liquid7.dds"), 8, 8, 256.f, 256.f);
	CreateSequence("LiquidBillboard8", TEXT("Billboard/Liquid8.dds"), 8, 8, 256.f, 256.f);
	CreateSequence("LiquidBillboard9", TEXT("Billboard/Liquid9.dds"), 8, 8, 256.f, 256.f);
	CreateSequence("LiquidBillboard10", TEXT("Billboard/Liquid10.dds"), 2, 2, 512.f, 512.f);

	CreateSequence("ElecBillboard1", TEXT("Billboard/Elec1.dds"), 8, 4, 128.f, 128.f);

	CreateSequence("SparkBillboard1", TEXT("Billboard/Spark1.dds"), 2, 2, 256.f, 256.f);
	CreateSequence("SparkBillboard2", TEXT("Billboard/Spark2.dds"), 4, 2, 256.f, 256.f);
	CreateSequence("SparkBillboard3", TEXT("Billboard/Spark3.dds"), 2, 2, 256.f, 256.f);
	CreateSequence("SparkBillboard4", TEXT("Billboard/Spark4.dds"), 2, 1, 128.f, 256.f);
	CreateSequence("SparkBillboard5", TEXT("Billboard/Spark5_1.png"), 4, 2, 256.f, 256.f);
	CreateSequence("SparkBillboard6", TEXT("Billboard/Spark5_2.png"), 4, 2, 256.f, 256.f);
	CreateSequence("SparkBillboard7", TEXT("Billboard/Spark6.dds"), 2, 1, 256.f, 256.f);

	CreateSequence("EtcBillboard1", TEXT("Billboard/Etc1.dds"), 8, 8, 256.f, 256.f);

	CreateSequence("FlameBillboard1", TEXT("Billboard/Flame1.dds"), 8, 8, 128.f, 128.f);

	CreateSequence("FireBillboard1", TEXT("Billboard/Fire0.png"), 8, 8, 256.f, 256.f);
	CreateSequence("FireBillboard2", TEXT("Billboard/Fire1.png"), 8, 8, 256.f, 256.f);
	CreateSequence("FireBillboard3", TEXT("Billboard/Fire2.png"), 8, 8, 256.f, 256.f);
	CreateSequence("FireBillboard4", TEXT("Billboard/Fire3.png"), 8, 8, 256.f, 256.f);
	CreateSequence("FireBillboard5", TEXT("Billboard/Fire4.png"), 16, 4, 128.f, 256.f);
	CreateSequence("FireBillboard6", TEXT("Billboard/Fire5.png"), 16, 4, 128.f, 256.f);
	CreateSequence("FireBillboard7", TEXT("Billboard/Fire6.png"), 16, 4, 128.f, 256.f);
	CreateSequence("FireBillboard8", TEXT("Billboard/Fire7.png"), 16, 4, 128.f, 256.f);
	CreateSequence("FireBillboard9", TEXT("Billboard/Fire8.png"), 8, 4, 256.f, 256.f);
	CreateSequence("FireBillboard10", TEXT("Billboard/Fire9.png"), 8, 8, 256.f, 256.f);
	CreateSequence("FireBillboard11", TEXT("Billboard/Fire10.png"), 8, 8, 256.f, 256.f);
	CreateSequence("FireBillboard12", TEXT("Billboard/Fire11.png"), 8, 2, 32.f, 64.f);
	CreateSequence("HitBreath", TEXT("Billboard/HitBreath.png"), 8, 4, 256.f, 256.f);

	CreateSequence("ExplosionBillboard1", TEXT("Billboard/Explosion.png"), 8, 6, 256.f, 248.f);
}

void CMainSceneMode::CreateParticle()
{
	m_Scene->GetResource()->CreateParticle("ChargingParticle");
	CParticle* Particle = m_Scene->GetResource()->FindParticle("ChargingParticle");

	CMaterial* Material = m_Scene->GetResource()->FindMaterial("ChargingParticle");

	Particle->SetMaterial(Material);
	Particle->SetSpawnCountMax(100);
	Particle->SetLifeTimeMin(0.6f);
	Particle->SetLifeTimeMax(0.8f);
	Particle->SetScaleMin(Vector3(0.2f, 0.2f, 1.f));
	Particle->SetScaleMax(Vector3(0.7f, 0.7f, 0.7f));
	Particle->SetSpeedMin(10.f);
	Particle->SetSpeedMax(30.f);
	Particle->SetMoveDir(Vector3(0.f, 0.f, -1.f));
	Particle->SetStartMin(Vector3(-2.5f, 2.5f, 0.f));
	Particle->SetStartMax(Vector3(2.5f, 7.5f, 0.f));
	Particle->SetColorMin(Vector4(1.f, 0.34f, 0.44f, 0.8f));
	Particle->SetColorMax(Vector4(0.98f, 0.25f, 0.25f, 0.3f));
	Particle->SetMoveAngle(Vector3(90.f, 90.f, 90.f));
	Particle->SetGravity(false);
	Particle->SetMove(true);

	m_Scene->GetResource()->CreateParticle("RockParticle");
	Particle = m_Scene->GetResource()->FindParticle("RockParticle");

	Material = m_Scene->GetResource()->FindMaterial("RockParticle");

	Particle->SetMaterial(Material);
	Particle->SetSpawnCountMax(100);
	Particle->SetLifeTimeMin(0.6f);
	Particle->SetLifeTimeMax(2.8f);
	Particle->SetScaleMin(Vector3(0.5f, 0.5f, 1.f));
	Particle->SetScaleMax(Vector3(1.f, 1.f, 1.f));
	Particle->SetSpeedMin(10.f);
	Particle->SetSpeedMax(30.f);
	Particle->SetMoveDir(Vector3(0.f, 0.f, -1.f));
	Particle->SetStartMin(Vector3(-2.5f, 2.5f, 0.f));
	Particle->SetStartMax(Vector3(2.5f, 7.5f, 0.f));
	Particle->SetColorMin(Vector4(1.f, 0.34f, 0.44f, 0.8f));
	Particle->SetColorMax(Vector4(0.98f, 0.25f, 0.25f, 0.3f));
	Particle->SetMoveAngle(Vector3(90.f, 90.f, 0.f));
	Particle->SetGravity(true);
	Particle->SetMove(true);

	m_Scene->GetResource()->CreateParticle("NormalArrowParticle");
	Particle = m_Scene->GetResource()->FindParticle("NormalArrowParticle");

	Material = m_Scene->GetResource()->FindMaterial("ArrowParticle");

	Particle->SetMaterial(Material);
	Particle->SetSpawnCountMax(15);
	Particle->SetLifeTimeMin(0.3f);
	Particle->SetLifeTimeMax(0.5f);
	Particle->SetScaleMin(Vector3(0.4f, 0.4f, 0.4f));
	Particle->SetScaleMax(Vector3(0.7f, 0.7f, 0.7f));
	//Particle->SetSpeedMin(10.f);
	//Particle->SetSpeedMax(30.f);
	Particle->SetMoveDir(Vector3(0.f, 0.f, 0.f));
	Particle->SetStartMin(Vector3(-1.5f, -1.5f, 0.f));
	Particle->SetStartMax(Vector3(1.5f, 1.5f, 0.f));
	Particle->SetColorMin(Vector4(100.f, 100.f, 100.f, 0.8f));
	Particle->SetColorMax(Vector4(100.f, 100.f, 100.f, 0.2f));
	Particle->SetMoveAngle(Vector3(0.f, 0.f, 0.f));
	//Particle->SetGravity(false);
	//Particle->SetMove(true);

	m_Scene->GetResource()->CreateParticle("StrongArrowParticle");
	Particle = m_Scene->GetResource()->FindParticle("StrongArrowParticle");

	Material = m_Scene->GetResource()->FindMaterial("ArrowParticle");

	Particle->SetMaterial(Material);
	Particle->SetSpawnCountMax(15);
	Particle->SetLifeTimeMin(0.3f);
	Particle->SetLifeTimeMax(0.5f);
	Particle->SetScaleMin(Vector3(0.4f, 0.4f, 0.4f));
	Particle->SetScaleMax(Vector3(0.7f, 0.7f, 0.7f));
	//Particle->SetSpeedMin(10.f);
	//Particle->SetSpeedMax(30.f);
	Particle->SetMoveDir(Vector3(0.f, 0.f, 0.f));
	Particle->SetStartMin(Vector3(-1.5f, -1.5f, 0.f));
	Particle->SetStartMax(Vector3(1.5f, 1.5f, 0.f));
	Particle->SetColorMin(Vector4(1.f, 0.f, 0.f, 0.8f));
	Particle->SetColorMax(Vector4(1.f, 0.f, 0.f, 0.2f));
	Particle->SetMoveAngle(Vector3(0.f, 0.f, 0.f));
	//Particle->SetGravity(false);
	//Particle->SetMove(true);

	m_Scene->GetResource()->CreateParticle("ExplosionArrowParticle");
	Particle = m_Scene->GetResource()->FindParticle("ExplosionArrowParticle");

	Material = m_Scene->GetResource()->FindMaterial("ArrowParticle");

	Particle->SetMaterial(Material);
	Particle->SetSpawnCountMax(15);
	Particle->SetLifeTimeMin(0.3f);
	Particle->SetLifeTimeMax(0.5f);
	Particle->SetScaleMin(Vector3(0.4f, 0.4f, 0.4f));
	Particle->SetScaleMax(Vector3(0.7f, 0.7f, 0.7f));
	//Particle->SetSpeedMin(10.f);
	//Particle->SetSpeedMax(30.f);
	Particle->SetMoveDir(Vector3(0.f, 0.f, 0.f));
	Particle->SetStartMin(Vector3(-1.5f, -1.5f, 0.f));
	Particle->SetStartMax(Vector3(1.5f, 1.5f, 0.f));
	Particle->SetColorMin(Vector4(1.f, 0.f, 0.f, 0.8f));
	Particle->SetColorMax(Vector4(1.f, 0.f, 0.f, 0.2f));
	Particle->SetMoveAngle(Vector3(0.f, 0.f, 0.f));
	//Particle->SetGravity(false);
	//Particle->SetMove(true);
}

void CMainSceneMode::AddWeaponSocket()
{
	m_Scene->GetResource()->AddSocket("PlayerSkeleton", "bone100",
		"BowHead");
	m_Scene->GetResource()->AddSocket("PlayerSkeleton", "bone11",
		"BowLeftHand");
	m_Scene->GetResource()->AddSocket("PlayerSkeleton", "bone46",
		"BowRightHand");

	m_Scene->GetResource()->AddSocket("PlayerSkeleton", "bone75",
		"BackBow");


	m_Scene->GetResource()->AddSocket("PlayerSkeleton", "boneWst10",
		"BowBox");

	m_Scene->GetResource()->AddSocket("PlayerSkeleton", "bone6",
		"PlayerFace");

	m_Scene->GetResource()->AddSocket("PlayerSkeleton", "bone0",
		"HitBreath");

	/*m_Scene->GetResource()->AddSocket("BowSkeleton", "BoneFunction.000",
		"BowVfx");*/

	m_Scene->GetResource()->AddSocket("BowSkeleton", "BoneFunction.100",
		"BowVfx");

	m_Scene->GetResource()->AddSocket("NPCBodySkeleton", "bone5", "NPCHeadSocket");
}

void CMainSceneMode::AddMonsterSocket()
{
	//바르노스
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.004", "Head");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.102", "Body1");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.100", "Body2");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.002", "Body3");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.141", "Body4");

	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.027", "RightWing1");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.234", "RightWing2");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.180", "RightWing3");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.181", "RightWing4");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.173", "RightWing5");

	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.023", "LeftWing1");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.214", "LeftWing2");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.159", "LeftWing3");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.161", "LeftWing4");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.153", "LeftWing5");




	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.090", "RightFoot");
	m_Scene->GetResource()->AddSocket("BarnosSkeleton", "BoneFunction.080", "LeftFoot");

	//랑고스타
	m_Scene->GetResource()->AddSocket("VespoidSkeleton", "BoneFunction.000", "UpperBody");
	m_Scene->GetResource()->AddSocket("VespoidSkeleton", "BoneFunction.141", "LowerBody");
	m_Scene->GetResource()->AddSocket("VespoidSkeleton", "BoneFunction.142", "Attack");

	//자그라스
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.121", "Head");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.101", "Body1");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.100", "Body2");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.002", "Body3");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.000", "Body4");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.140", "Body5");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.141", "Tail1");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.142", "Tail2");

	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.040", "LeftFoot");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.060", "RightFoot");

	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.012", "RightFrontLeg");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.008", "LeftFrontLeg");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.019", "RightBackLeg");
	m_Scene->GetResource()->AddSocket("JagrasSkeleton", "BoneFunction.015", "LeftBackLeg");

	//케스토톤
	m_Scene->GetResource()->AddSocket("KestodonSkeleton", "BoneFunction.003", "Head");
	m_Scene->GetResource()->AddSocket("KestodonSkeleton", "BoneFunction.002", "UpperBody");
	m_Scene->GetResource()->AddSocket("KestodonSkeleton", "BoneFunction.140", "LowerBody");
	m_Scene->GetResource()->AddSocket("KestodonSkeleton", "BoneFunction.141", "LowerLowerBody");
	m_Scene->GetResource()->AddSocket("KestodonSkeleton", "BoneFunction.142", "Tail");
	m_Scene->GetResource()->AddSocket("KestodonSkeleton", "BoneFunction.015", "LeftLeg");
	m_Scene->GetResource()->AddSocket("KestodonSkeleton", "BoneFunction.019", "RightLeg");
}

void CMainSceneMode::AddLargeMonsterSocket()
{
	// Rathalos
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone114", "RightLeg");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone98", "LeftLeg");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone115", "RightFoot");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone99", "LeftFoot");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone16", "Head1");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone5", "Head2");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone2", "Body");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone21", "LeftWing");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone60", "RightWing");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone131", "TailWithBody");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone132", "TailConnection");
	m_Scene->GetResource()->AddSocket("RathalosSkeleton", "bone133", "Tail");

	// Anjanath
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.031", "Head1");	// Head
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.003", "Head2");	// Neck
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.001", "Body");
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.014", "LeftBackLeg");
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.018", "RightBackLeg");
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.012", "LeftFrontLeg");
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.008", "RightFrontLeg");
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.080", "LeftBackFoot");
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.020", "RightBackFoot");
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.141", "TailWithBody");
	m_Scene->GetResource()->AddSocket("AnjanathSkeleton", "BoneFunction.143", "Tail");
}


void CMainSceneMode::CreateSequence(const std::string& Name, const TCHAR* FileName, int CountX, int CountY, float SizeX, float SizeY)
{
	m_Scene->GetResource()->CreateAnimationSequence2D(Name, Name, FileName);

	for (int i = 0; i < CountY; ++i)
	{
		for (int j = 0; j < CountX; ++j)
		{
			m_Scene->GetResource()->AddAnimationSequence2DFrame(Name, Vector2(j * SizeX, i * SizeY), Vector2(SizeX, SizeY));
		}
	}
}

void CMainSceneMode::AddLandScape(std::vector<TCHAR*>& vec, const TCHAR* Path)
{
	TCHAR* FileName = DBG_NEW TCHAR[32];
	memset(FileName, 0, sizeof(TCHAR) * 32);
	lstrcpy(FileName, Path);
	vec.push_back(FileName);
}

void CMainSceneMode::SetLandScape(int Register, const std::string& Name, std::vector<TCHAR*>& vecFileName, const std::string& PathName)
{
	CMaterial* Material = m_Scene->GetResource()->FindMaterial("LandScape");

	Material->AddTextureArray(Register, (int)Buffer_Shader_Type::Pixel, Name, vecFileName, PathName);

	SAFE_DELETE_ARRAY_VECLIST(vecFileName);
}

void CMainSceneMode::SetCheckPointFunc()
{
	CPlayer* Player = (CPlayer*)m_Scene->GetSceneMode()->GetPlayerObject();

	Vector3 PlayerPos = Player->GetWorldPos();
	PlayerPos.y += 20.f;
	Vector3 Dir = Player->GetWorldAxis(AXIS_Z);

	CMernos* Mernos = m_Scene->CreateGameObject<CMernos>("Mernos");
	Mernos->SetWorldPos(PlayerPos + Dir * 10.f);
}

void CMainSceneMode::PlayBattleBGM(BGM_Type BGMType)
{
	switch (BGMType)
	{
	case BGM_Type::None:
		CResourceManager::GetInst()->SoundStop("MonsterBattle");
		break;
	case BGM_Type::MonsterBattle:
		if (!CResourceManager::GetInst()->IsSoundPlay("MonsterBattle"))
		{
			CResourceManager::GetInst()->SoundPlay("MonsterBattle");
			CResourceManager::GetInst()->SetVolume("MonsterBattleBGM", 0.f);
		}
		break;
	case BGM_Type::BossBattle:
		CResourceManager::GetInst()->SoundStop("MonsterBattle");
		if (!CResourceManager::GetInst()->IsSoundPlay("BossBattle"))
			CResourceManager::GetInst()->SoundPlay("BossBattle");
		break;
	case BGM_Type::QuestComplete:
		CResourceManager::GetInst()->SoundStop("BossBattle");
		if (!CResourceManager::GetInst()->IsSoundPlay("QuestComplete"))
			CResourceManager::GetInst()->SoundPlay("QuestComplete");
		break;
	case BGM_Type::FinalBossBattle:
		CResourceManager::GetInst()->SoundStop("MonsterBattle");
		if (!CResourceManager::GetInst()->IsSoundPlay("FinalBossBattle"))
			CResourceManager::GetInst()->SoundPlay("FinalBossBattle");
		break;
	case BGM_Type::FinalQuestComplete:
		CResourceManager::GetInst()->SoundStop("FinalBossBattle");
		if (!CResourceManager::GetInst()->IsSoundPlay("FinalQuestComplete"))
			CResourceManager::GetInst()->SoundPlay("FinalQuestComplete");
		break;
	}

	m_BGMBattleType = BGMType;
}
