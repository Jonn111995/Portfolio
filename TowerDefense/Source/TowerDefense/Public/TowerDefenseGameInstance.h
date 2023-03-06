// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TowerDefenseGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTowerDefenseGameInstance : public UGameInstance{

	GENERATED_BODY()
	
public:
	/// <summary>
	/// 道のクラスパスを取得
	/// </summary>
	const FString& GetRoadChipPath();
	/// <summary>
	/// 味方キャラを置くことが出来るマスのクラスパスを取得
	/// </summary>
	const FString& GetCharacterSetPositionChipPath();
	/// <summary>
	/// 壁(なにも置けないマス)のクラスパスを取得
	/// </summary>
	const FString& GetWallChipPath();
	/// <summary>
	/// 自軍の拠点のクラスパスを取得
	/// </summary>
	const FString& GetDefenseBaseChipPath();
	/// <summary>
	/// 敵の拠点のクラスパスを取得
	/// </summary>
	const FString& GetEnemyBaseChipPath();

	/// <summary>
	/// プレイヤーキャラのクラスパスを取得
	/// </summary>
	/// <returns></returns>
	const FString& GetPlayerCharacterPath();

	/// <summary>
	/// エネミーキャラのクラスパスを取得
	/// </summary>
	/// <returns></returns>
	const FString& GetEnemyCharacterPath();

	/// <summary>
	/// BattleLevelHUD(MainWidget)のクラスパスを取得
	/// </summary>
	/// <returns></returns>
	const FString& GetBattleLevelHUDPath();

	/// <summary>
	/// CharacterIconのクラスパスを取得
	/// </summary>
	/// <returns></returns>
	const FString& GetCharacterIconPath();

	const FString& GetCharacterLauncharPath() { return CharacterLauncharPath; };

	/// <summary>
	/// IntroductionWidgetのクラスパスを取得
	/// </summary>
	/// <returns></returns>
	const FString& GetIntroductionWidgetPath() { return IntroductionWidgetPath; };

	const FString& GetLongRangeEnemyPath() { return LongRangeEnemyPath; };

	const FString& GetHpBarWidgetPath() { return HpBarWidgetPath; };

	const FString& GetLongRangePlayerCharaPath() { return LongRangePlayerCharaPath; };

	const FString& GetDefensePlayerCharaPath() { return DefensePlayerCharaPath; };

	const FString& GetPlayerBaseHpBarWidgetPath() { return PlayerBaseHpBarWidgetPath; };

	//=======================================================================
	//TitleLevelで使うWidgetなどのBPパスのゲッター
	//=======================================================================

	const FString& GetTitleLevelMainWidgetPath() { return TitleLevelMainWidgetPath; };
	/*const FString& GetTitleLevelCreditWidgetPath() { return TitleLevelCreditWidgetPath; };
	const FString& GetTitleLevelCreditScrollBoxWidgetPath() { return TitleLevelCreditScrollBoxWidgetPath; };
	const FString& GetTitleLevelCreditTextBoxWidgetPath() { return TitleLevelCreditTextBoxWidgetPath; };*/

	void InitializeGameInstance();

	bool GetbIsStartGameInstance() { return bIsStartGameInstance; };
	
protected:

	//この中で、ゲーム設定情報からパスを読み取って、パスを保持する処理を行う
	void virtual OnStart() override;

private:

	/// <summary>
	/// パッケージした際
	/// </summary>
	bool bIsStartGameInstance;

	/// <summary>
	/// 道のクラスパス
	/// </summary>
	UPROPERTY()
	FString RoadChipPath;

	/// <summary>
	/// 味方キャラを置くことが出来るマスのクラスパス
	/// </summary>
	UPROPERTY()
	FString CharacterSetPositionChipPath;

	/// <summary>
	/// 壁(なにも置けないマス)のクラスパス
	/// </summary>
	UPROPERTY()
	FString WallChipPath;

	/// <summary>
	/// 自軍の拠点のクラスパス
	/// </summary>
	UPROPERTY()
	FString DefenseBaseChipPath;

	/// <summary>
	/// 敵の拠点のクラスパス
	/// </summary>
	UPROPERTY()
	FString EnemyBaseChipPath;

	/// <summary>
	/// プレイヤーキャラのクラスパス
	/// </summary>
	UPROPERTY()
	FString PlayerCharacterPath;

	/// <summary>
	/// エネミーキャラのクラスパス
	/// </summary>
	UPROPERTY()
	FString EnemyCharacterPath;

	/// <summary>
	/// BattleLevelHUD(MainWidget)のクラスパス
	/// </summary>
	UPROPERTY()
	FString BattleLevelHUDPath;

	/// <summary>
	/// CharacterIconのクラスパス
	/// </summary>
	UPROPERTY()
	FString CharacterIconPath;

	/// <summary>
	/// CharacterLauncharのクラスパス
	/// </summary>
	UPROPERTY()
	FString CharacterLauncharPath;

	UPROPERTY()
	FString HpBarWidgetPath;

	UPROPERTY()
	FString LongRangePlayerCharaPath;

	UPROPERTY()
	FString DefensePlayerCharaPath;

	UPROPERTY()
	FString LongRangeEnemyPath;

	UPROPERTY()
	FString IntroductionWidgetPath;

	UPROPERTY()
	FString TitleLevelMainWidgetPath;

	/*UPROPERTY()
	FString TitleLevelCreditWidgetPath;

	UPROPERTY()
	FString TitleLevelCreditScrollBoxWidgetPath;

	UPROPERTY()
	FString TitleLevelCreditTextBoxWidgetPath;*/

	UPROPERTY()
	FString PlayerBaseHpBarWidgetPath;
};
