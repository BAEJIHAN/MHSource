#include "ClientManager3D.h"
#include "Engine.h"
#include "resource.h"
#include "Scene/SceneManager.h"
#include "Scene/StartSceneMode.h"
#include "Scene/LoadingSceneMode.h"
#include "Scene/MainSceneMode.h"
#include "Scene/TownSceneMode.h"
#include "Scene/LoadingSceneMode.h"
#include "Input.h"
#include "Resource/ResourceManager.h"
#include "UI/NormalMouse.h"
#include "UI/ClickMouse.h"
#include "UI/JoomMouse.h"
#include "UI/ChargingJoomMouse.h"
#include "Object/Player.h"
#include "Object/LandScapeObj.h"
#include "Object/Barnos.h"
#include "Object/Jagras.h"
#include "Object/Kestodon.h"
#include "Object/Vespoid.h"
#include "Object/Anjanath.h"
#include "Object/Rathalos.h"
#include "Object/FieldObj.h"
#include "Object/SlidingBox.h"
#include "Object/HealFlower.h"
#include "Object/SmallTree1.h"
#include "Object/SmallTree2.h"
#include "Object/SmallTree3.h"
#include "Object/SmallTree4.h"
#include "Object/SmallTree5.h"
#include "Object/Tree1.h"
#include "Object/Tree2.h"
#include "Object/Tree3.h"
#include "Object/Tree4.h"
#include "Object/Tree5.h"
#include "Object/Tree6.h"
#include "Object/Tree7.h"
#include "Object/Tree8.h"
#include "Object/Tree9.h"
#include "Object/BigTree.h"
#include "Object/BrokenTree1.h"
#include "Object/BrokenTree2.h"
#include "Object/BrokenTree3.h"
#include "Object/MushRoom1.h"
#include "Object/MushRoom2.h"
#include "Object/MushRoom3.h"
#include "Object/Grass1.h"
#include "Object/Grass2.h"
#include "Object/Grass3.h"
#include "Object/Grass4.h"
#include "Object/Grass5.h"
#include "Object/Grass6.h"
#include "Object/Grass7.h"
#include "Object/Grass8.h"
#include "Object/Grass9.h"
#include "Object/SmallGrass.h"
#include "Object/Vine.h"
#include "Object/Vine2.h"
#include "Object/Vine3.h"
#include "Object/Vine4.h"
#include "Object/Vine5.h"
#include "Object/Precipice.h"
#include "Object/Precipice2.h"
#include "Object/Sculpture.h"
#include "Object/SmallStone1.h"
#include "Object/GrassRock1.h"
#include "Object/GrassRock2.h"
#include "Object/GrassRock3.h"
#include "Object/GrassRock4.h"
#include "Object/GrassRock5.h"
#include "Object/GrassRock6.h"
#include "Object/GrassRock7.h"
#include "Object/GrassRock8.h"
#include "Object/GrassRock9.h"
#include "Object/Wreck1.h"
#include "Object/Tent1.h"
#include "Object/Tent2.h"
#include "Object/Box1.h"
#include "Object/Far.h"
#include "Object/DesertPebble.h"
#include "Object/DesertSmallStone.h"
#include "Object/DesertStone1.h"
#include "Object/DesertStone2.h"
#include "Object/DesertStone3.h"
#include "Object/DesertStone4.h"
#include "Object/DesertStone5.h"
#include "Object/DesertStone6.h"
#include "Object/DesertBigStone.h"
#include "Object/DesertRockWall.h"
#include "Object/DesertStalactite1.h"
#include "Object/DesertStalactite2.h"
#include "Object/DesertStalactite3.h"
#include "Object/DesertStalactite4.h"
#include "Object/DesertStalagmite1.h"
#include "Object/DesertStalagmite2.h"
#include "Object/DesertStalagmite3.h"
#include "Object/Stonej/Stonej1.h"
#include "Object/Stonej/Stonej2.h"
#include "Object/Stonej/Stonej3.h"
#include "Object/Stonej/Stonej4.h"
#include "Object/Stonej/Stonej5.h"
#include "Object/Stonej/Stonej6.h"
#include "Object/Stonej/Stonej7.h"
#include "Object/Stonej/Stonej8.h"
#include "Object/Stonej/Stonej9.h"
#include "Object/Stonej/Stonej10.h"
#include "Object/Stonej/Stonej11.h"
#include "Object/Stonej/Stonej12.h"
#include "Object/Stonej/Stonej13.h"
#include "Object/Stonej/Stonej14.h"
#include "Object/Stonej/Stonej15.h"
#include "Object/Stonej/Stonej16.h"
#include "Object/Stonej/Stonej17.h"
#include "Object/Stonej/Stonej18.h"
#include "Object/Stonej/Stonej19.h"
#include "Object/Stonej/Stonej20.h"
#include "Object/Stonej/Stonej21.h"
#include "Object/Stonej/Stonej22.h"
#include "Object/Stonej/Stonej23.h"
#include "Object/Stonej/Stonej24.h"
#include "Object/Stonej/Stonej25.h"
#include "Object/Stonej/Stonej26.h"
#include "Object/Stonej/Stonej27.h"
#include "Object/Stonej/Stonej28.h"
#include "Object/Stonej/Stonej29.h"
#include "Object/Stonej/Stonej30.h"
#include "Object/Stonej/Stonej31.h"
#include "Object/Stonej/Stonej32.h"
#include "Object/Stonej/Stonej33.h"
#include "Object/Stonej/Stonej34.h"
#include "Object/Stonej/Stonej35.h"
#include "Object/Stonej/Stonej36.h"
#include "Object/Stonej/Stonej37.h"
#include "Object/TownBarrel.h"
#include "Object/TownCarriage.h"
#include "Object/TownCheckPoint.h"
#include "Object/TownDragonHead.h"
#include "Object/TownPassage.h"
#include "Object/TownPumpkinMan.h"
#include "Object/TownRampart.h"
#include "Object/TownShadeScreen.h"
#include "Object/TownSign.h"
#include "Object/TownStructure.h"
#include "Object/TownSummerHouse.h"
#include "Object/TownTunnel.h"
#include "Object/DesertMountain1.h"
#include "Object/DesertMountain2.h"
#include "Component/Arm.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/SpriteComponent.h"
#include "Component/LandScape.h"
#include "Component/CameraComponent.h"
#include "Component/ColliderSphere.h"
#include "Component/ColliderBox3D.h"
#include "Object/EventManager.h"
#include "Object/ObjectManager.h"

DEFINITION_SINGLE(CClientManager3D)

CClientManager3D::CClientManager3D()
{
}

