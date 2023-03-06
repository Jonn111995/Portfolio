// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/CharacterLauncharWidget.h"


void UCharacterLauncharWidget::NativeConstruct() {

	Super::NativeConstruct();
	CharacterIconPanel->AddChildToUniformGrid(CharacterIcon[kFirstCharaID], kFirstRow, kFirstColumn);
	CharacterIconPanel->AddChildToUniformGrid(CharacterIcon[kSecondCharaID], kFirstRow, kSecondColumn);
	CharacterIconPanel->AddChildToUniformGrid(CharacterIcon[kThirdCharaID], kFirstRow, kThirdColumn);
}

void UCharacterLauncharWidget::SetCharacterStatusUIParam(float NeedCost, int Hp, int Attack, int Defense, int StopEnemy, float AttackSpan){

	FText NeedCostText = FText::FromString(FString::SanitizeFloat(NeedCost));
	FText HpText = FText::FromString(FString::FromInt(Hp));
	FText AttackText = FText::FromString(FString::FromInt(Attack));
	FText DefenseText = FText::FromString(FString::FromInt(Defense));
	FText StopEnemyNumText = FText::FromString(FString::FromInt(StopEnemy));
	FText AttackSpanNumText = FText::FromString(FString::SanitizeFloat(AttackSpan));

	CostNum->SetText(NeedCostText);
	HpNum->SetText(HpText);
	AttackNum->SetText(AttackText);
	DefenseNum->SetText(DefenseText);
	StopEnemyNum->SetText(StopEnemyNumText);
	AttackSpanNum->SetText(AttackSpanNumText);

}

void UCharacterLauncharWidget::CallShowStatus(){

	PlayAnimation(ShowStatus, 0.0f, 1);
}

void UCharacterLauncharWidget::CallHideStatus(){

	PlayAnimation(HideStatus, -0.01f, 1);

}

void UCharacterLauncharWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent){

	CallHideStatus();
}
