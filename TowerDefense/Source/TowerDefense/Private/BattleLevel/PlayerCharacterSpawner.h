// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "../BattleLevel/Interface/PlayerCharaSpawnerEventInterface.h"
#include  "../BattleLevel/Interface/CharacterSpawnerEventInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "CharacterStruct.h"
#include "PlayerCharacterSpawner.generated.h"

UCLASS()
/// <summary>
/// プレイヤーキャラをスポーンさせるクラス
/// </summary>
class APlayerCharacterSpawner : public AActor
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	APlayerCharacterSpawner();
	/// <summary>
	/// プレイヤーキャラをスポーンさせる
	/// </summary>
	bool SpawnPlayerCharacter(int TypeId ,FVector position);
	/// <summary>
	/// インターフェースをセットする。BattleLevelGameModeに実装されている
	/// </summary>
	/// <param name="spawner_interface"></param>
	void SetSpawnerInterface(IPlayerCharaSpawnerEventInterface* spawner_interface);

	void SetCharacterSpawnerInterface(ICharacterSpawnerEventInterface* Cspawner_interface);

	/// <summary>
	/// ワールドのポインタをセットする
	/// </summary>
	/// <param name="world"></param>
	void SetWorldPtr(UWorld* world);

	/// <summary>
	/// プレイヤーキャラクラスの情報をセット
	/// </summary>
	/// <param name="CharaClass"></param>
	void SetPlayerCharacterClass(TSubclassOf<class ACharacter> CharaClass);

	void SetLongRangeCharacterClass(TSubclassOf<class ACharacter> CharaClass);

	void SetDefenseCharacterClass(TSubclassOf<class ACharacter> CharaClass);

	/// <summary>
	/// フィールドの味方キャラクターを削除する
	/// 現状は撤退時にこの関数を呼んでいる
	/// </summary>
	/// <param name="chara"></param>
	void DeletePlayerCharacter(APlayerCharacter* chara);

	/// <summary>
	/// DataManagerからプレイヤーのデータを受取る
	/// </summary>
	/// <param name="StructArray"></param>
	void SetPlayerStatusDataList(TArray<CharacterStruct::CharaStruct> StructArray) { PlayerStatusDataList = StructArray; };

	/// <summary>
	/// キャラクターのステータスを設定する
	/// </summary>
	/// <param name="BaseChara"></param>
	void SetPlayerCharaStatus(APlayerCharacter* PlayerChara);

	void SetHpBarWidgetClass(TSubclassOf<class UHpBarWidget> HpBarclass) { HpBarWidgetClass = HpBarclass; };

	void StopPlayerCharacter(bool clear);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	/// <summary>
	/// インターフェースのポインタ
	/// </summary>
	IPlayerCharaSpawnerEventInterface* SpawnerInterface;

	ICharacterSpawnerEventInterface* CSpawnerInterface;

	/// <summary>
	/// プレイヤーキャラクラスの変数
	/// </summary>
	UPROPERTY()
	TSubclassOf<class ACharacter> PlayerCharacterClass;

	UPROPERTY()
	TSubclassOf<class ACharacter> LongRangeCharacterClass;

	UPROPERTY()
	TSubclassOf<class ACharacter> DefenseCharacterClass;

	/// <summary>
	/// ワールドのポインタ
	/// </summary>
	UPROPERTY()
	UWorld* WorldPtr;

	/// <summary>
	/// スポーンさせるキャラのZ座標。Zは変わらないので固定。
	/// </summary>
	const float PlayerCharaSpawnZPosition = 101.0f;

	/// <summary>
	/// スポーンしたキャラのポインタ配列
	/// </summary>
	UPROPERTY()
	TArray<APlayerCharacter*> PlayerCharacterArray;

	/// <summary>
	/// DataManagerから受取るCharaStructの構造体の配列
	/// </summary>
	TArray<CharacterStruct::CharaStruct> PlayerStatusDataList;

	UPROPERTY()
	TSubclassOf<class UHpBarWidget> HpBarWidgetClass;


};
