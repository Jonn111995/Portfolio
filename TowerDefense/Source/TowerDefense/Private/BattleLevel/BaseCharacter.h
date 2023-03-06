// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../BattleLevel/Interface/BaseCharacterEventInterface.h"
#include "Components/WidgetComponent.h"
#include "HpBarWidget.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "ProceduralMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BaseCharacter.generated.h"

UCLASS()
class ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	/// <summary>
	/// キャラクターの方向を表す
	/// </summary>
	enum CharacterDirection {

		kNone,

		kNorth,

		kSouth,

		kEast,

		kWest
	};

	//キャラクターが死んでいるかどうかを確認する
	enum CharacterStatus {

		//生きている
		kActive,
		//死んでいる
		kDead,
		//ゲーム終了時のフェーズ
		kPause,
		//なにもさせない
		kAfterDead
	};

	//キャラクターの種類を確認する
	enum CharacterSide {

		//プレイヤー
		kPlayer,

		//敵
		kEnemy

	};

	// Sets default values for this character's properties
	ABaseCharacter();

	bool bIsShowArrow = false;

	void SetbIsShowArrow(bool arrow) { bIsShowArrow = arrow; };
	bool GetbIsShowArrow() { return bIsShowArrow; };

	/// <summary>
	/// キャラのX座標をセットする
	/// </summary>
	/// <param name="x">指定するｘの値</param>
	void SetXPoint(const int x) { XPoint = x; };
	/// <summary>
	/// キャラのX座標を取得する
	/// </summary>
	/// <returns>ｘ座標</returns>
	const int GetXPoint() const { return XPoint; };

	/// <summary>
	/// キャラのＹ座標をセットする
	/// </summary>
	/// <param name="y">設定するyの座標</param>
	void SetYPoint(const int y) { YPoint = y; };
	/// <summary>
	/// キャラのＹ座標を取得
	/// </summary>
	/// <returns></returns>
	const int GetYPoint() const { return YPoint; };

	/// <summary>
	/// キャラの方向をセット
	/// </summary>
	/// <param name="direction"></param>
	void SetNowDirection(CharacterDirection direction) { NowDirection = direction; };
	/// <summary>
	/// キャラの方向を取得
	/// </summary>
	/// <returns></returns>
	CharacterDirection GetNowDirection() { return NowDirection; };

	/// <summary>
	/// キャラクターIDのセッター
	/// </summary>
	/// <param name="id"></param>
	void SetCharacterId(const int id) { CharacterId = id; };

	/// <summary>
	/// キャラクターIDのゲッター
	/// </summary>
	/// <returns></returns>
	const int GetCharacterId() { return CharacterId; };

	/// <summary>
	/// HPのセッターゲッター
	/// </summary>
	/// <param name="hp"></param>
	void SetHp(const int hp) { HP = hp; };
	const int GetHp() { return HP; };

	/// <summary>
	/// 攻撃力のセッターゲッター
	/// </summary>
	/// <param name="attack"></param>
	void SetAttack(const int attack) { AttackNum = attack; };
	const int GetAttack() { return AttackNum; };

	/// <summary>
	/// 防御力のセッターゲッター
	/// </summary>
	/// <param name="defense"></param>
	void SetDefense(const int defense) { DefenseNum = defense; };
	const int GetDefense() { return DefenseNum; };

	/// <summary>
	/// X座標の索敵範囲のセッターゲッター
	/// </summary>
	/// <param name="range"></param>
	void SetSerchXRange(const int range) { SerchXRange = range; };
	int GetSerchXRange() { return SerchXRange; };

	/// <summary>
	/// Y座標の索敵範囲のセッターゲッター
	/// </summary>
	/// <param name="range"></param>
	void SetSerchYRange(const int range) { SerchYRange = range; };
	int GetSerchYRange() { return SerchYRange; };

	/// <summary>
	/// キャラの種類のセッターゲッター
	/// </summary>
	/// <param name="side"></param>
	void SetCharacterSide(CharacterSide side) { CharaSide = side; };
	CharacterSide GetCharacterSide() { return CharaSide; };

	/// <summary>
	/// キャラの状態のセッターゲッター
	/// </summary>
	/// <param name="status"></param>
	void SetCharacterStatus(CharacterStatus status) { NowStatus = status; };
	CharacterStatus GetCharacterStatus() { return NowStatus; };

	/// <summary>
	/// ターゲットをまだ配列入れれるかどうかを確認するセッターゲッター
	/// </summary>
	/// <param name="rimit"></param>
	void SetbIsRimitTarget(const bool rimit) { bIsRimitTarget = rimit; };
	bool GetbIsRimitTarget() { return bIsRimitTarget; };


	/// <summary>
	/// ターゲットキャラのセッターゲッター
	/// </summary>
	/// <param name="chara"></param>
	virtual void SetTargetEnemy(ABaseCharacter* chara);
	virtual ABaseCharacter* GetTargetEnemy();

	/// <summary>
	/// キャラの攻撃スピードのセッターゲッター
	/// </summary>
	/// <param name="span"></param>
	void SetAttackSpan(float span) { AttackSpan = span; };
	UFUNCTION(BlueprintCallable)
	float GetAttackSpan() { return AttackSpan; };

	/// <summary>
	/// 索敵範囲の開始距離のセッターゲッター
	/// </summary>
	/// <param name="StartNum"></param>
	void SetStartSerchRangeNum(int StartNum) { StartSerchRangeNum = StartNum; };
	int GetStartSerchRangeNum() { return StartSerchRangeNum; };

	/// <summary>
	/// 攻撃をあたえる関数
	/// </summary>
	/// <returns></returns>
	bool GiveDamage();

	/// <summary>
	/// 攻撃を貰う関数
	/// </summary>
	/// <param name="damage">ダメージ数</param>
	/// <returns></returns>
	bool GetDamage(const int damage, ABaseCharacter* Target);

	/// <summary>
	/// BaseCharacterインターフェイスをセットする
	/// </summary>
	/// <param name="Interface"></param>
	void SetBaseCharaInterface(IBaseCharacterEventInterface* Interface) { BaseCharacterInterface = Interface; };

	void SetHpBarWidgetClass(TSubclassOf<class UHpBarWidget> HpBarclass) { HpBarWidgetClass = HpBarclass; };

	/// <summary>
	/// 攻撃アニメーションの再生通知フラグのセッターゲッター
	/// </summary>
	UFUNCTION(BlueprintCallable)
	bool GetbIsAttackToEnemy() { return bIsAttackToEnemy; };
	void SetbIsAttackToEnemy(bool IsAttack) { bIsAttackToEnemy = IsAttack; };

	/// <summary>
	/// 死亡アニメーションの再生通知フラグのゲッター
	/// </summary>
	UFUNCTION(BlueprintCallable)
	bool GetbIsDeadAnimation() { return bIsDeadAnimation; };

	/// <summary>
	/// スポーンアニメーションの再生通知フラグのゲッター
	/// </summary>
	UFUNCTION(BlueprintCallable)
	bool GetbIsSpawnAnimation() { return bIsSpawnAnimation; };

	/// <summary>
	// 止められる敵の数のセッターゲッター
	/// </summary>
	void SetStopEnemyNum(int StopNum) { StopEnemyNum = StopNum; };
	int GetStopEnemyNum() { return StopEnemyNum; };

	/// <summary>
	/// 現在のターゲットの数を取得
	/// </summary>
	int GetTargetEnemyNum() { return TargetEnemy.Num(); };

	/*void SetbIsStillAttacked(bool attacked) { bIsStillAttacked = attacked; };
	bool GetbIsStillAttacked() { return bIsStillAttacked; };*/

	/// <summary>
	/// 攻撃されたかどうかのセッターゲッター
	/// </summary>
	/// <returns></returns>
	const bool GetbIsAttacked() { return bIsAttacked; };
	void SetbIsAttacked(bool attacked) { bIsAttacked = attacked; };

	/// <summary>
	/// 勝利アニメーションの再生通知フラグのセッターゲッター
	/// </summary>
	void SetbIsVictoryAnimation(bool victory) { bIsVictoryAnimation = victory; };
	UFUNCTION(BlueprintCallable)
	bool GetbIsVictoryAnimation() { return bIsVictoryAnimation; };

	/// <summary>
	/// 敗北アニメーションの再生通知フラグのセッターゲッター
	/// </summary>
	void SetbIsDefeatedAnimation(bool defeated) { bIsDefeatedAnimation = defeated; };
	UFUNCTION(BlueprintCallable)
	bool GetbIsDefeatedAnimation() { return bIsDefeatedAnimation; };

	/// <summary>
	/// 死亡アニメーションの終了通知フラグのセッターゲッター
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void SetbIsFinishDeathAnimation(bool dead) { bIsFinishDeathAnimation = dead; };
	bool GetbIsFinishDeathAnimation() { return bIsFinishDeathAnimation; };

	/*UPROPERTY()
		UProceduralMeshComponent* ProcMesh;

	void CreateMesh();

	void AProcMesh();*/


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ArrowMesh;

	const float kAjustNumAttackArrowSize = 200;

	const float kTurnRate = 2.0f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	/// <summary>
	/// キャラのＸ座標
	/// </summary>
	int XPoint;
	/// <summary>
	/// キャラのY座標
	/// </summary>
	int YPoint;

	/// <summary>
	/// キャラクターID
	/// </summary>
	int CharacterId;

	/// <summary>
	/// キャラの現在の方向
	/// </summary>
	CharacterDirection NowDirection;

	/// <summary>
	/// キャラクターのHP
	/// </summary>
	int HP;

	/// <summary>
	/// キャラクターの攻撃力
	/// </summary>
	int AttackNum;

	/// <summary>
	/// キャラの防御力
	/// </summary>
	int DefenseNum;

	/// <summary>
	/// X座標の索敵範囲
	/// </summary>
	int SerchXRange;

	/// <summary>
	/// Y座標の索敵範囲
	/// </summary>
	int SerchYRange;

	/// <summary>
	/// 攻撃処理を呼ぶ間隔の時間
	/// </summary>
	float AttackSpan;

	/// <summary>
	/// 攻撃処理を呼び出す更新頻度
	/// </summary>
	float CountTimeForAttack;

	/// <summary>
	/// 索敵開始距離
	/// </summary>
	int StartSerchRangeNum;

	/// <summary>
	/// 止められる敵の数
	/// </summary>
	int StopEnemyNum;

	/// <summary>
	/// キャラクターのステータスの状態。生きているか死んでいるか
	/// </summary>
	CharacterStatus NowStatus;

	/// <summary>
	/// 攻撃する敵キャラのポインタ
	/// </summary>
	UPROPERTY()
	TArray<ABaseCharacter*> TargetEnemy;

	/// <summary>
	/// 配列にターゲットをまだ入れれるかどうか
	/// </summary>
	bool bIsRimitTarget;

	/// <summary>
	/// 攻撃されたかどうか
	/// </summary>
	bool bIsAttacked;

	//bool bIsStillAttacked;

	/// <summary>
	/// ターゲットエネミー配列の先頭の敵を指定する定数
	/// </summary>
	const int kFirstAttackEnemyIndex = 0;

	/// <summary>
	/// 攻撃アニメーションの再生通知フラグ
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAttackToEnemy = false;

	/// <summary>
	/// 死亡アニメーションの再生通知フラグ
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDeadAnimation = false;

	/// <summary>
	/// スポーンアニメーションの再生通知フラグ
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSpawnAnimation = false;

	/// <summary>
	/// 勝利アニメーションの再生通知フラグ
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsVictoryAnimation = false;

	/// <summary>
	/// 敗北アニメーションの再生通知フラグ
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDefeatedAnimation = false;

	/// <summary>
	/// 死亡アニメーションの終了通知通知フラグ
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsFinishDeathAnimation;

	/// <summary>
	/// キャラがプレイヤーか敵かを判別する変数
	/// </summary>
	CharacterSide CharaSide;

	/// <summary>
	/// BaseCharacterのインターフェイス
	/// </summary>
	IBaseCharacterEventInterface* BaseCharacterInterface;

	/// <summary>
	/// キャラクターにアタッチされたWidgetComponentで使用するWidgetのBPClass
	/// </summary>
	UPROPERTY()
	TSubclassOf<class UHpBarWidget> HpBarWidgetClass;

	/// <summary>
	/// キャラクターにアタッチするWIdgetComponent
	/// </summary>
	UPROPERTY(EditAnywhere)
	UWidgetComponent* HpBarWidget;

	/// <summary>
	/// ヒットエフェクトのポインタ
	/// エディタでセットする
	/// </summary>
	UPROPERTY(EditAnyWhere)
	UParticleSystem* HitEffect;

	/// <summary>
	/// Nigaraシステムをセットする。
	/// </summary>
	UPROPERTY(EditAnywhere, Category = "Firing")
	UNiagaraSystem* FireEffectMuzzle;

	/// <summary>
	/// 生成したNiagara Componentを入れる変数
	/// </summary>
	UNiagaraComponent* NiagaraComp;

	USceneComponent* NiagaraAttachedComp;

	UHpBarWidget* HpWidget;
};