CClientManager3D::~CClientManager3D()
{
	CEventManager::DestroyInst();

	CEngine::DestroyInst();
	CObjectManager::DestroyInst();
}

bool CClientManager3D::Init(HINSTANCE hInst)
{
	TCHAR	Title[64] = {};

#ifdef _DEBUG
	lstrcpy(Title, TEXT("[디버그] 몬스터 헌터 월드 FPS : "));
#else
	lstrcpy(Title, TEXT("몬스터 헌터 월드 FPS : "));
#endif // _DEBUG

	if (!CEngine::GetInst()->Init(hInst, Title, 1280, 720, IDI_ICON1))
	{
		CEngine::DestroyInst();
		return false;
	}

	CSceneManager::GetInst()->SetCreateSceneModeFunction<CClientManager3D>(this, &CClientManager3D::CreateSceneMode);
	CSceneManager::GetInst()->SetCreateObjectFunction<CClientManager3D>(this, &CClientManager3D::CreateObject);
	CSceneManager::GetInst()->SetCreateComponentFunction<CClientManager3D>(this, &CClientManager3D::CreateComponent);

	CEventManager::GetInst()->Init();
	CObjectManager::GetInst()->Init();

	CInput::GetInst()->CreateKey("RunFront", 'W');
	CInput::GetInst()->CreateKey("RunBack", 'S');
	CInput::GetInst()->CreateKey("RunLeft", 'A');
	CInput::GetInst()->CreateKey("RunRight", 'D');
	CInput::GetInst()->CreateKey("RunQuickFront", 'W');
	CInput::GetInst()->CreateKey("RunQuickBack", 'S');
	CInput::GetInst()->CreateKey("RunQuickLeft", 'A');
	CInput::GetInst()->CreateKey("RunQuickRight", 'D');
	CInput::GetInst()->CreateKey("DrawWeapon", 'C');
	CInput::GetInst()->CreateKey("Evade", VK_SPACE);
	CInput::GetInst()->CreateKey("EvadeShift", VK_SPACE);
	CInput::GetInst()->CreateKey("EvadeShot", VK_SPACE);
	CInput::GetInst()->CreateKey("Attack", VK_LBUTTON);
	CInput::GetInst()->CreateKey("AttackJoom", VK_RBUTTON);
	CInput::GetInst()->CreateKey("ESC", VK_ESCAPE);
	CInput::GetInst()->CreateKey("Skill1", '1');
	CInput::GetInst()->CreateKey("CameraDeploy", VK_F6);
	CInput::GetInst()->CreateKey("CameraWalk", VK_F7);

	CInput::GetInst()->CreateKey("FlightCamera", VK_F11);

	CInput::GetInst()->CreateKey("QuickShot", 'E');

	CInput::GetInst()->CreateKey("Potion", 'R');

	CInput::GetInst()->CreateKey("Coating", 'Q');

	CInput::GetInst()->CreateKey("Interaction", 'F');

	CInput::GetInst()->CreateKey("Up", VK_NUMPAD8);
	CInput::GetInst()->CreateKey("Down", VK_NUMPAD2);


	CInput::GetInst()->CreateKey("Interaction", 'F');

	CResourceManager::GetInst()->CreateSoundChannelGroup("BGM");
	CResourceManager::GetInst()->CreateSoundChannelGroup("MonsterBattleBGM");
	CResourceManager::GetInst()->CreateSoundChannelGroup("JoinBGM");
	CResourceManager::GetInst()->CreateSoundChannelGroup("Environment");
	CResourceManager::GetInst()->CreateSoundChannelGroup("UI");
	CResourceManager::GetInst()->CreateSoundChannelGroup("Effect");
	CResourceManager::GetInst()->CreateSoundChannelGroup("Step");
	CResourceManager::GetInst()->CreateSoundChannelGroup("Kestodon");
	CResourceManager::GetInst()->CreateSoundChannelGroup("Jagras");
	CResourceManager::GetInst()->CreateSoundChannelGroup("Vespoid");
	CResourceManager::GetInst()->CreateSoundChannelGroup("Barnos");
	CResourceManager::GetInst()->CreateSoundChannelGroup("Mernos");
	CResourceManager::GetInst()->CreateSoundChannelGroup("Anjanath");
	CResourceManager::GetInst()->CreateSoundChannelGroup("Rathalos");

	//CResourceManager::GetInst()->SetVolume(20);
	CResourceManager::GetInst()->SetVolume("BGM", 25);
	CResourceManager::GetInst()->SetVolume("MonsterBattleBGM", MonsterBattleBGMVolume);
	CResourceManager::GetInst()->SetVolume("JoinBGM", 15);
	CResourceManager::GetInst()->SetVolume("Environment", 60);
	CResourceManager::GetInst()->SetVolume("UI", 25);
	CResourceManager::GetInst()->SetVolume("Effect", 25);
	CResourceManager::GetInst()->SetVolume("Effect2", 60);
	CResourceManager::GetInst()->SetVolume("Step", 35);
	CResourceManager::GetInst()->SetVolume("Kestodon", 30);
	CResourceManager::GetInst()->SetVolume("Jagras", 30);
	CResourceManager::GetInst()->SetVolume("Vespoid", 30);
	CResourceManager::GetInst()->SetVolume("Barnos", 30);
	CResourceManager::GetInst()->SetVolume("Mernos", 30);

	AddSound();

	// 마우스 위젯 설정
	CNormalMouse* MouseNormal = CEngine::GetInst()->CreateMouse<CNormalMouse>(Mouse_State::Normal, "NormalMouse");
	CClickMouse* MouseClick = CEngine::GetInst()->CreateMouse<CClickMouse>(Mouse_State::Click, "ClickMouse");
	CJoomMouse* MouseJoom = CEngine::GetInst()->CreateMouse<CJoomMouse>(Mouse_State::State2, "MouseJoom");
	CChargingJoomMouse* MouseChargingJoom = CEngine::GetInst()->CreateMouse<CChargingJoomMouse>(Mouse_State::State3, "MouseChargingJoom");

	return true;
}

void CClientManager3D::CreateDefaultSceneMode()
{
	CSceneManager::GetInst()->CreateSceneMode<CMainSceneMode>();
	//CSceneManager::GetInst()->CreateSceneMode<CTownSceneMode>();
}

int CClientManager3D::Run()
{
	return CEngine::GetInst()->Run();
}

void CClientManager3D::CreateSceneMode(CScene* Scene, size_t Type)
{
}

CGameObject* CClientManager3D::CreateObject(CScene* Scene, size_t Type)
{
	CGameObject* Obj = nullptr;

	Obj = CreateCharacter(Scene, Type);

	if (Obj)
		return Obj;

	Obj = CreateObj1(Scene, Type);

	if (Obj)
		return Obj;

	Obj = CreateObj2(Scene, Type);

	return Obj;
}

