// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMainWidget.h"
#include "CharacterLauncharWidget.h"
#include "CharacterIconWidget.h"
#include "Components/SizeBox.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "BattleLevelMainWidget.generated.h"

/**
 * 
 */

UCLASS()
/// <summary>
/// バトルレベルで使うメインのウィジェット。ここに各ウィジェットを追加させて表示する
/// </summary>
class UBattleLevelMainWidget : public UBaseMainWidget
{
	GENERATED_BODY()

protected:
	
	void virtual NativeConstruct() override;
private:
	/// <summary>
	/// キャラクターロンチャーのポインタ
	/// </summary>
	UPROPERTY()
	UCharacterLauncharWidget* LauncharWidget;
	/// <summary>
	/// キャラクターアイコンウィジェットのポインタ
	/// </summary>
	UPROPERTY()
	TArray<UCharacterIconWidget*> CharacterIconWidget;

	/// <summary>
	/// 現在のコストを表示させるための変数
	/// </summary>
	float NowSpawnCost;

	/// <summary>
	/// コストの最大値
	/// </summary>
	float MaxSpawnCost;

	/// <summary>
	/// 制限時間の開始時間
	/// </summary>
	float LimitSeconds;

	/// <summary>
	/// もう一度バトルレベルをロードする
	/// </summary>
	UFUNCTION()
	void OpenBattleLevel();

	/// <summary>
	/// タイトルレベルをロードする
	/// </summary>
	UFUNCTION()
	void OpenTitleLevel();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsFinishShowMessage;

	/// <summary>
	/// ロンチャーを表示するパネルのポインタ
	/// このパネルがある位置にロンチャーを表示する
	/// </summary>
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* LauncharPanel;

	/// <summary>
	/// キャラアイコンのセッター
	/// </summary>
	/// <returns></returns>
	UCharacterLauncharWidget* GetLaunchar() { return LauncharWidget; };
	/// <summary>
	/// キャラアイコンのゲッター
	/// </summary>
	/// <returns></returns>
	TArray<UCharacterIconWidget*> GetCharacterIcon() { return CharacterIconWidget; };
	/// <summary>
	/// ロンチャーのセッター
	/// </summary>
	/// <param name="launchar"></param>
	void SetLaunchar(UCharacterLauncharWidget* launchar) { LauncharWidget = launchar; };
	/// <summary>
	/// ロンチャーのゲッター
	/// </summary>
	/// <param name="Icon"></param>
	void SetCharacterIcon(TArray<UCharacterIconWidget*> Icon) {CharacterIconWidget = Icon; };

	/// <summary>
	/// 現在のコストをセットする
	/// </summary>
	/// <param name="cost"></param>
	void SetSpawnCost(float cost) { NowSpawnCost = cost; };

	/// <summary>
	/// コストの最大値をセットする
	/// </summary>
	/// <param name="cost"></param>
	void SetMaxSpawnCost(float cost) { MaxSpawnCost = cost; };

	/// <summary>
	/// コストの最大値、現在値をセットし、Wigetのコストを表示させるテキストパネルにも値をセットする
	/// </summary>
	/// <param name="SetMaxCost"></param>
	void InitializeCost(float SetMaxCost);

	/// <summary>
	/// Widgetにコストの現在値、最大値をセット
	/// </summary>
	void InitializeCostDisplay();

	/// <summary>
	/// 現在値を、Widgetの方にも反映させる
	/// </summary>
	void SetCostDisplay();

	/// <summary>
	/// 制限時間の開始時間をセットする
	/// </summary>
	/// <param name="time"></param>
	void SetLimitSeconds(float time) { LimitSeconds = time; };

	/// <summary>
	/// 現在の制限時間を更新する
	/// </summary>
	/// <param name="Time"></param>
	void UpdateTime(float Time);

	/// <summary>
	/// リザルトメッセージを出すアニメーションを呼ぶ
	/// </summary>
	UFUNCTION()
	void ShowMessage(FString message);

	/// <summary>
	/// リザルトメッセージを隠すアニメーションを呼ぶ
	/// </summary>
	UFUNCTION()
	void HideMessage();

	/// <summary>
	/// リザルトボタンを出すアニメーションを呼ぶ
	/// </summary>
	UFUNCTION()
	void ShowResultButton();

	UFUNCTION()
	void ShowGameUI();

	/// <summary>
	/// ゲームUIを隠すアニメーションを呼ぶ
	/// </summary>
	UFUNCTION()
	void HideInGameUi();

	/// <summary>
	/// リスタートボタンのポインタ
	/// </summary>
	UPROPERTY(meta = (BindWidget))
	UButton* ReStartButton;

	/// <summary>
	/// タイトルボタンのポインタ
	/// </summary>
	UPROPERTY(meta = (BindWidget))
	UButton* TitleButton;

	/// <summary>
	/// 現在のコストを表示するTextパネル
	/// </summary>
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NowCost;

	/// <summary>
	/// 最大のコストを表示するTextパネル
	/// </summary>
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxCost;

	/// <summary>
	/// 残り時間を表示するWidgetのTextパネルのポインタ
	/// </summary>
	UPROPERTY(meta = (BindWidget))
	UTextBlock * RemainTime;

	/// <summary>
	/// リザルトメッセージを表示するテキストパネルのポインタ
	/// </summary>
	UPROPERTY(meta = (BindWidget))
	UTextBlock * GameResultMessage;
	
	/// <summary>
	/// リザルトメッセージに付けているアニメーションのポインタ
	/// </summary>
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation * ShowResultMessage;

	/// <summary>
	/// コスト表示の更新アニメーション
	/// </summary>
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ChangeCostAnimation;

	/// <summary>
	/// リザルトボタンの表示アニメーション
	/// </summary>
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeInButton;

	/// <summary>
	/// リザルトメッセージを隠す
	/// </summary>
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* HideResultMessage;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeInGameUI;

	/// <summary>
	/// ゲームUIを隠す
	/// </summary>
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeOutInGameUi;

	/// <summary>
	/// リザルトメッセージのアニメーションの終了通知が来たら、BPからこの関数を呼んでboolの設定を変える
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void SetbIsFinishShowMessage(bool finish) { bIsFinishShowMessage = finish; };
	/// <summary>
	/// リザルトメッセージが終わったかどうかのゲッター
	/// </summary>
	/// <returns></returns>
	bool GetbIsFinishShowMessage() { return bIsFinishShowMessage; };
	/*UPROPERTY(EditAnyWhere)
	UParticleSystem* ChangeCostEffect;*/

};
