#pragma once

#include "Scene/SceneMode.h"
#include "Object_Info.h"
class CMainSceneMode :
	public CSceneMode
{
public:
	CMainSceneMode();
	~CMainSceneMode();

private:
	CSharedPtr<class CMainWindow> m_MainWindow;
	std::function<void(bool, float)> m_LoadingFunction;
	std::vector<Object_Info*> m_vecObjectInfo;
	float	m_BGMFadeScale;
	float	m_BGMFadeScale2; // FadeIn
	int		m_MonsterAggroCount;	// 0일 시 브금중단
	BGM_Type	m_BGMBattleType; // 적과 배틀 시 사용될 음악

public:
	void AddMonsterAggro()
	{
		++m_MonsterAggroCount;
	}

	void SubMonsterAggro()
	{
		--m_MonsterAggroCount;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	const CharacterInfo* GetCharacterInfo(const std::string& CharacterName)  const;

private:
	void LoadMesh();
	void CreateMaterial();
	void CreateAnimationSequence();
	void CreateBillboardSequence();
	void CreateParticle();
	void AddWeaponSocket();
	void AddMonsterSocket();
	void AddLargeMonsterSocket();
	void LoadSceneFile(const char* FileName, const std::string& PathName = DATA_PATH);
	void CreateSequence(const std::string& Name, const TCHAR* FileName, int CountX, int CountY, float SizeX, float SizeY);

private:
	void AddLandScape(std::vector<TCHAR*>& vec, const TCHAR* Path);
	void SetLandScape(int Register, const std::string& Name, std::vector<TCHAR*>& vecFileName, const std::string& PathName = TEXTURE_PATH);

	void SetCheckPointFunc();

public:
	void PlayBattleBGM(BGM_Type BGMType);

public:
	template <typename T>
	void SetLoadingFunction(T* Obj, void(T::* Func)(bool, float))
	{
		m_LoadingFunction = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
	}
};