CComponent* CClientManager3D::CreateComponent(CGameObject* Obj, size_t Type)
{
	if (Type == typeid(CSceneComponent).hash_code())
	{
		CSceneComponent* Root = Obj->GetRootComponent();

		CComponent* Component = Obj->LoadComponent<CSceneComponent>();

		if (Root)
			Root->AddChild((CSceneComponent*)Component);

		return Component;
	}

	else if (Type == typeid(CSpriteComponent).hash_code())
	{
		CSceneComponent* Root = Obj->GetRootComponent();

		CComponent* Component = Obj->LoadComponent<CSpriteComponent>();

		if (Root)
			Root->AddChild((CSceneComponent*)Component);

		return Component;
	}

	else if (Type == typeid(CStaticMeshComponent).hash_code())
	{
		CSceneComponent* Root = Obj->GetRootComponent();

		CComponent* Component = Obj->LoadComponent<CStaticMeshComponent>();

		if (Root)
			Root->AddChild((CSceneComponent*)Component);

		return Component;
	}

	else if (Type == typeid(CArm).hash_code())
	{
		CSceneComponent* Root = Obj->GetRootComponent();

		CArm* Component = Obj->LoadComponent<CArm>();

		if (Root)
			Root->AddChild((CSceneComponent*)Component);

		return Component;
	}

	else if (Type == typeid(CAnimationMeshComponent).hash_code())
	{
		CSceneComponent* Root = Obj->GetRootComponent();

		CAnimationMeshComponent* Component = Obj->LoadComponent<CAnimationMeshComponent>();

		if (Root)
			Root->AddChild((CSceneComponent*)Component);

		return Component;
	}

	else if (Type == typeid(CLandScape).hash_code())
	{
		CSceneComponent* Root = Obj->GetRootComponent();

		CLandScape* Component = Obj->LoadComponent<CLandScape>();

		if (Root)
			Root->AddChild((CSceneComponent*)Component);

		return Component;
	}

	else if (Type == typeid(CCameraComponent).hash_code())
	{
		CSceneComponent* Root = Obj->GetRootComponent();

		CCameraComponent* Component = Obj->LoadComponent<CCameraComponent>();

		if (Root)
			Root->AddChild((CSceneComponent*)Component);

		return Component;
	}

	else if (Type == typeid(CColliderSphere).hash_code())
	{
		CSceneComponent* Root = Obj->GetRootComponent();

		CColliderSphere* Component = Obj->LoadComponent<CColliderSphere>();

		if (Root)
			Root->AddChild((CSceneComponent*)Component);

		return Component;
	}

	else if (Type == typeid(CColliderBox3D).hash_code())
	{
		CSceneComponent* Root = Obj->GetRootComponent();

		CColliderBox3D* Component = Obj->LoadComponent<CColliderBox3D>();

		if (Root)
			Root->AddChild((CSceneComponent*)Component);

		return Component;
	}

	return nullptr;
}

CGameObject* CClientManager3D::CreateCharacter(CScene* Scene, size_t Type)
{
	if (Type == typeid(CGameObject).hash_code())
	{
		CGameObject* Obj = Scene->LoadGameObject<CGameObject>();

		return Obj;
	}

	else if (Type == typeid(CPlayer).hash_code())
	{
		CPlayer* Obj = Scene->LoadGameObject<CPlayer>();

		return Obj;
	}

	else if (Type == typeid(CLandScapeObj).hash_code())
	{
		CLandScapeObj* Obj = Scene->LoadGameObject<CLandScapeObj>();

		return Obj;
	}

	else if (Type == typeid(CBarnos).hash_code())
	{
		CBarnos* Obj = Scene->LoadGameObject<CBarnos>();

		return Obj;
	}

	else if (Type == typeid(CJagras).hash_code())
	{
		CJagras* Obj = Scene->LoadGameObject<CJagras>();

		return Obj;
	}

	else if (Type == typeid(CKestodon).hash_code())
	{
		CKestodon* Obj = Scene->LoadGameObject<CKestodon>();

		return Obj;
	}

	else if (Type == typeid(CVespoid).hash_code())
	{
		CVespoid* Obj = Scene->LoadGameObject<CVespoid>();

		return Obj;
	}

	else if (Type == typeid(CAnjanath).hash_code())
	{
		CAnjanath* Obj = Scene->LoadGameObject<CAnjanath>();

		return Obj;
	}

	else if (Type == typeid(CRathalos).hash_code())
	{
		CRathalos* Obj = Scene->LoadGameObject<CRathalos>();

		return Obj;
	}

	return nullptr;
}

