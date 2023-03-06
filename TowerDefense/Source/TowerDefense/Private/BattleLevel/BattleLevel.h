// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "../../Private/BattleLevel/BattleField.h"
#include "PlayerCharacterSpawner.h"
#include "EnemySpawner.h"
#include "EnemySpawnerManager.h"
#include "BattleLevelGameMode.h"
#include "Camera/CameraActor.h"
#include "BattleLevelDataManager.h"
#include "HpBarWidget.h"
#include "BattleLevel.generated.h"



/**
 * 
 */
 /// <summary>
 /// バトルレベルのクラス
 /// </summary>
UCLASS()
class ABattleLevel : public ALevelScriptActor{

	GENERATED_BODY()

protected:

	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;

private:

	
	/// <summary>
	/// RoadChipのクラスを格納する変数
	/// </summary>
	UPROPERTY()
	TSubclassOf<class AStaticMeshActor> RoadChipClass;
	
	/// <summary>
	/// WallChipのクラスを格納する変数
	/// </summary>
	UPROPERTY()
	TSubclassOf<class AStaticMeshActor> WallChipClass;

	/// <summary>
	/// CharacterSetPositionChipのクラスを格納する変数
	/// </summary>
	UPROPERTY()
	TSubclassOf<class AStaticMeshActor> CharacterSetPositionChipClass;

	/// <summary>
	/// DefenseBaseChipのクラスを格納する変数
	/// </summary>
	UPROPERTY()
	TSubclassOf<class AStaticMeshActor> DefenseBaseChipClass;

	/// <summary>
	/// EnemyBaseChipのクラスを格納する変数
	/// </summary>
	UPROPERTY()
	TSubclassOf<class AStaticMeshActor> EnemyBaseChipClass;

	/// <summary>
	/// EnemyBaseChipのクラスを格納する変数
	/// </summary>
	UPROPERTY()
	TSubclassOf<class ACharacter> PlayerCharacterClass;

	UPROPERTY()
	TSubclassOf<class ACharacter> EnemyCharacterClass;

	UPROPERTY()
	TSubclassOf<UHpBarWidget> HpBarWidgetClass;

	UPROPERTY()
	TSubclassOf<UHpBarWidget> PlayerBaseHpBarWidgetClass;

	UPROPERTY()
	TSubclassOf<class ACharacter> LongRangePlayerCharaClass;

	UPROPERTY()
	TSubclassOf<class ACharacter> DefensePlayerCharaClass;

	UPROPERTY()
	TSubclassOf<class ACharacter> LongRangeEnemyCharaClass;

	/// <summary>
	/// BattleFieldクラスのポインタ
	/// </summary>
	UPROPERTY()
	ABattleField* Field = nullptr;

	/// <summary>
	/// プレイヤーキャラスポナーのポインタ
	/// </summary>
	UPROPERTY()
	APlayerCharacterSpawner* PlayerCharaSpawner = nullptr;

	/// <summary>
	/// エネミースポナーのポインタ
	/// </summary>
	UPROPERTY()
	AEnemySpawner* EnemySpawner = nullptr;

	/// <summary>
	/// スポナーのマネージャーのポインタ
	/// </summary>
	UPROPERTY()
	AEnemySpawnerManager* EnemySpawnerManager = nullptr;

	/// <summary>
	/// BattleLevelGameModeのポインタ
	/// </summary>
	UPROPERTY()
	ABattleLevelGameMode* BattleLevelGameModePtr = nullptr;

	/// <summary>
	/// マップを映しだすカメラのポインタ
	/// </summary>
	UPROPERTY(EditAnywhere)
	AActor* FieldCamera;

	/// <summary>
	/// DataManagerのポインタ
	/// </summary>
	UPROPERTY()
	ABattleLevelDataManager* DataManager = nullptr;

};
