// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/BattleLevelMainWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UBattleLevelMainWidget::NativeConstruct() {
	Super::NativeConstruct();

	//ランチャーのポインタがあれば
	if (IsValid(LauncharWidget)) {

		//ランチャーに生成されたアイコンの配列を渡す
		LauncharWidget->SetCharacterIcon(CharacterIconWidget);

		//パネルにランチャーを追加し表示する
		LauncharPanel->AddChildToCanvas(LauncharWidget);
		LauncharWidget = Cast<UCharacterLauncharWidget>(LauncharWidget);

		//リザルト時に出すボタンに関数をバインドする
		ReStartButton->OnClicked.AddDynamic(this, &UBattleLevelMainWidget::OpenBattleLevel);
		TitleButton->OnClicked.AddDynamic(this, &UBattleLevelMainWidget::OpenTitleLevel);
	}
}

void UBattleLevelMainWidget::InitializeCost(float SetMaxCost){

	// コストの最大値をセット
	SetMaxSpawnCost(SetMaxCost);

	// コストの現在値をセット
	SetSpawnCost(MaxSpawnCost);

	/// WIdgetの方に、セットした値を反映させる
	InitializeCostDisplay();
}

void UBattleLevelMainWidget::InitializeCostDisplay(){

	//最大コストを、FStringに変換。
	FString String = FString::SanitizeFloat(MaxSpawnCost);
	//最大のコスト表示にセットする。
	MaxCost->SetText(FText::FromString(String));

	//現在のコストを、Stringに変換。
	String = FString::SanitizeFloat(NowSpawnCost);

	//それを現在のコスト表示にセット。
	NowCost->SetText(FText::FromString(String));
}

void UBattleLevelMainWidget::SetCostDisplay(){

	//現在のコストを、Stringに変換。
	FString String = FString::SanitizeFloat(NowSpawnCost);

	//コストの表示を更新するときにアニメーションを再生
	PlayAnimation(ChangeCostAnimation, 0.0f, 1);

	//それを現在のコスト表示にセット。
	NowCost->SetText(FText::FromString(String));
}

void UBattleLevelMainWidget::UpdateTime(float Time) {

	//現在のコストを、Stringに変換
	FString String = FString::FromInt(Time);
	//それを現在のコスト表示にセット
	RemainTime->SetText(FText::FromString(String));
		
}

void UBattleLevelMainWidget::ShowMessage(FString message) {
    
	//テキストパネルに引き数の文字をセットする
	GameResultMessage->SetText(FText::FromString(message));
	//アニメーションを再生する
	PlayAnimation(ShowResultMessage, 0.0f, 1);
}


void UBattleLevelMainWidget::HideMessage() {

	//アニメーションを再生する
	PlayAnimation(HideResultMessage, 0.0f, 1);

}

void UBattleLevelMainWidget::ShowResultButton() {

	//アニメーションを再生する
	PlayAnimation(FadeInButton, 3.0f,1);
}

void UBattleLevelMainWidget::ShowGameUI() {

	PlayAnimation(FadeInGameUI, 0.1f, 1);
}


void UBattleLevelMainWidget::HideInGameUi() {

	PlayAnimation(FadeOutInGameUi, 0.1f, 1);	
}


void UBattleLevelMainWidget::OpenBattleLevel() {

	UGameplayStatics::OpenLevel(GetWorld(), "TowerDefenseLevel");
}

void UBattleLevelMainWidget::OpenTitleLevel() {

	UGameplayStatics::OpenLevel(GetWorld(), "TitleLevel");
}