// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/CharacterIconWidget.h"


void UCharacterIconWidget::NativeConstruct() {
	Super::NativeConstruct();

	NowPhase = kNoneSelect;
	//関数をイベントにバインドする
	LaunchButton->OnClicked.AddUniqueDynamic(this, &UCharacterIconWidget::OnLaunchCharacter);
}

void UCharacterIconWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent){

	UE_LOG(LogTemp, Log, TEXT("Call::NativeOnMouseLeave"));

	IconInterface->RequestHideCharaStatus();
}

void UCharacterIconWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent){

	UE_LOG(LogTemp, Log, TEXT("Call::NativeOnMouseEnter"));

	IconInterface->RequestShowCharaStatus(NeedCost, Hp, Attack, Defense, StopEnemyNum, AttackSpan);
}

void UCharacterIconWidget::OnLaunchCharacter() {


	UE_LOG(LogTemp, Log, TEXT("Call::OnLaunchCharacter"));

	NowPhase = kSelect;

	//PlayAnimation(SelectIn, 0.0f, 1);

	//Widgetマネージャーにクリックされたことを通知する
	IconInterface->RequestLaunchCharacter(SpawnCharaTypeId, NeedCost, XRange, YRange, StartSerchRangeNum);
}

void UCharacterIconWidget::CallSelectIn(){

	PlayAnimation(SelectIn, 0.0f, 1);
}

void UCharacterIconWidget::CallSelectOut(){

	PlayAnimation(SelectOut, 0.0f, 1);

}

void UCharacterIconWidget::CallShowSpawnMessage(FString Message){

	SpawnMessage->SetText(FText::FromString(Message));
	PlayAnimation(ShowSpawnMessage, 0.0f, 1);

}
