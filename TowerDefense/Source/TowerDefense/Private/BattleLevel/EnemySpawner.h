// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyCharacter.h"
#include "CharacterStruct.h"
#include "../BattleLevel/Interface/BaseCharacterEventInterface.h"
#include "../BattleLevel/Interface/EnemyCharacterEventInterface.h"
#include "../BattleLevel/Interface/CharacterSpawnerEventInterface.h"
#include "../BattleLevel/Interface/EnemySpawnerEventInterface.h"
#include "Animation/SkeletalMeshActor.h"
#include "EnemySpawner.generated.h"

UCLASS()
/// <summary>
/// 敵のスポナー
/// </summary>
class AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	AEnemySpawner();

	/// <summary>
	/// プレイヤーキャラをスポーンさせる
	/// </summary>
	void SpawnEnemyCharacter(int TypeId, FVector position);

	/// <summary>
	/// Enemyキャラのインターフェースをセットする。BattleLevelGameModeに実装されている
	/// </summary>
	/// <param name="spawner_interface"></param>
	void SetEnemySpawnerInterface(IEnemySpawnerEventInterface* Interface) { EnemySpawnerInterface = Interface; };

	/// <summary>
	/// エネミーとプレイヤーのスポナー両方で使うことになる処理をまとめたインターフェース
	/// </summary>
	/// <param name="Cspawner_interface"></param>
	void SetCharacterSpawnerInterface(ICharacterSpawnerEventInterface* Interface) { CSpawnerInterface = Interface; };

	/// <summary>
	/// ワールドのポインタをセットする
	/// </summary>
	/// <param name="world"></param>
	void SetWorldPtr(UWorld* world) { WorldPtr = world; };

	/// <summary>
	/// エネミーキャラクラスの情報をセット
	/// </summary>
	/// <param name="CharaClass"></param>
	void SetEnemyCharacterClass(TSubclassOf<class ACharacter> CharaClass) { EnemyCharacterClass = CharaClass; };

	void SetLongRangeEnemyCharacterClass(TSubclassOf<class ACharacter> CharaClass) { LongRangeEnemyClass = CharaClass; };

	/// <summary>
	/// フィールドの敵キャラクターを削除する
	/// 現状は撤退時にこの関数を呼んでいる
	/// </summary>
	/// <param name="chara"></param>
	void DeleteEnemyCharacter(AEnemyCharacter* chara);

	/// <summary>
	/// DataManagerから敵のデータを受取る
	/// </summary>
	/// <param name="StructArray"></param>
	void SetEnemyStatusDataList(TArray<CharacterStruct::CharaStruct> StructArray) { EnemyStatusDataList = StructArray; };

	/// <summary>
	/// キャラクターのステータスを設定する
	/// </summary>
	/// <param name="BaseChara"></param>
	void SetEnemyCharaStatus(AEnemyCharacter* BaseChara);

	void SetHpBarWidgetClass(TSubclassOf<class UHpBarWidget> HpBarclass) { HpBarWidgetClass = HpBarclass; };

	void DeleteDeadPlayerCharaInTargetEnemy(ABaseCharacter* chara);

	void StopEnemyCharacter(bool clear);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	/// <summary>
	/// EnemySpawnerクラスのインターフェースのポインタ
	/// </summary>
	IEnemySpawnerEventInterface* EnemySpawnerInterface;
	/// <summary>
	/// スポナーで共通して使う処理をまとめたインターフェース
	/// </summary>
	ICharacterSpawnerEventInterface* CSpawnerInterface;

	/// <summary>
	/// エネミーーキャラクラスの変数
	/// </summary>
	UPROPERTY()
	TSubclassOf<class ACharacter> EnemyCharacterClass;

	UPROPERTY()
	TSubclassOf<class ACharacter> LongRangeEnemyClass;

	/// <summary>
	/// ワールドのポインタ
	/// </summary>
	UPROPERTY()
	UWorld* WorldPtr;

	/// <summary>
	/// スポーンさせるキャラのZ座標。Zは変わらないので固定。
	/// </summary>
	const float EnemyCharaSpawnZPosition = 130.0f;

	const int MapChipSize = 100;

	/// <summary>
	/// スポーンしたキャラのポインタ配列
	/// </summary>
	UPROPERTY()
	TArray<AEnemyCharacter*> EnemyCharacterArray;

	/// <summary>
	/// DataManagerから受取るCharaStructの構造体の配列
	/// </summary>
	TArray<CharacterStruct::CharaStruct> EnemyStatusDataList;


	UPROPERTY()
	TSubclassOf<class UHpBarWidget> HpBarWidgetClass;


};
