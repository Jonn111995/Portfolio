// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <vector>
#include "BaseCharacter.h"
#include "BattleField.h"
#include "CharacterStruct.h"
#include "StructFile/EnemyWaveInfoStruct.h"
#include "StructFile/BattlePlayerStateStruct.h"
#include "StructFile/IntroductionPageInfoStruct.h"
#include "Misc/Paths.h"
#include "BattleLevelDataManager.generated.h"

UCLASS()
class ABattleLevelDataManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleLevelDataManager();

	/// <summary>
	/// 各ファイルの読み込みを行う関数を呼ぶ
	/// </summary>
	void Initialize();
	/// <summary>
	/// 配列のアイテムのポインタの削除と配列の削除を行う
	/// </summary>
	void Finalize();
	/// <summary>
	/// プレイヤーキャラデータ配列を取得する
	/// </summary>
	/// <returns></returns>
	TArray <CharacterStruct::CharaStruct> GetPlayerCharaList() { return PlayerCharacterDataList; };
	/// <summary>
	/// エネミーキャラデータ配列を取得する
	/// </summary>
	/// <returns></returns>
	TArray <CharacterStruct::CharaStruct> GetEnemyCharaList() { return EnemyCharacterDataList; };

	/// <summary>
	/// マップチップの配置情報を取得する
	/// </summary>
	/// <returns></returns>
	TArray <TArray<int>> GetFieldMapData() { return FieldMapData; };
	/// <summary>
	/// マップチップの方向情報を取得する
	/// </summary>
	/// <returns></returns>
	TArray <TArray<ABattleField::FieldDirection>> GetFieldDirectionData() { return FieldDirectionData; };

	/// <summary>
	/// 敵のWave情報を取得する
	/// </summary>
	/// <returns></returns>
	TArray <EnemyWaveInfoStruct::WaveInfo> GetWaveInfoList() { return EnemyWaveInfoData; };

	/// <summary>
	/// プレイヤーデータの情報を取得する
	/// </summary>
	/// <returns></returns>
	BattlePlayerStateStruct::PlayerStateData GetPlayerStateStructData(){ return PlayerState; };

	/// <summary>
	/// 制限時間を取得する
	/// </summary>
	/// <returns></returns>
	int GetLimitTime() { return LimitTime; };

	/// <summary>
	/// ゲーム説明UIの説明文などの情報を取得する
	/// </summary>
	/// <returns></returns>
	TArray<IntroductionPageInfoStruct::IntroductionPageInfo> GetIntroductionPageInfo() { return IntroductionPageInfoArray; };

	/// <summary>
	/// キャラクターのステータスデータをCSVから読み込む
	/// </summary>
	void ReadCharacterData();

	/// <summary>
	/// ReadMapChipDataとReadMapDirectionDataを呼ぶ
	/// </summary>
	void ReadFieldData();

	/// <summary>
	/// フィールドのマップチップの配置情報をCSVから読み込む
	/// </summary>
	void ReadMapChipData();

	/// <summary>
	/// フィールドの方向情報をCSVから読み込む
	/// </summary>
	void ReadMapDirectionData();

	/// <summary>
	/// 敵のWave情報をCSVから読み込む
	/// </summary>
	void ReadWaveInfoData();

	/// <summary>
	/// プレイヤーの情報をCSVから読み取る。コストや拠点のHP等
	/// </summary>
	void ReadPlayerStateData();
	
	/// <summary>
	/// 制限時間の情報をCSVから読み取る
	/// </summary>
	void ReadGameStateData();

	/// <summary>
	/// ゲーム開始時のイントロダクションの情報を読み込む
	/// </summary>
	void ReadIntroductionInfoFile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	/// <summary>
	/// 読み込んだプレイヤーのデータ
	/// </summary>
	TArray <CharacterStruct::CharaStruct> PlayerCharacterDataList;
	/// <summary>
	/// 読み込んだ敵のデータ
	/// </summary>
	TArray <CharacterStruct::CharaStruct> EnemyCharacterDataList;
	/// <summary>
	/// 読み込んだフィールドのデータ
	/// </summary>
	TArray <TArray<int>> FieldMapData;
	/// <summary>
	/// 読み込んだ方角のデータ
	/// </summary>
	TArray <TArray<ABattleField::FieldDirection>> FieldDirectionData;
	/// <summary>
	/// 読み込んだWave情報のデータ
	/// </summary>
	TArray <EnemyWaveInfoStruct::WaveInfo> EnemyWaveInfoData;

	/// <summary>
	/// プレイヤー自体に関わるデータ構造体
	/// </summary>
	BattlePlayerStateStruct::PlayerStateData PlayerState;

	/// <summary>
	/// ゲーム説明の情報が入った配列を入れる
	/// </summary>
	TArray<IntroductionPageInfoStruct::IntroductionPageInfo> IntroductionPageInfoArray;

	/// <summary>
	/// 読み込んだ制限時間を入れる変数
	/// </summary>
	int LimitTime;

	/// <summary>
	/// キャラデータのCSVファイルの名前
	/// </summary>
	FString CharacterListFile = "Content/CSVFiles/CharacterDataFile.csv";
	/// <summary>
	/// フィールドの方角CSVファイルの名前
	/// </summary>
	FString FieldDirectionFile = "Content/CSVFiles/FieldDirectionFile.csv";
	/// <summary>
	/// フィールドのマップチップの配置情報のCSVファイルの名前
	/// </summary>
	FString FieldMapChipFile = "Content/CSVFiles/FieldMapChipFile.csv";
	/// <summary>
	/// Wave情報を記したCSVファイルの名前
	/// </summary>
	FString EnemyWaveInfoFile = "Content/CSVFiles/EnemyWaveInfoFile.csv";

	/// <summary>
	/// プレイヤー自体のコストなどの情報を記したCSVファイル
	/// </summary>
	FString PlayerStateFile = "Content/CSVFiles/PlayerStateFile.csv";

	/// <summary>
	/// 制限時間の情報が入ったCSVファイル
	/// </summary>
	FString GameStateFile = "Content/CSVFiles/GameStateFile.csv";

	/// <summary>
	/// ゲーム説明の情報が入ったCSVファイル
	/// </summary>
	FString  IntroductionPageInfoFile = "Content/CSVFiles/IntroductionPageInfoFile.csv";

	/// <summary>
	/// どの敵を召喚するかのタイプIDの列の最初の列の番号
	/// </summary>
	const int kEnemyTypeColumnStartNum = 3;

};
