
#include "MainSceneMode.h"
#include "PathManager.h"
#include "Scene/Scene.h"
#include "Excel/Excel.h"
#include "Excel/ExcelManager.h"
#include "GameInfo.h"
#include "../ClientManager3D.h"
#include "../Object/Player.h"
#include "../Object/LandScapeObj.h"
#include "../Object/Barnos.h"
#include "../Object/Jagras.h"
#include "../Object/Kestodon.h"
#include "../Object/Vespoid.h"
#include "../Object/Anjanath.h"
#include "../Object/Rathalos.h"
#include "../Object/SlidingBox.h"
#include "../Object/HealFlower.h"
#include "../Object/SmallTree1.h"
#include "../Object/SmallTree2.h"
#include "../Object/SmallTree3.h"
#include "../Object/SmallTree4.h"
#include "../Object/SmallTree5.h"
#include "../Object/Tree1.h"
#include "../Object/Tree2.h"
#include "../Object/Tree3.h"
#include "../Object/Tree4.h"
#include "../Object/Tree5.h"
#include "../Object/Tree6.h"
#include "../Object/Tree7.h"
#include "../Object/Tree8.h"
#include "../Object/Tree9.h"
#include "../Object/BigTree.h"
#include "../Object/BrokenTree1.h"
#include "../Object/BrokenTree2.h"
#include "../Object/BrokenTree3.h"
#include "../Object/MushRoom1.h"
#include "../Object/MushRoom2.h"
#include "../Object/MushRoom3.h"
#include "../Object/Grass1.h"
#include "../Object/Grass2.h"
#include "../Object/Grass3.h"
#include "../Object/Grass4.h"
#include "../Object/Grass5.h"
#include "../Object/Grass6.h"
#include "../Object/Grass7.h"
#include "../Object/Grass8.h"
#include "../Object/Grass9.h"
#include "../Object/SmallGrass.h"
#include "../Object/Vine.h"
#include "../Object/Vine2.h"
#include "../Object/Vine3.h"
#include "../Object/Vine4.h"
#include "../Object/Vine5.h"
#include "../Object/Precipice.h"
#include "../Object/Precipice2.h"
#include "../Object/Sculpture.h"
#include "../Object/SmallStone1.h"
#include "../Object/GrassRock1.h"
#include "../Object/GrassRock2.h"
#include "../Object/GrassRock3.h"
#include "../Object/GrassRock4.h"
#include "../Object/GrassRock5.h"
#include "../Object/GrassRock6.h"
#include "../Object/GrassRock7.h"
#include "../Object/GrassRock8.h"
#include "../Object/GrassRock9.h"
#include "../Object/Wreck1.h"
#include "../Object/Tent1.h"
#include "../Object/Tent2.h"
#include "../Object/Box1.h"
#include "../Object/Far.h"
#include "../Object/DesertPebble.h"
#include "../Object/DesertSmallStone.h"
#include "../Object/DesertStone1.h"
#include "../Object/DesertStone2.h"
#include "../Object/DesertStone3.h"
#include "../Object/DesertStone4.h"
#include "../Object/DesertStone5.h"
#include "../Object/DesertStone6.h"
#include "../Object/DesertBigStone.h"
#include "../Object/DesertRockWall.h"
#include "../Object/DesertStalactite1.h"
#include "../Object/DesertStalactite2.h"
#include "../Object/DesertStalactite3.h"
#include "../Object/DesertStalactite4.h"
#include "../Object/DesertStalagmite1.h"
#include "../Object/DesertStalagmite2.h"
#include "../Object/DesertStalagmite3.h"
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

