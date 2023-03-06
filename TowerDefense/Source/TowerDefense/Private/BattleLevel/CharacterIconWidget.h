// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "../../Private/BattleLevel/Interface/CharacterIconEventInterface.h"
#include "CharacterIconWidget.generated.h"

/**
 * 
 */
UCLASS()
/// <summary>
/// クリックされたらイベント通知を行ってスポーンさせるクラス
/// キャラが増えたら、ここにスポーンさせるキャラの情報を置く
/// </summary>
class UCharacterIconWidget : public UUserWidget{

	GENERATED_BODY()

	//デリゲート
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClickedEvent);

protected:

	void virtual NativeConstruct() override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:

	/// <summary>
	/// アイコンのフェーズ
	/// </summary>
	enum IconPhase {
	
		/// <summary>
		/// 選択中
		/// </summary>
		kSelect,

		/// <summary>
		/// 選択中ではない
		/// </summary>
		kNoneSelect
	
	};

	/// <summary>
	/// アイコンをクリックしたときに呼び出される関数。キャラをスポーンさせるリクエストを行う
	/// Buttonのクリックのイベントにバインドする
	/// </summary>
	UFUNCTION()
	void OnLaunchCharacter(); 

	/// <summary>
	/// ボタンのポインタ
	/// </summary>
	UPROPERTY(meta = (BindWidget))
	UButton* LaunchButton;

	/// <summary>
	/// アイコンの画像表示のコンポーネントのポインタ
	/// </summary>
	UPROPERTY(meta = (BindWidget))
	UImage* IconImage;

	/// <summary>
	/// インターフェースを受取る
	/// </summary>
	/// <param name="Interface"></param>
	void SetInterface(ICharacterIconEventInterface* Interface) { IconInterface = Interface; };

	/// <summary>
	/// 出撃するキャラのタイプIDのセッター
	/// </summary>
	/// <param name="id"></param>
	void SetSpawnCharaTypeId(int id) { SpawnCharaTypeId = id; };
	int GetSpawnCharaTypeId() { return SpawnCharaTypeId; };

	/// <summary>
	/// 出撃するのに必要なコストのセッター
	/// </summary>
	/// <param name="cost"></param>
	void SetNeedCost(float cost) { NeedCost = cost; };

	/// <summary>
	/// HPのセッターゲッター
	/// </summary>
	/// <param name="hp"></param>
	void SetHp(const int hp) { Hp = hp; };
	const int GetHp() { return Hp; };

	/// <summary>
	/// 攻撃力のセッターゲッター
	/// </summary>
	/// <param name="attack"></param>
	void SetAttack(const int attack) { Attack = attack; };
	const int GetAttack() { return Attack; };

	/// <summary>
	/// 防御力のセッターゲッター
	/// </summary>
	/// <param name="defense"></param>
	void SetDefense(const int defense) { Defense = defense; };
	const int GetDefense() { return Defense; };

	/// <summary>
	/// X座標の索敵範囲のセッターゲッター
	/// </summary>
	/// <param name="range"></param>
	void SetSerchXRange(const int range) { XRange = range; };
	int GetSerchXRange() { return XRange; };

	/// <summary>
	/// Y座標の索敵範囲のセッターゲッター
	/// </summary>
	/// <param name="range"></param>
	void SetSerchYRange(const int range) { YRange = range; };
	int GetSerchYRange() { return YRange; };

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
	// 止められる敵の数のセッターゲッター
	/// </summary>
	void SetStopEnemyNum(int StopNum) { StopEnemyNum = StopNum; };
	int GetStopEnemyNum() { return StopEnemyNum; };

	/// <summary>
	/// 選択中アニメーションを呼ぶ
	/// </summary>
	void CallSelectIn();

	/// <summary>
	/// 選択中アニメーションを隠す
	/// </summary>
	void CallSelectOut();

	/// <summary>
	/// スポーンしたらメッセージを出す
	/// </summary>
	/// <param name="Message"></param>
	void CallShowSpawnMessage(FString Message);

	/// <summary>
	/// アイコンのフェーズのセッターゲッター
	/// </summary>
	/// <param name="phase"></param>
	void SetIconPhase(IconPhase phase) { NowPhase = phase; };
	IconPhase GetIconPhase() { return NowPhase; };

private:

	/// <summary>
	/// アイコンの現在のフェーズ
	/// </summary>
	IconPhase NowPhase;

	/// <summary>
	/// マネージャーにイベント通知を行う為のインターフェース
	/// </summary>
	ICharacterIconEventInterface* IconInterface;

	/// <summary>
	/// 出撃するキャラのタイプID
	/// </summary>
	int SpawnCharaTypeId;

	/// <summary>
	/// 出撃するのに必要なコスト
	/// </summary>
	float NeedCost;

	//キャラのHP
	int Hp;

	//キャラの攻撃力
	int Attack;

	//キャラの防御力
	int Defense;

	//キャラのXの索敵範囲
	int XRange;

	//キャラのYの索敵範囲
	int YRange;

	//キャラの攻撃スピード
	float AttackSpan;

	//キャラの索敵開始範囲
	int StartSerchRangeNum;

	//キャラを止められる数
	int StopEnemyNum;

	/// <summary>
	/// スポーンに関わるメッセージを表示する
	/// スポーンに成功したら成功と出したり、コストが足りなかったり、スポーン地点ではないところをクリックしたら失敗した旨を表示したり。
	/// </summary>
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SpawnMessage;

	/// <summary>
	/// 選択中UIを表示させるアニメーション
	/// </summary>
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* SelectIn;

	/// <summary>
	/// 選択中UIを隠すアニメーション
	/// </summary>
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* SelectOut;

	/// <summary>
	/// スポーンに関わるメッセージを表示するアニメーション
	/// </summary>
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ShowSpawnMessage;
};

