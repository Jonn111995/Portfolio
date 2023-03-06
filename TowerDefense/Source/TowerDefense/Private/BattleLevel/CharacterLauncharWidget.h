// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "CharacterIconWidget.h"
#include "CharacterLauncharWidget.generated.h"

/**
 * 
 */

UCLASS()
/// <summary>
/// キャラクターをスポーンさせるUIのクラス
/// </summary>
class UCharacterLauncharWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/// <summary>
	/// 生成するキャラクターアイコンのポインタのセッター
	/// </summary>
	void SetCharacterIcon(TArray<UCharacterIconWidget*> icon) { CharacterIcon = icon; };

	void SetCharacterStatusUIParam(float NeedCost, int Hp, int Attack, int Defense, int StopEnemyNum, float AttackSpanNum);

	void CallShowStatus();

	void CallHideStatus();

protected:
	void NativeConstruct() override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

private:

	/// <summary>
	/// 生成するキャラクターアイコンのポインタ
	/// </summary>
	TArray<UCharacterIconWidget*> CharacterIcon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CostNum;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HpNum;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttackNum;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DefenseNum;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StopEnemyNum;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttackSpanNum;

	/// <summary>
	/// アイコンを追加する為のパネルのポインタ
	/// </summary>
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* CharacterIconPanel;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ShowStatus;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* HideStatus;

	/// <summary>
	/// 一番目のキャラID
	/// </summary>
	const int kFirstCharaID = 0;
	/// <summary>
	/// 二番目のキャラID
	/// </summary>
	const int kSecondCharaID = 1;
	/// <summary>
	/// 三番目のキャラID
	/// </summary>
	const int kThirdCharaID = 2;

	/// <summary>
	/// 一番目の行
	/// </summary>
	const int kFirstRow = 0;
	/// <summary>
	/// 一番目の列
	/// </summary>
	const int kFirstColumn = 0;
	/// <summary>
	/// 二番目の列
	/// </summary>
	const int kSecondColumn = 1;
	/// <summary>
	/// 三番目の列
	/// </summary>
	const int kThirdColumn = 2;
	
};