void CMainSceneMode::LoadSceneFile(const char* FileName, const std::string& PathName)
{
	char	FullPath[MAX_PATH] = {};

	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	if (Info)
		strcpy_s(FullPath, Info->PathMultibyte);

	strcat_s(FullPath, FileName);

	FILE* File = nullptr;

	fopen_s(&File, FullPath, "rb");

	if (!File)
		return;

	CExcel* NewExcel = nullptr;

	size_t SceneNameLen = 0;
	fread(&SceneNameLen, sizeof(size_t), 1, File);

	char SelectSceneMultibyte[128] = {};
	fread(SelectSceneMultibyte, sizeof(char*) * SceneNameLen, 1, File);

	if (!SelectSceneMultibyte)
		ASSERT("if (!SelectSceneMultibyte)");

	size_t ObjectInfoListMax = 0;
	fread(&ObjectInfoListMax, sizeof(size_t), 1, File);

	for (size_t ObjectInfoListi = 0; ObjectInfoListi < ObjectInfoListMax; ++ObjectInfoListi)
	{
		Object_Info* NewInfo = DBG_NEW Object_Info;

		size_t GameObjectListMax = 0;
		fread(&GameObjectListMax, sizeof(size_t), 1, File);

		CGameObject* NewObject = nullptr;

		for (size_t i = 0; i < GameObjectListMax; ++i)
		{
			size_t ObjectNameSize = 0;
			fread(&ObjectNameSize, sizeof(size_t), 1, File);

			char* ObjectNameMultibyte = DBG_NEW char[ObjectNameSize + 1];
			memset(ObjectNameMultibyte, 0, sizeof(char) * ObjectNameSize + 1);
			fread(ObjectNameMultibyte, sizeof(char) * ObjectNameSize, 1, File);

			Object_Type	Type = Object_Type::Max;
			fread(&Type, sizeof(Object_Type), 1, File);
			NewInfo->Type = Type;

			Monster_Type MonsterType = Monster_Type::Max;
			fread(&MonsterType, sizeof(Monster_Type), 1, File);
			NewInfo->MonsterType = MonsterType;

			FieldObj_Type FieldObjType = FieldObj_Type::Max;
			fread(&FieldObjType, sizeof(FieldObj_Type), 1, File);
			NewInfo->FieldObjType = FieldObjType;

			int FieldObjNum = 0;
			fread(&FieldObjNum, sizeof(int), 1, File);
			NewInfo->FieldObjNum = FieldObjNum;

			size_t CharacterInfoListMax = 0;
			fread(&CharacterInfoListMax, sizeof(size_t), 1, File);

			if (CharacterInfoListMax > 0)
			{
				CharacterInfo* NewCharacterInfo = DBG_NEW CharacterInfo;

				char	resultPath[MAX_PATH] = {};
				strcpy_s(resultPath, MAX_PATH, FullPath);

				size_t FullLength = strlen(resultPath);

				for (size_t i = FullLength; i > 0; --i)
				{
					if (resultPath[i] == '\\')
					{
						memset(&resultPath[i], 0, sizeof(char) * (FullLength - i));
						break;
					}
				}

				const char* TypeName = CClientManager3D::GetInst()->GetHierarchyName(Type);

				size_t CharNameLen = 0;
				fread(&CharNameLen, sizeof(size_t), 1, File);

				char CharacterNameMultibyte[128] = {};
				fread(CharacterNameMultibyte, sizeof(char*) * CharNameLen, 1, File);
				NewCharacterInfo->CharacterName = CharacterNameMultibyte;

				if (CharacterNameMultibyte == "")
					ASSERT("if (CharacterNameMultibyte == "")");

				char FileName[128] = {};

				strcpy_s(FileName, 128, TypeName);
				strcat_s(FileName, 128, "_");
				strcat_s(FileName, 128, NewCharacterInfo->CharacterName.c_str());

				NewExcel = CExcelManager::GetInst()->CreateExcel(FileName, resultPath, false);

				if (!NewExcel)
					ASSERT("if (!NewExcel)");

				NewExcel->NextLine(); // AttackMin
				NewCharacterInfo->AttackMin = NewExcel->ReadNumberFloat();

				NewExcel->NewLine();

				NewExcel->NextLine(); // AttackMax
				NewCharacterInfo->AttackMax = NewExcel->ReadNumberFloat();

				NewExcel->NewLine();

				NewExcel->NextLine(); // HP
				NewCharacterInfo->HP = NewExcel->ReadNumberFloat();

				NewExcel->NewLine();

				NewExcel->NextLine(); // Stamina
				NewCharacterInfo->Stamina = NewExcel->ReadNumberFloat();

				NewExcel->NewLine();

				NewExcel->NextLine(); // Speed
				NewCharacterInfo->Speed = NewExcel->ReadNumberFloat();

				NewInfo->CharacterInfoList.push_back(NewCharacterInfo);
			}

			if (NewInfo->Type == Object_Type::Player)
			{
				NewObject = m_Scene->CreateGameObject<CPlayer>(ObjectNameMultibyte);
				SetPlayerObject(NewObject);
			}

			else if (NewInfo->Type == Object_Type::Monster)
			{
				switch (NewInfo->MonsterType)
				{
				case Monster_Type::Barnos:
					NewObject = m_Scene->CreateGameObject<CBarnos>(ObjectNameMultibyte);
					break;
				case Monster_Type::Jagras:
					NewObject = m_Scene->CreateGameObject<CJagras>(ObjectNameMultibyte);
					break;
				case Monster_Type::Kestodon:
					NewObject = m_Scene->CreateGameObject<CKestodon>(ObjectNameMultibyte);
					break;
				case Monster_Type::Vespoid:
					NewObject = m_Scene->CreateGameObject<CVespoid>(ObjectNameMultibyte);
					break;
				case Monster_Type::Anjanath:
					NewObject = m_Scene->CreateGameObject<CAnjanath>(ObjectNameMultibyte);
					break;
				case Monster_Type::Rathalos:
					NewObject = m_Scene->CreateGameObject<CRathalos>(ObjectNameMultibyte);
					break;
				}
			}

			else if (NewInfo->Type == Object_Type::LandScape)
				NewObject = m_Scene->CreateGameObject<CLandScapeObj>(ObjectNameMultibyte);

			else if (NewInfo->Type == Object_Type::FieldObj)
			{
				switch (NewInfo->FieldObjType)
				{
				case FieldObj_Type::SlidingBox:
					NewObject = m_Scene->CreateGameObject<CSlidingBox>(ObjectNameMultibyte);
					break;					
				case FieldObj_Type::HealFlower:
					NewObject = m_Scene->CreateGameObject<CHealFlower>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::SmallTree:
					if (NewInfo->FieldObjNum == 1)
						NewObject = m_Scene->CreateGameObject<CSmallTree1>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 2)
						NewObject = m_Scene->CreateGameObject<CSmallTree2>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 3)
						NewObject = m_Scene->CreateGameObject<CSmallTree3>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 4)
						NewObject = m_Scene->CreateGameObject<CSmallTree4>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 5)
						NewObject = m_Scene->CreateGameObject<CSmallTree5>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::Tree:
					if (NewInfo->FieldObjNum == 1)
						NewObject = m_Scene->CreateGameObject<CTree1>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 2)
						NewObject = m_Scene->CreateGameObject<CTree2>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 3)
						NewObject = m_Scene->CreateGameObject<CTree3>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 4)
						NewObject = m_Scene->CreateGameObject<CTree4>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 5)
						NewObject = m_Scene->CreateGameObject<CTree5>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 6)
						NewObject = m_Scene->CreateGameObject<CTree6>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 7)
						NewObject = m_Scene->CreateGameObject<CTree7>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 8)
						NewObject = m_Scene->CreateGameObject<CTree8>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 9)
						NewObject = m_Scene->CreateGameObject<CTree9>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::BigTree:
					NewObject = m_Scene->CreateGameObject<CBigTree>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::BrokenTree:
					if (NewInfo->FieldObjNum == 1)
						NewObject = m_Scene->CreateGameObject<CBrokenTree1>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 2)
						NewObject = m_Scene->CreateGameObject<CBrokenTree2>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 3)
						NewObject = m_Scene->CreateGameObject<CBrokenTree3>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::MushRoom:
					if (NewInfo->FieldObjNum == 1)
						NewObject = m_Scene->CreateGameObject<CMushRoom1>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 2)
						NewObject = m_Scene->CreateGameObject<CMushRoom2>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 3)
						NewObject = m_Scene->CreateGameObject<CMushRoom3>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::SmallGrass:
					NewObject = m_Scene->CreateGameObject<CSmallGrass>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::Grass:
					if (NewInfo->FieldObjNum == 1)
						NewObject = m_Scene->CreateGameObject<CGrass1>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 2)
						NewObject = m_Scene->CreateGameObject<CGrass2>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 3)
						NewObject = m_Scene->CreateGameObject<CGrass3>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 4)
						NewObject = m_Scene->CreateGameObject<CGrass4>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 5)
						NewObject = m_Scene->CreateGameObject<CGrass5>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 6)
						NewObject = m_Scene->CreateGameObject<CGrass6>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 7)
						NewObject = m_Scene->CreateGameObject<CGrass7>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 8)
						NewObject = m_Scene->CreateGameObject<CGrass8>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 9)
						NewObject = m_Scene->CreateGameObject<CGrass9>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::Vine:
					if (NewInfo->FieldObjNum == 1)
						NewObject = m_Scene->CreateGameObject<CVine>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 2)
						NewObject = m_Scene->CreateGameObject<CVine2>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 3)
						NewObject = m_Scene->CreateGameObject<CVine3>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 4)
						NewObject = m_Scene->CreateGameObject<CVine4>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 5)
						NewObject = m_Scene->CreateGameObject<CVine5>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::Precipice:
					if (NewInfo->FieldObjNum == 1)
						NewObject = m_Scene->CreateGameObject<CPrecipice>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 2)
						NewObject = m_Scene->CreateGameObject<CPrecipice2>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::Sculpture:
					NewObject = m_Scene->CreateGameObject<CSculpture>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::SmallStone:
					NewObject = m_Scene->CreateGameObject<CSmallStone1>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::GrassRock:
					if (NewInfo->FieldObjNum == 1)
						NewObject = m_Scene->CreateGameObject<CGrassRock1>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 2)
						NewObject = m_Scene->CreateGameObject<CGrassRock2>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 3)
						NewObject = m_Scene->CreateGameObject<CGrassRock3>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 4)
						NewObject = m_Scene->CreateGameObject<CGrassRock4>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 5)
						NewObject = m_Scene->CreateGameObject<CGrassRock5>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 6)
						NewObject = m_Scene->CreateGameObject<CGrassRock6>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 7)
						NewObject = m_Scene->CreateGameObject<CGrassRock7>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 8)
						NewObject = m_Scene->CreateGameObject<CGrassRock8>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 9)
						NewObject = m_Scene->CreateGameObject<CGrassRock9>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::Wreck:
					NewObject = m_Scene->CreateGameObject<CWreck1>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::Tent:
					if (NewInfo->FieldObjNum == 1)
						NewObject = m_Scene->CreateGameObject<CTent1>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 2)
						NewObject = m_Scene->CreateGameObject<CTent2>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::Box:
					NewObject = m_Scene->CreateGameObject<CBox1>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::Far:
					NewObject = m_Scene->CreateGameObject<CFar>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::Stone:
					if (NewInfo->FieldObjNum == 1)
						NewObject = m_Scene->CreateGameObject<CStonej1>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 2)
						NewObject = m_Scene->CreateGameObject<CStonej2>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 3)
						NewObject = m_Scene->CreateGameObject<CStonej3>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 4)
						NewObject = m_Scene->CreateGameObject<CStonej4>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 5)
						NewObject = m_Scene->CreateGameObject<CStonej5>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 6)
						NewObject = m_Scene->CreateGameObject<CStonej6>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 7)
						NewObject = m_Scene->CreateGameObject<CStonej7>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 8)
						NewObject = m_Scene->CreateGameObject<CStonej8>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 9)
						NewObject = m_Scene->CreateGameObject<CStonej9>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 10)
						NewObject = m_Scene->CreateGameObject<CStonej10>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 11)
						NewObject = m_Scene->CreateGameObject<CStonej11>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 12)
						NewObject = m_Scene->CreateGameObject<CStonej12>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 13)
						NewObject = m_Scene->CreateGameObject<CStonej13>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 14)
						NewObject = m_Scene->CreateGameObject<CStonej14>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 15)
						NewObject = m_Scene->CreateGameObject<CStonej15>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 16)
						NewObject = m_Scene->CreateGameObject<CStonej16>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 17)
						NewObject = m_Scene->CreateGameObject<CStonej17>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 18)
						NewObject = m_Scene->CreateGameObject<CStonej18>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 19)
						NewObject = m_Scene->CreateGameObject<CStonej19>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 20)
						NewObject = m_Scene->CreateGameObject<CStonej20>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 21)
						NewObject = m_Scene->CreateGameObject<CStonej21>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 22)
						NewObject = m_Scene->CreateGameObject<CStonej22>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 23)
						NewObject = m_Scene->CreateGameObject<CStonej23>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 24)
						NewObject = m_Scene->CreateGameObject<CStonej24>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 25)
						NewObject = m_Scene->CreateGameObject<CStonej25>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 26)
						NewObject = m_Scene->CreateGameObject<CStonej26>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 27)
						NewObject = m_Scene->CreateGameObject<CStonej27>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 28)
						NewObject = m_Scene->CreateGameObject<CStonej28>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 29)
						NewObject = m_Scene->CreateGameObject<CStonej29>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 30)
						NewObject = m_Scene->CreateGameObject<CStonej30>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 31)
						NewObject = m_Scene->CreateGameObject<CStonej31>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 32)
						NewObject = m_Scene->CreateGameObject<CStonej32>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 33)
						NewObject = m_Scene->CreateGameObject<CStonej33>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 34)
						NewObject = m_Scene->CreateGameObject<CStonej34>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 35)
						NewObject = m_Scene->CreateGameObject<CStonej35>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 36)
						NewObject = m_Scene->CreateGameObject<CStonej36>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 37)
						NewObject = m_Scene->CreateGameObject<CStonej37>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::TownBarrel:
					NewObject = m_Scene->CreateGameObject<CTownBarrel>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::TownCarriage:
					NewObject = m_Scene->CreateGameObject<CTownCarriage>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::TownCheckPoint:
					NewObject = m_Scene->CreateGameObject<CTownCheckPoint>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::TownDragonHead:
					NewObject = m_Scene->CreateGameObject<CTownDragonHead>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::TownPassage:
					NewObject = m_Scene->CreateGameObject<CTownPassage>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::TownPumpkinMan:
					NewObject = m_Scene->CreateGameObject<CTownPumpkinMan>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::TownRampart:
					NewObject = m_Scene->CreateGameObject<CTownRampart>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::TownShadeScreen:
					NewObject = m_Scene->CreateGameObject<CTownShadeScreen>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::TownSign:
					NewObject = m_Scene->CreateGameObject<CTownSign>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::TownStructure:
					NewObject = m_Scene->CreateGameObject<CTownStructure>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::TownSummerHouse:
					NewObject = m_Scene->CreateGameObject<CTownSummerHouse>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::TownTunnel:
					NewObject = m_Scene->CreateGameObject<CTownTunnel>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::DesertPebble:
					NewObject = m_Scene->CreateGameObject<CDesertPebble>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::DesertSmallStone:
					NewObject = m_Scene->CreateGameObject<CDesertSmallStone>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::DesertStone:
					if (NewInfo->FieldObjNum == 1)
						NewObject = m_Scene->CreateGameObject<CDesertStone1>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 2)
						NewObject = m_Scene->CreateGameObject<CDesertStone2>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 3)
						NewObject = m_Scene->CreateGameObject<CDesertStone3>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 4)
						NewObject = m_Scene->CreateGameObject<CDesertStone4>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 5)
						NewObject = m_Scene->CreateGameObject<CDesertStone5>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 6)
						NewObject = m_Scene->CreateGameObject<CDesertStone6>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::DesertBigStone:
					NewObject = m_Scene->CreateGameObject<CDesertBigStone>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::DesertRockWall:
					NewObject = m_Scene->CreateGameObject<CDesertRockWall>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::DesertStalactite:
					if (NewInfo->FieldObjNum == 1)
						NewObject = m_Scene->CreateGameObject<CDesertStalactite1>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 2)
						NewObject = m_Scene->CreateGameObject<CDesertStalactite2>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 3)
						NewObject = m_Scene->CreateGameObject<CDesertStalactite3>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 4)
						NewObject = m_Scene->CreateGameObject<CDesertStalactite4>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::DesertStalagmite:
					if (NewInfo->FieldObjNum == 1)
						NewObject = m_Scene->CreateGameObject<CDesertStalagmite1>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 2)
						NewObject = m_Scene->CreateGameObject<CDesertStalagmite2>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 3)
						NewObject = m_Scene->CreateGameObject<CDesertStalagmite3>(ObjectNameMultibyte);
					break;
				case FieldObj_Type::DesertMountain:
					if (NewInfo->FieldObjNum == 1)
						NewObject = m_Scene->CreateGameObject<CDesertMountain1>(ObjectNameMultibyte);
					else if (NewInfo->FieldObjNum == 2)
						NewObject = m_Scene->CreateGameObject<CDesertMountain2>(ObjectNameMultibyte);
					break;
				}
			}

			SAFE_DELETE_ARRAY(ObjectNameMultibyte);

			Vector3 WorldPos, WorldScale, WorldRot;

			fread(&WorldPos, sizeof(Vector3), 1, File);
			fread(&WorldScale, sizeof(Vector3), 1, File);
			fread(&WorldRot, sizeof(Vector3), 1, File);

			NewObject->SetWorldPos(WorldPos);
			NewObject->SetWorldScale(WorldScale);

			if (Type == Object_Type::LandScape)
				NewObject->Load(File);

			else
				NewObject->SetWorldRot(WorldRot);
		}

		m_vecObjectInfo.push_back(NewInfo);
	}

	fclose(File);
}