CGameObject* CClientManager3D::CreateObj1(CScene* Scene, size_t Type)
{
	CGameObject* Obj = nullptr;

	if (Type == typeid(CSlidingBox).hash_code())
	{
		CSlidingBox* Obj = Scene->LoadGameObject<CSlidingBox>();

		return Obj;
	}

	else if (Type == typeid(CHealFlower).hash_code())
	{
		CHealFlower* Obj = Scene->LoadGameObject<CHealFlower>();

		return Obj;
	}

	else if (Type == typeid(CSmallTree1).hash_code())
	{
		CSmallTree1* Obj = Scene->LoadGameObject<CSmallTree1>();

		return Obj;
	}

	else if (Type == typeid(CSmallTree2).hash_code())
	{
		CSmallTree2* Obj = Scene->LoadGameObject<CSmallTree2>();

		return Obj;
	}

	else if (Type == typeid(CSmallTree3).hash_code())
	{
		CSmallTree3* Obj = Scene->LoadGameObject<CSmallTree3>();

		return Obj;
	}

	else if (Type == typeid(CSmallTree4).hash_code())
	{
		CSmallTree4* Obj = Scene->LoadGameObject<CSmallTree4>();

		return Obj;
	}

	else if (Type == typeid(CSmallTree5).hash_code())
	{
		CSmallTree5* Obj = Scene->LoadGameObject<CSmallTree5>();

		return Obj;
	}

	else if (Type == typeid(CTree1).hash_code())
	{
		CTree1* Obj = Scene->LoadGameObject<CTree1>();

		return Obj;
	}

	else if (Type == typeid(CTree2).hash_code())
	{
		CTree2* Obj = Scene->LoadGameObject<CTree2>();

		return Obj;
	}

	else if (Type == typeid(CTree3).hash_code())
	{
		CTree3* Obj = Scene->LoadGameObject<CTree3>();

		return Obj;
	}

	else if (Type == typeid(CTree4).hash_code())
	{
		CTree4* Obj = Scene->LoadGameObject<CTree4>();

		return Obj;
	}

	else if (Type == typeid(CTree5).hash_code())
	{
		CTree5* Obj = Scene->LoadGameObject<CTree5>();

		return Obj;
	}

	else if (Type == typeid(CTree6).hash_code())
	{
		CTree6* Obj = Scene->LoadGameObject<CTree6>();

		return Obj;
	}

	else if (Type == typeid(CTree7).hash_code())
	{
		CTree7* Obj = Scene->LoadGameObject<CTree7>();

		return Obj;
	}

	else if (Type == typeid(CTree8).hash_code())
	{
		CTree8* Obj = Scene->LoadGameObject<CTree8>();

		return Obj;
	}

	else if (Type == typeid(CTree9).hash_code())
	{
		CTree9* Obj = Scene->LoadGameObject<CTree9>();

		return Obj;
	}

	else if (Type == typeid(CBigTree).hash_code())
	{
		CBigTree* Obj = Scene->LoadGameObject<CBigTree>();

		return Obj;
	}

	else if (Type == typeid(CBrokenTree1).hash_code())
	{
		CBrokenTree1* Obj = Scene->LoadGameObject<CBrokenTree1>();

		return Obj;
	}

	else if (Type == typeid(CBrokenTree2).hash_code())
	{
		CBrokenTree2* Obj = Scene->LoadGameObject<CBrokenTree2>();

		return Obj;
	}

	else if (Type == typeid(CBrokenTree3).hash_code())
	{
		CBrokenTree3* Obj = Scene->LoadGameObject<CBrokenTree3>();

		return Obj;
	}

	else if (Type == typeid(CMushRoom1).hash_code())
	{
		CMushRoom1* Obj = Scene->LoadGameObject<CMushRoom1>();

		return Obj;
	}

	else if (Type == typeid(CMushRoom2).hash_code())
	{
		CMushRoom2* Obj = Scene->LoadGameObject<CMushRoom2>();

		return Obj;
	}

	else if (Type == typeid(CMushRoom3).hash_code())
	{
		CMushRoom3* Obj = Scene->LoadGameObject<CMushRoom3>();

		return Obj;
	}

	else if (Type == typeid(CGrass1).hash_code())
	{
		CGrass1* Obj = Scene->LoadGameObject<CGrass1>();

		return Obj;
	}

	else if (Type == typeid(CGrass2).hash_code())
	{
		CGrass2* Obj = Scene->LoadGameObject<CGrass2>();

		return Obj;
	}

	else if (Type == typeid(CGrass3).hash_code())
	{
		CGrass3* Obj = Scene->LoadGameObject<CGrass3>();

		return Obj;
	}

	else if (Type == typeid(CGrass4).hash_code())
	{
		CGrass4* Obj = Scene->LoadGameObject<CGrass4>();

		return Obj;
	}

	else if (Type == typeid(CGrass5).hash_code())
	{
		CGrass5* Obj = Scene->LoadGameObject<CGrass5>();

		return Obj;
	}

	else if (Type == typeid(CGrass6).hash_code())
	{
		CGrass6* Obj = Scene->LoadGameObject<CGrass6>();

		return Obj;
	}

	else if (Type == typeid(CGrass7).hash_code())
	{
		CGrass7* Obj = Scene->LoadGameObject<CGrass7>();

		return Obj;
	}

	else if (Type == typeid(CGrass8).hash_code())
	{
		CGrass8* Obj = Scene->LoadGameObject<CGrass8>();

		return Obj;
	}

	else if (Type == typeid(CGrass9).hash_code())
	{
		CGrass9* Obj = Scene->LoadGameObject<CGrass9>();

		return Obj;
	}

	else if (Type == typeid(CVine).hash_code())
	{
		CVine* Obj = Scene->LoadGameObject<CVine>();

		return Obj;
	}

	else if (Type == typeid(CVine2).hash_code())
	{
		CVine2* Obj = Scene->LoadGameObject<CVine2>();

		return Obj;
	}

	else if (Type == typeid(CVine3).hash_code())
	{
		CVine3* Obj = Scene->LoadGameObject<CVine3>();

		return Obj;
	}

	else if (Type == typeid(CVine4).hash_code())
	{
		CVine4* Obj = Scene->LoadGameObject<CVine4>();

		return Obj;
	}

	else if (Type == typeid(CVine5).hash_code())
	{
		CVine5* Obj = Scene->LoadGameObject<CVine5>();

		return Obj;
	}

	else if (Type == typeid(CPrecipice).hash_code())
	{
		CPrecipice* Obj = Scene->LoadGameObject<CPrecipice>();

		return Obj;
	}

	else if (Type == typeid(CPrecipice2).hash_code())
	{
		CPrecipice2* Obj = Scene->LoadGameObject<CPrecipice2>();

		return Obj;
	}

	else if (Type == typeid(CSculpture).hash_code())
	{
		CSculpture* Obj = Scene->LoadGameObject<CSculpture>();

		return Obj;
	}

	else if (Type == typeid(CSmallStone1).hash_code())
	{
		CSmallStone1* Obj = Scene->LoadGameObject<CSmallStone1>();

		return Obj;
	}

	else if (Type == typeid(CGrassRock1).hash_code())
	{
		CSmallStone1* Obj = Scene->LoadGameObject<CSmallStone1>();

		return Obj;
	}

	else if (Type == typeid(CGrassRock2).hash_code())
	{
		CGrassRock2* Obj = Scene->LoadGameObject<CGrassRock2>();

		return Obj;
	}

	else if (Type == typeid(CGrassRock3).hash_code())
	{
		CGrassRock3* Obj = Scene->LoadGameObject<CGrassRock3>();

		return Obj;
	}

	else if (Type == typeid(CGrassRock4).hash_code())
	{
		CGrassRock4* Obj = Scene->LoadGameObject<CGrassRock4>();

		return Obj;
	}

	else if (Type == typeid(CGrassRock5).hash_code())
	{
		CGrassRock5* Obj = Scene->LoadGameObject<CGrassRock5>();

		return Obj;
	}

	else if (Type == typeid(CGrassRock6).hash_code())
	{
		CGrassRock6* Obj = Scene->LoadGameObject<CGrassRock6>();

		return Obj;
	}

	else if (Type == typeid(CGrassRock7).hash_code())
	{
		CGrassRock7* Obj = Scene->LoadGameObject<CGrassRock7>();

		return Obj;
	}

	else if (Type == typeid(CGrassRock8).hash_code())
	{
		CGrassRock8* Obj = Scene->LoadGameObject<CGrassRock8>();

		return Obj;
	}

	else if (Type == typeid(CGrassRock9).hash_code())
	{
		CGrassRock9* Obj = Scene->LoadGameObject<CGrassRock9>();

		return Obj;
	}

	else if (Type == typeid(CWreck1).hash_code())
	{
		CWreck1* Obj = Scene->LoadGameObject<CWreck1>();

		return Obj;
	}

	else if (Type == typeid(CSmallGrass).hash_code())
	{
		CSmallGrass* Obj = Scene->LoadGameObject<CSmallGrass>();

		return Obj;
	}

	else if (Type == typeid(CTent1).hash_code())
	{
		CTent1* Obj = Scene->LoadGameObject<CTent1>();

		return Obj;
	}

	else if (Type == typeid(CTent2).hash_code())
	{
		CTent2* Obj = Scene->LoadGameObject<CTent2>();

		return Obj;
	}

	else if (Type == typeid(CBox1).hash_code())
	{
		CBox1* Obj = Scene->LoadGameObject<CBox1>();

		return Obj;
	}

	else if (Type == typeid(CFar).hash_code())
	{
		CFar* Obj = Scene->LoadGameObject<CFar>();

		return Obj;
	}

	return nullptr;
}

