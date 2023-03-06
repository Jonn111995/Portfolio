// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleLevel/BaseCharacter.h"
#include "../BattleLevel/Interface/PlayerCharacterEventInterface.h"
#include "PlayerCharacter.generated.h"

/**
 *
 */

UCLASS()
/// <summary>
/// プレイヤーキャラのクラス
/// </summary>
class APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:

	/// <summary>
	/// 味方キャラの種類
	/// </summary>
	enum PlayerCharaType {

		kNormal,

		kLongRange,

		kDefense

	};

	/// <summary>
	/// 味方キャラのフェーズ
	/// </summary>
	enum PlayerCharaPhase {

		kSpawn,

		kSerch,

		kBattle,

		kRetreat

	};

	APlayerCharacter();

	/// <summary>
	/// キャラクターの現在のフェーズのセッターゲッター
	/// </summary>
	/// <param name="phase"></param>
	void SetCharaPhase(PlayerCharaPhase phase) { NowCharaPhase = phase; };
	PlayerCharaPhase GetCharaPhase() { return NowCharaPhase; };

	/// <summary>
	/// 撤退モーションの再生をABPへ通知するためのゲッター
	/// </summary>
	UFUNCTION(BlueprintCallable)
	bool GetbIsRetreatAnimation() { return bIsRetreatAnimation; };
	/// <summary>
	/// 撤退モーションの通知フラグのセッター
	/// </summary>
	/// <param name="retreat"></param>
	void SetbIsRetreatAnimation(bool retreat) { bIsRetreatAnimation = retreat; };

	/// <summary>
	/// スポーンアニメーションの再生が終わったフラグのセッター
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void SetbIsFinishSpawnAnimation(bool finish) { bIsFinishSpawnAnimation = finish; };


	/// <summary>
	/// プレイヤーキャラのインターフェースのセッター
	/// </summary>
	/// <param name="Interface"></param>
	void SetPCharaEventInterface(IPlayerCharacterEventInterface* Interface) { PCharaEventInterface = Interface; };

	/// <summary>
	/// 味方キャラの種類のセッターゲッター
	/// </summary>
	/// <param name="type"></param>
	void SetPlayerCharaType(PlayerCharaType type) { CharaType = type; };
	PlayerCharaType GetPlayerCharaType() { return CharaType; };

	/// <summary>
	/// 現在攻撃を仕掛けられていて、足を止めている敵が入った配列
	/// </summary>
	/// <param name="Enemy"></param>
	void SetEnemyArrayAttackingToThisPlayer(ABaseCharacter* Enemy);

	/// <summary>
	/// 止めている敵の数を調べ、まだ止められるかどうかを確認する
	/// </summary>
	/// <returns></returns>
	bool CheckNumAttackingToThisPlayer();

	/// <summary>
	/// 止められる敵の数の上限に達しているかどうかのセッターゲッター
	/// </summary>
	/// <param name="NoMoreStop"></param>
	void SetbIsNoMoreStopEnemy(bool NoMoreStop) { bIsNoMoreStopEnemy = NoMoreStop; };
	bool GetbIsNoMoreStopEnemy() { return bIsNoMoreStopEnemy; };
	
	void SetNeedCost(float cost) { NeedCost = cost; };
	float GetNeedCost() { return NeedCost; };

	void BindFunction();

protected:


	/// <summary>
	/// プレイヤーキャラの現在のフェーズ
	/// </summary>
	PlayerCharaPhase NowCharaPhase;

	/// <summary>
	/// 撤退モーションの通知フラグ
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRetreatAnimation = false;

	/// <summary>
	/// スポーンアニメーションの通知フラグ
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsFinishSpawnAnimation = false;

	/// <summary>
	/// プレイヤーキャラのインターフェース
	/// </summary>
	IPlayerCharacterEventInterface* PCharaEventInterface;

	/// <summary>
	/// 味方キャラの種類
	/// </summary>
	PlayerCharaType CharaType;

	/// <summary>
	/// 敵を止められるかどうかのフラグ
	/// </summary>
	bool bIsNoMoreStopEnemy;

	/// <summary>
	/// 止めている敵が入った配列
	/// </summary>
	UPROPERTY()
	TArray<ABaseCharacter*> EnemyArrayAttackingToThisPlayer;

	/// <summary>
	/// 敵が味方キャラの攻撃範囲にいるかどうかを確認する関数
	/// </summary>
	/// <returns></returns>
	bool CheckEnemyPositionInRange();

	virtual void Tick(float DeltaTime) override;

	/// <summary>
	/// 出撃必要コスト
	/// </summary>
	float NeedCost;

	UFUNCTION()
	void ShowRetreatUI();

	UFUNCTION()
	void HideRetreatUI();
};
