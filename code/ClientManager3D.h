#pragma once

#include "GameInfo.h"

class CClientManager3D
{
public:
	bool Init(HINSTANCE hInst);
	void CreateDefaultSceneMode();
	int Run();

	void CreateSceneMode(class CScene* Scene, size_t Type);
	class CGameObject* CreateObject(class CScene* Scene, size_t Type);
	class CComponent* CreateComponent(class CGameObject* Obj, size_t Type);

private:
	class CGameObject* CreateCharacter(CScene* Scene, size_t Type);
	class CGameObject* CreateObj1(CScene* Scene, size_t Type);
	class CGameObject* CreateObj2(CScene* Scene, size_t Type);

public:
	class CMainSceneMode* GetMainScene()	const;
	void PlayBattleBGM(BGM_Type BGMType);

public:
	const char* GetHierarchyName(Object_Type Type)	const;

public:
	void BGMSoundLoad();
	void BGMSoundStop();

private:
	void AddSound();

public:
	DECLARE_SINGLE(CClientManager3D)
};