CGameObject* CClientManager3D::CreateObj2(CScene* Scene, size_t Type)
{
	CGameObject* Obj = nullptr;

	if (Type == typeid(CDesertPebble).hash_code())
	{
		CDesertPebble* Obj = Scene->LoadGameObject<CDesertPebble>();

		return Obj;
	}

	else if (Type == typeid(CDesertSmallStone).hash_code())
	{
		CDesertSmallStone* Obj = Scene->LoadGameObject<CDesertSmallStone>();

		return Obj;
	}

	else if (Type == typeid(CDesertStone1).hash_code())
	{
		CDesertStone1* Obj = Scene->LoadGameObject<CDesertStone1>();

		return Obj;
	}

	else if (Type == typeid(CDesertStone2).hash_code())
	{
		CDesertStone2* Obj = Scene->LoadGameObject<CDesertStone2>();

		return Obj;
	}

	else if (Type == typeid(CDesertStone3).hash_code())
	{
		CDesertStone3* Obj = Scene->LoadGameObject<CDesertStone3>();

		return Obj;
	}

	else if (Type == typeid(CDesertStone4).hash_code())
	{
		CDesertStone4* Obj = Scene->LoadGameObject<CDesertStone4>();

		return Obj;
	}

	else if (Type == typeid(CDesertStone5).hash_code())
	{
		CDesertStone5* Obj = Scene->LoadGameObject<CDesertStone5>();

		return Obj;
	}

	else if (Type == typeid(CDesertStone6).hash_code())
	{
		CDesertStone6* Obj = Scene->LoadGameObject<CDesertStone6>();

		return Obj;
	}

	else if (Type == typeid(CDesertBigStone).hash_code())
	{
		CDesertBigStone* Obj = Scene->LoadGameObject<CDesertBigStone>();

		return Obj;
	}

	else if (Type == typeid(CDesertRockWall).hash_code())
	{
		CDesertRockWall* Obj = Scene->LoadGameObject<CDesertRockWall>();

		return Obj;
	}

	else if (Type == typeid(CDesertStalactite1).hash_code())
	{
		CDesertStalactite1* Obj = Scene->LoadGameObject<CDesertStalactite1>();

		return Obj;
	}

	else if (Type == typeid(CDesertStalactite2).hash_code())
	{
		CDesertStalactite2* Obj = Scene->LoadGameObject<CDesertStalactite2>();

		return Obj;
	}

	else if (Type == typeid(CDesertStalactite3).hash_code())
	{
		CDesertStalactite3* Obj = Scene->LoadGameObject<CDesertStalactite3>();

		return Obj;
	}

	else if (Type == typeid(CDesertStalactite4).hash_code())
	{
		CDesertStalactite4* Obj = Scene->LoadGameObject<CDesertStalactite4>();

		return Obj;
	}

	else if (Type == typeid(CDesertStalagmite1).hash_code())
	{
		CDesertStalagmite1* Obj = Scene->LoadGameObject<CDesertStalagmite1>();

		return Obj;
	}

	else if (Type == typeid(CDesertStalagmite2).hash_code())
	{
		CDesertStalagmite2* Obj = Scene->LoadGameObject<CDesertStalagmite2>();

		return Obj;
	}

	else if (Type == typeid(CDesertStalagmite3).hash_code())
	{
		CDesertStalagmite3* Obj = Scene->LoadGameObject<CDesertStalagmite3>();

		return Obj;
	}

	else if (Type == typeid(CStonej1).hash_code())
	{
		CStonej1* Obj = Scene->LoadGameObject<CStonej1>();

		return Obj;
	}

	else if (Type == typeid(CStonej2).hash_code())
	{
		CStonej2* Obj = Scene->LoadGameObject<CStonej2>();

		return Obj;
	}

	else if (Type == typeid(CStonej3).hash_code())
	{
		CStonej3* Obj = Scene->LoadGameObject<CStonej3>();

		return Obj;
	}

	else if (Type == typeid(CStonej4).hash_code())
	{
		CStonej4* Obj = Scene->LoadGameObject<CStonej4>();

		return Obj;
	}

	else if (Type == typeid(CStonej5).hash_code())
	{
		CStonej5* Obj = Scene->LoadGameObject<CStonej5>();

		return Obj;
	}

	else if (Type == typeid(CStonej6).hash_code())
	{
		CStonej6* Obj = Scene->LoadGameObject<CStonej6>();

		return Obj;
	}

	else if (Type == typeid(CStonej7).hash_code())
	{
		CStonej7* Obj = Scene->LoadGameObject<CStonej7>();

		return Obj;
	}

	else if (Type == typeid(CStonej8).hash_code())
	{
		CStonej8* Obj = Scene->LoadGameObject<CStonej8>();

		return Obj;
	}

	else if (Type == typeid(CStonej9).hash_code())
	{
		CStonej9* Obj = Scene->LoadGameObject<CStonej9>();

		return Obj;
	}

	else if (Type == typeid(CStonej10).hash_code())
	{
		CStonej10* Obj = Scene->LoadGameObject<CStonej10>();

		return Obj;
	}

	else if (Type == typeid(CStonej11).hash_code())
	{
		CStonej11* Obj = Scene->LoadGameObject<CStonej11>();

		return Obj;
	}

	else if (Type == typeid(CStonej12).hash_code())
	{
		CStonej12* Obj = Scene->LoadGameObject<CStonej12>();

		return Obj;
	}

	else if (Type == typeid(CStonej13).hash_code())
	{
		CStonej13* Obj = Scene->LoadGameObject<CStonej13>();

		return Obj;
	}

	else if (Type == typeid(CStonej14).hash_code())
	{
		CStonej14* Obj = Scene->LoadGameObject<CStonej14>();

		return Obj;
	}

	else if (Type == typeid(CStonej15).hash_code())
	{
		CStonej15* Obj = Scene->LoadGameObject<CStonej15>();

		return Obj;
	}

	else if (Type == typeid(CStonej16).hash_code())
	{
		CStonej16* Obj = Scene->LoadGameObject<CStonej16>();

		return Obj;
	}

	else if (Type == typeid(CStonej17).hash_code())
	{
		CStonej17* Obj = Scene->LoadGameObject<CStonej17>();

		return Obj;
	}

	else if (Type == typeid(CStonej18).hash_code())
	{
		CStonej18* Obj = Scene->LoadGameObject<CStonej18>();

		return Obj;
	}

	else if (Type == typeid(CStonej19).hash_code())
	{
		CStonej19* Obj = Scene->LoadGameObject<CStonej19>();

		return Obj;
	}

	else if (Type == typeid(CStonej20).hash_code())
	{
		CStonej20* Obj = Scene->LoadGameObject<CStonej20>();

		return Obj;
	}

	else if (Type == typeid(CStonej21).hash_code())
	{
		CStonej21* Obj = Scene->LoadGameObject<CStonej21>();

		return Obj;
	}

	else if (Type == typeid(CStonej22).hash_code())
	{
		CStonej22* Obj = Scene->LoadGameObject<CStonej22>();

		return Obj;
	}

	else if (Type == typeid(CStonej23).hash_code())
	{
		CStonej23* Obj = Scene->LoadGameObject<CStonej23>();

		return Obj;
	}

	else if (Type == typeid(CStonej24).hash_code())
	{
		CStonej24* Obj = Scene->LoadGameObject<CStonej24>();

		return Obj;
	}

	else if (Type == typeid(CStonej25).hash_code())
	{
		CStonej25* Obj = Scene->LoadGameObject<CStonej25>();

		return Obj;
	}

	else if (Type == typeid(CStonej26).hash_code())
	{
		CStonej26* Obj = Scene->LoadGameObject<CStonej26>();

		return Obj;
	}

	else if (Type == typeid(CStonej27).hash_code())
	{
		CStonej27* Obj = Scene->LoadGameObject<CStonej27>();

		return Obj;
	}

	else if (Type == typeid(CStonej28).hash_code())
	{
		CStonej28* Obj = Scene->LoadGameObject<CStonej28>();

		return Obj;
	}

	else if (Type == typeid(CStonej29).hash_code())
	{
		CStonej29* Obj = Scene->LoadGameObject<CStonej29>();

		return Obj;
	}

	else if (Type == typeid(CStonej30).hash_code())
	{
		CStonej30* Obj = Scene->LoadGameObject<CStonej30>();

		return Obj;
	}

	else if (Type == typeid(CStonej31).hash_code())
	{
		CStonej31* Obj = Scene->LoadGameObject<CStonej31>();

		return Obj;
	}

	else if (Type == typeid(CStonej32).hash_code())
	{
		CStonej32* Obj = Scene->LoadGameObject<CStonej32>();

		return Obj;
	}

	else if (Type == typeid(CStonej33).hash_code())
	{
		CStonej33* Obj = Scene->LoadGameObject<CStonej33>();

		return Obj;
	}

	else if (Type == typeid(CStonej34).hash_code())
	{
		CStonej34* Obj = Scene->LoadGameObject<CStonej34>();

		return Obj;
	}

	else if (Type == typeid(CStonej35).hash_code())
	{
		CStonej35* Obj = Scene->LoadGameObject<CStonej35>();

		return Obj;
	}

	else if (Type == typeid(CStonej36).hash_code())
	{
		CStonej36* Obj = Scene->LoadGameObject<CStonej36>();

		return Obj;
	}

	else if (Type == typeid(CStonej37).hash_code())
	{
		CStonej37* Obj = Scene->LoadGameObject<CStonej37>();

		return Obj;
	}

	else if (Type == typeid(CTownBarrel).hash_code())
	{
		CTownBarrel* Obj = Scene->LoadGameObject<CTownBarrel>();

		return Obj;
	}

	else if (Type == typeid(CTownCarriage).hash_code())
	{
		CTownCarriage* Obj = Scene->LoadGameObject<CTownCarriage>();

		return Obj;
	}

	else if (Type == typeid(CTownCheckPoint).hash_code())
	{
		CTownCheckPoint* Obj = Scene->LoadGameObject<CTownCheckPoint>();

		return Obj;
	}

	else if (Type == typeid(CTownDragonHead).hash_code())
	{
		CTownDragonHead* Obj = Scene->LoadGameObject<CTownDragonHead>();

		return Obj;
	}

	else if (Type == typeid(CTownPassage).hash_code())
	{
		CTownPassage* Obj = Scene->LoadGameObject<CTownPassage>();

		return Obj;
	}

	else if (Type == typeid(CTownPumpkinMan).hash_code())
	{
		CTownPumpkinMan* Obj = Scene->LoadGameObject<CTownPumpkinMan>();

		return Obj;
	}

	else if (Type == typeid(CTownRampart).hash_code())
	{
		CTownRampart* Obj = Scene->LoadGameObject<CTownRampart>();

		return Obj;
	}

	else if (Type == typeid(CTownShadeScreen).hash_code())
	{
		CTownShadeScreen* Obj = Scene->LoadGameObject<CTownShadeScreen>();

		return Obj;
	}

	else if (Type == typeid(CTownSign).hash_code())
	{
		CTownSign* Obj = Scene->LoadGameObject<CTownSign>();

		return Obj;
	}

	else if (Type == typeid(CTownStructure).hash_code())
	{
		CTownStructure* Obj = Scene->LoadGameObject<CTownStructure>();

		return Obj;
	}

	else if (Type == typeid(CTownSummerHouse).hash_code())
	{
		CTownSummerHouse* Obj = Scene->LoadGameObject<CTownSummerHouse>();

		return Obj;
	}

	else if (Type == typeid(CTownTunnel).hash_code())
	{
		CTownTunnel* Obj = Scene->LoadGameObject<CTownTunnel>();

		return Obj;
	}

	else if (Type == typeid(CDesertMountain1).hash_code())
	{
		CDesertMountain1* Obj = Scene->LoadGameObject<CDesertMountain1>();

		return Obj;
	}

	else if (Type == typeid(CDesertMountain2).hash_code())
	{
		CDesertMountain2* Obj = Scene->LoadGameObject<CDesertMountain2>();

		return Obj;
	}

	return nullptr;
}

