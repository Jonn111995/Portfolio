// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/HpBarWidget.h"

void UHpBarWidget::UpdateHpBar(float hp) {

	//引き数の現在のHPをHPの最大値で割る
	float HpPercent = hp / MaxHp;

	//その割合をプログレスバーでにセット
	HpBar->SetPercent(HpPercent);

}

void UHpBarWidget::UpdatePhaseDisplay(const FString& PhaseName) {

	
	/*FTextFormat TextFormat;
	TextFormat.FromString(PhaseName);
	FFormatOrderedArguments OrderArgue;
	FText text = FText::Format(TextFormat.FromString(PhaseName), OrderArgue);*/

    PhaseDisplay->SetText(FText::FromString(PhaseName));
}

void UHpBarWidget::UpdateTargetNumDisplay(const int num){

	FString NumString = FString::FromInt(num);

	TargetNumDisplay->SetText(FText::FromString(NumString));
}

void UHpBarWidget::UpdateAttackingEnemyNumDisplay(const int num){

	FString NumString = FString::FromInt(num);

	AttackingEnemyNumDisplay->SetText(FText::FromString(NumString));
}

void UHpBarWidget::CallShowRetreatUI(){

	PlayAnimation(ShowRetreatUI, 0.0f, 1);
}

void UHpBarWidget::CallHideRetreatUI(){

	PlayAnimation(HideRetreatUI, 0.0f, 1);

}
