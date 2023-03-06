// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "HpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class UHpBarWidget : public UUserWidget{
	GENERATED_BODY()

public:

	/// <summary>
	/// 最大HPをセットする
	/// </summary>
	void SetMaxHp(float hp) { MaxHp = hp; };
	/// <summary>
	/// HPBarの表示を更新する処理
	/// BaseCharacterのダメージを受ける関数の中で呼び出す。
	/// </summary>
	/// <param name="hp"></param>
	void UpdateHpBar(float hp);

	void UpdatePhaseDisplay(const FString& PhaseName);

	void UpdateTargetNumDisplay(const int num);
	void UpdateAttackingEnemyNumDisplay(const int num);

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PhaseDisplay;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TargetNumDisplay;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttackingEnemyNumDisplay;

	void CallShowRetreatUI();

	void CallHideRetreatUI();

private:
	    
	/// <summary>
	/// 最大HPを表す
	/// </summary>
	float MaxHp;

	FText TextMessage;

	FText NowTargetNum;

	FText NowAttackingEnemyNum;

	/// <summary>
	/// WidgetBPに配置されたプログレスバーのポインタ
	/// </summary>
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HpBar;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ShowRetreatUI;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* HideRetreatUI;

};