CMainSceneMode* CClientManager3D::GetMainScene() const
{
	CSceneMode* SceneMode = CSceneManager::GetInst()->GetScene()->GetSceneMode();

	return dynamic_cast<CMainSceneMode*>(SceneMode);
}

void CClientManager3D::PlayBattleBGM(BGM_Type BGMType)
{
	CMainSceneMode* Scene = GetMainScene();

	if (!Scene)
		return;

	Scene->PlayBattleBGM(BGMType);
}

const char* CClientManager3D::GetHierarchyName(Object_Type Type) const
{
	switch (Type)
	{
	case Object_Type::Player:
		return "플레이어";
	case Object_Type::Monster:
		return "몬스터";
	case Object_Type::LandScape:
		return "지형";
	case Object_Type::FieldObj:
		return "필드";
	}

	return "";
}

void CClientManager3D::BGMSoundLoad()
{
	CResourceManager::GetInst()->LoadSound("BGM", true, "MainMenu", "Bgm/MainMenu.flac");

	CResourceManager::GetInst()->LoadSound("BGM", true, "TownBGM", "Bgm/Town.flac");

	CResourceManager::GetInst()->LoadSound("MonsterBattleBGM", true, "MonsterBattle", "Bgm/MonsterBattle.flac");

	CResourceManager::GetInst()->LoadSound("JoinBGM", false, "Stage1Join", "Bgm/Stage1Join.flac");
	CResourceManager::GetInst()->LoadSound("BGM", true, "BossBattle", "Bgm/BossBattle.mp3");
	CResourceManager::GetInst()->LoadSound("BGM", true, "QuestComplete", "Bgm/QuestComplete.flac");

	CResourceManager::GetInst()->LoadSound("JoinBGM", false, "Stage2Join", "Bgm/Stage2Join.flac");
	CResourceManager::GetInst()->LoadSound("BGM", true, "FinalBossBattle", "Bgm/FinalBossBattle.flac");
	CResourceManager::GetInst()->LoadSound("BGM", true, "FinalQuestComplete", "Bgm/FinalQuestComplete.flac");

	CResourceManager::GetInst()->LoadSound("BGM", true, "Ending", "Bgm/Ending.mp3");

	CResourceManager::GetInst()->LoadSound("Environment", true, "Stage1Env", "Bgm/Stage1Env.ogg");
	CResourceManager::GetInst()->LoadSound("Environment", true, "2StageSound", "Bgm/2StageSound.mp3");
}

