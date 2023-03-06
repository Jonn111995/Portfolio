// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleLevel/BaseCharacter.h"
#include "../BattleLevel/Interface/EnemyCharacterEventInterface.h"
#include "../BattleLevel/Interface/CharacterSpawnerEventInterface.h"
#include "../BattleLevel/StructFile/EnemyWaveInfoStruct.h"
#include "EnemyCharacter.generated.h"

/**
 *
 */

UCLASS()
/// <summary>
/// 敵のクラス
/// </summary>
class AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:

	/*struct DirectionDistance {

		CharacterDirection direction = ABaseCharacter::CharacterDirection::kNone;

		int Distance = 0;

		int GoToX = 0;

		int GoToY = 0;

	};*/

	//敵の行動フェーズ
	enum EnemyPhase {

		kNone,

		kCheckSrounding,

		kDecidePosition,

		kWalking,

		kBattle,

		kCheckNextPhase

	};

	enum EnemyType {

		kNormal,

		kLongRange

	};

	AEnemyCharacter();
	/// <summary>
	/// エネミーのフェーズのセッターゲッター
	/// </summary>
	/// <returns></returns>
	const EnemyPhase GetEnemyPhase() { return NowPhase; };
	void SetEnemyPhase(const EnemyPhase phase) { NowPhase = phase; };

	/// <summary>
	/// 次の行くX座標のセッターゲッター
	/// </summary>
	/// <returns></returns>
	int GetNextXPoint() { return NextXPoint; };
	void SetNextXPoint(int x) { NextXPoint = x; };

	/// <summary>
	/// 次の行くY座標のセッターゲッター
	/// </summary>
	/// <returns></returns>
	int GetNextYPoint() { return NextYPoint; };
	void SetNextYPoint(int y) { NextYPoint = y; };

	/// <summary>
	/// バトルフェーズに行くかどうかのセッターゲッター
	/// </summary>
	/// <returns></returns>
	const bool GetbIsBattle() { return bIsBattle; };
	void SetbIsBattle(bool battle) { bIsBattle = battle; };

	//const bool GetbIsReachAnimation() { return bIsReachAnimation; };
	//void SetbIsReachAnimation(bool IsReachAnima) { bIsBattle = bIsReachAnimation; };

	const EnemyType GetEnemyType() { return Type; };
	void SetEnemyType(EnemyType type) { Type = type; };

	//void SetCanGoToList(TArray<CharacterDirection> list) { CanGoToList = list; };
	//TArray<CharacterDirection> GetCanGoToList() { return CanGoToList; };

	/// <summary>
	/// エネミーインターフェイスのセッター
	/// </summary>
	/// <param name="Interface"></param>
	void SetEnemyInterface(IEnemyCharacterEventInterface* Interface) { EnemyInterface = Interface; };

	/// <summary>
	/// スポナーのインターフェイス。今はまだスポナーがないのでここで実装
	/// </summary>
	/// <param name="Interface"></param>
	//void SetCharaSpawnerInterface(ICharacterSpawnerEventInterface* Interface) { SpawnInterface = Interface; };
	/// <summary>
	/// ターゲットエネミーのセッター。オーバーライドしている
	/// </summary>
	/// <param name="chara"></param>
	virtual void SetTargetEnemy(ABaseCharacter* chara) override;

	/// <summary>
	/// ターゲットエネミーを削除する
	/// </summary>
	void DeleteTargetEnemy(ABaseCharacter* Chara);

	//UPROPERTY(EditAnyWhere)
	//UParticleSystem* ReachEffect;
	/*void AddGoToDirection(CharacterDirection direction);*/

	void SetHealCostForDefeating(float HealCost) { HealCostForDefeating = HealCost; };
	float GetHealCostForDefeating() { return HealCostForDefeating; };

	void SetWalkSpeed(float speed) { WalkSpeed = speed; };
	float GetWalkSpeed() { return WalkSpeed; };

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	float HealCostForDefeating;

private:

	/// <summary>
	/// 敵キャラが次に向かう地点のX座標
	/// </summary>
	int NextXPoint;
	/// <summary>
	/// 敵キャラが次に向かう地点のY座標
	/// </summary>
	int NextYPoint;

	/*TArray<CharacterDirection> CanGoToList;*/

	/// <summary>
	/// 目標の座標を格納する
	/// </summary>
	FVector NewPosition;

	/// <summary>
	/// 敵キャラの移動の更新時間
	/// </summary>
	float CountTime;

	/// <summary>
	/// 敵キャラの現在の行動フェーズ
	/// </summary>
	EnemyPhase NowPhase;

	/// <summary>
	/// 敵キャラの現在の位置
	/// </summary>
	UPROPERTY()
	FVector NowLocation;
	/// <summary>
	/// 敵キャラの更新された座標を格納する
	/// </summary>
	UPROPERTY()
	FVector UpDatedLocation;
	/// <summary>
	/// 更新する時間の間隔
	/// デフォルト値を設定
	/// CSVから変えられる
	/// </summary>
	float time = 0.01f;
	/// <summary>
	/// 敵の歩くスピード
	/// 一応デフォルト値で1.0を設定
	/// CSVから変えられる
	/// </summary>
	UPROPERTY(EditAnywhere)
	float WalkSpeed = 1.0f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//bool bIsReachAnimation = false;

	/// <summary>
	/// 敵キャラのイベントインターフェース
	/// </summary>
	IEnemyCharacterEventInterface* EnemyInterface;

	//TArray<DirectionDistance> DistanceList;

	//DirectionDistance DecideDirection{};

	/// <summary>
	/// 敵キャラが移動したときにフィールドのポインタを変える為のイベントインターフェース
	/// </summary>
	//ICharacterSpawnerEventInterface* SpawnInterface;

	/// <summary>
	/// バトルフェーズに移るかどうか
	/// </summary>
	bool bIsBattle;

	/// <summary>
	/// エネミーの種類
	/// </summary>
	EnemyType Type;

	/// <summary>
	/// ワールド座標を計算する
	/// </summary>
	void CaluculateTargetLocation();

	/// <summary>
	/// キャラクターのワールドの座標を更新する
	/// </summary>
	/// <param name="differ_x"></param>
	/// <param name="differ_y"></param>
	void UpdateLocation(float& differ_x, float& differ_y, float DeltaTime);

	/// <summary>
	/// Fieldクラスのキャラクターのポインタを更新する
	/// </summary>
	void UpdateMapPtr();

	/// <summary>
	/// バトルが終わった後にどのフェーズに遷移するかを決定する
	/// </summary>
	/// <param name="AbsDifferX">目標位置と現在位置との差</param>
	/// <param name="AbsDifferY">目標位置と現在位置との差</param>
	void CheckChangePhase(float& AbsDifferX, float& AbsDifferY);

	/// <summary>
	/// 敵キャラを索敵する。
	/// </summary>
	virtual void SerchEnemy();
};