void CClientManager3D::BGMSoundStop()
{
	CResourceManager::GetInst()->SoundStop("MainMenu");

	CResourceManager::GetInst()->SoundStop("TownBGM");

	CResourceManager::GetInst()->SoundStop("MonsterBattle");

	CResourceManager::GetInst()->SoundStop("Stage1Join");
	CResourceManager::GetInst()->SoundStop("BossBattle");
	CResourceManager::GetInst()->SoundStop("QuestComplete");

	CResourceManager::GetInst()->SoundStop("Stage2Join");
	CResourceManager::GetInst()->SoundStop("FinalBossBattle");
	CResourceManager::GetInst()->SoundStop("FinalQuestComplete");

	CResourceManager::GetInst()->SoundStop("Ending");

	CResourceManager::GetInst()->SoundStop("Stage1Env");
	CResourceManager::GetInst()->SoundStop("2StageSound");
}

void CClientManager3D::AddSound()
{
	// 플레이어 활 관련 사운드
	CResourceManager::GetInst()->LoadSound("Effect", false, "ArrowHitted", "Bow/ArrowHitted.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect", false, "ArrowShoot", "Bow/ArrowShoot.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect", false, "ChargingBow", "Bow/ChargingBow.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect", false, "ChargingCount", "Bow/ChargingCount.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect", true, "ChargingLoop", "Bow/ChargingLoop.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect", false, "ChargingStart", "Bow/ChargingStart.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect", false, "DragonCharge", "Bow/Dragon_Piercer_Charge.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect", false, "DragonShot", "Bow/DragonShot.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect", false, "DragonStart", "Bow/DragonStart.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect", false, "DrawBow", "Bow/DrawBow.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect", false, "SheatheBow", "Bow/SheatheBow.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect", false, "Remove_coating", "Bow/Remove_coating.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect", false, "PowerShot", "Bow/PowerShot.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect", false, "BowChargingCount", "Bow/BowChargingCount.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect", false, "EvadeSound", "Player/EvadeSound.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect", false, "ArrowShot", "Bow/ArrowShot.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect", false, "ArrowDrop", "Bow/ArrowDrop.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect", false, "ArrowShotHight", "Bow/ArrowShotHight.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect", false, "PlayerShot1", "Player/Action/PlayerShot1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect", false, "PlayerShot2", "Player/Action/PlayerShot2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect", false, "PlayerStamina", "Player/Action/PlayerStamina.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect2", false, "Carving", "Player/Carving.mp3", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Effect", false, "ArrowHit", "Bow/ArrowHit.ogg", SOUND_PATH);

	// 플레이어 스텝 사운드
	// Sand
	CResourceManager::GetInst()->LoadSound("Step", false, "SandStep1", "Player/Step/Sand/SandStep1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Step", false, "SandStep2", "Player/Step/Sand/SandStep2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Step", false, "SandStep3", "Player/Step/Sand/SandStep3.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Step", false, "SandStep4", "Player/Step/Sand/SandStep4.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Step", false, "SandStep5", "Player/Step/Sand/SandStep5.ogg", SOUND_PATH);

	// Dirt
	CResourceManager::GetInst()->LoadSound("Step", false, "DirtStep1", "Player/Step/Dirt/DirtStep1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Step", false, "DirtStep2", "Player/Step/Dirt/DirtStep2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Step", false, "DirtStep3", "Player/Step/Dirt/DirtStep3.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Step", false, "DirtStep4", "Player/Step/Dirt/DirtStep4.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Step", false, "DirtStep5", "Player/Step/Dirt/DirtStep5.ogg", SOUND_PATH);

	// Stone
	CResourceManager::GetInst()->LoadSound("Step", false, "StoneStep1", "Player/Step/Stone/StoneStep2.ogg", SOUND_PATH);


	//일반 몬스터 사운드
	//barnos
	CResourceManager::GetInst()->LoadSound("Barnos", false, "BarnosAttack1", "Monster/Barnos/attack1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Barnos", false, "BarnosAttack2", "Monster/Barnos/attack2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Barnos", false, "BarnosAttack3", "Monster/Barnos/attack3.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Barnos", false, "BarnosDeath", "Monster/Barnos/death.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Barnos", false, "BarnosHit", "Monster/Barnos/hit.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Barnos", false, "BarnosScream", "Monster/Barnos/scream.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Barnos", true, "BarnosWing1", "Monster/Barnos/wing1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Barnos", true, "BarnosWing2", "Monster/Barnos/wing2.ogg", SOUND_PATH);

	//vespoid
	CResourceManager::GetInst()->LoadSound("Vespoid", false, "VespoidAttack1", "Monster/Vespoid/attack1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Vespoid", false, "VespoidAttack2", "Monster/Vespoid/attack2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Vespoid", false, "VespoidDeath", "Monster/Vespoid/death.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Vespoid", false, "VespoidHit", "Monster/Vespoid/hit.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Vespoid", false, "VespoidScream", "Monster/Vespoid/scream.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Vespoid", true, "VespoidWing", "Monster/Vespoid/wing.ogg", SOUND_PATH);

	//jagras
	CResourceManager::GetInst()->LoadSound("Jagras", false, "JagrasIdle", "Monster/Jagras/idle.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Jagras", false, "JagrasDeath", "Monster/Jagras/death.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Jagras", false, "JagrasScream", "Monster/Jagras/scream.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Jagras", false, "JagrasHit", "Monster/Jagras/hit.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Jagras", false, "JagrasAttack1", "Monster/Jagras/attack1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Jagras", false, "JagrasAttack2", "Monster/Jagras/attack2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Jagras", false, "JagrasAttack3", "Monster/Jagras/attack3.ogg", SOUND_PATH);

	//kestodon
	CResourceManager::GetInst()->LoadSound("Kestodon", true, "KestodonCharge", "Monster/Kestodon/charge.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Kestodon", false, "KestodonDeath", "Monster/Kestodon/death.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Kestodon", false, "KestodonScream", "Monster/Kestodon/scream.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Kestodon", false, "KestodonHit", "Monster/Kestodon/hit.ogg", SOUND_PATH);

	//mernos
	CResourceManager::GetInst()->LoadSound("Mernos", false, "MernosWing", "Monster/Mernos/wing.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Mernos", false, "MernosVoice1", "Monster/Mernos/voice1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Mernos", false, "MernosVoice2", "Monster/Mernos/voice2.ogg", SOUND_PATH);

	// Anjanath
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathMeetRoaring", "Boss/Anjanath/FirstRoaring.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathBreathReady1", "Boss/Anjanath/Breath_Ready1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathBreathReady2", "Boss/Anjanath/Breath_Ready2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathIdle1", "Boss/Anjanath/Idle1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathIdle2", "Boss/Anjanath/Idle2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathIdle3", "Boss/Anjanath/Idle3.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathChargeAttack1", "Boss/Anjanath/ChargeAttack1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathChargeAttack2", "Boss/Anjanath/ChargeAttack2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathBiteAttack1", "Boss/Anjanath/Mouth_Attack1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathBiteAttack2", "Boss/Anjanath/Mouth_Attack2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathBiteReady", "Boss/Anjanath/BiteReady.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathBiteAttackEnd", "Boss/Anjanath/PentaBiteEnd.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathRoaring1", "Boss/Anjanath/Roar1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathRoaring2", "Boss/Anjanath/Roar2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathCriticalDamage", "Boss/Anjanath/Critical_Damaged.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathDead", "Boss/Anjanath/Dead.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathBiteAttackSE", "Boss/Anjanath/SE/MouseGrap.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathBreathSE", "Boss/Anjanath/SE/Short_Breath.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathSlowStep1SE", "Boss/Anjanath/SE/SlowStep_Dirt1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathSlowStep2SE", "Boss/Anjanath/SE/SlowStep_Dirt2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathFastStep1SE", "Boss/Anjanath/SE/FastStep_Dirt1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathFastStep2SE", "Boss/Anjanath/SE/FastStep_Dirt2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Anjanath", false, "AnjanathFastStep3SE", "Boss/Anjanath/SE/FastStep_Dirt3.ogg", SOUND_PATH);

	// Rathalos

	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosBiteAttack1", "Boss/Rathalos/BiteAttack1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosBiteAttack2", "Boss/Rathalos/BiteAttack2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosBreathReady", "Boss/Rathalos/BreathReady.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosBreathAttack1", "Boss/Rathalos/BreathAttack1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosBreathAttack2", "Boss/Rathalos/BreathAttack2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosChargeAttack1", "Boss/Rathalos/ChargeAttack1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosChargeEnd", "Boss/Rathalos/ChargeEnd.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosCriticalDamaged1", "Boss/Rathalos/CriticalDamged1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosCriticalDamaged2", "Boss/Rathalos/CriticalDamged2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosDead", "Boss/Rathalos/Dead.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosFlyBreath1", "Boss/Rathalos/FlyBreath1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosIdle1", "Boss/Rathalos/Idle1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosIdle2", "Boss/Rathalos/Idle2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosRoarReady", "Boss/Rathalos/RoarReady1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosRoaringMeet", "Boss/Rathalos/MeetRoar.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosNormalRoar1", "Boss/Rathalos/NormalRoar1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosNormalRoar2", "Boss/Rathalos/NormalRoar2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosShortRoar1", "Boss/Rathalos/ShortRoar1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosBreath1", "Boss/Rathalos/ShortBreath1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosTailAttack1", "Boss/Rathalos/TailAttack1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosTailAttack2", "Boss/Rathalos/TailAttack2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosFlyBreathAttack1", "Boss/Rathalos/FlyBreath.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosFlyBreathAttack2", "Boss/Rathalos/FlyBreath1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosFastFootStep1SE", "Boss/Rathalos/SE/FastFootStep1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosFastFootStep2SE", "Boss/Rathalos/SE/FastFootStep2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosSlowFootStep1SE", "Boss/Rathalos/SE/SlowStep_Dirt1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosSlowFootStep2SE", "Boss/Rathalos/SE/SlowStep_Dirt2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosFlyAir1SE", "Boss/Rathalos/SE/FlyAir1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosShortBreath1SE", "Boss/Rathalos/SE/ShortBreath1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosShortBreath2SE", "Boss/Rathalos/SE/ShortBreath2.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Rathalos", false, "RathalosFlyBreathSE", "Boss/Rathalos/SE/FlyBreath.ogg", SOUND_PATH);


	CResourceManager::GetInst()->LoadSound("UI", false, "BottleSwap", "UI/GlassSlotSelectSound.ogg", SOUND_PATH);

	BGMSoundLoad();
}
