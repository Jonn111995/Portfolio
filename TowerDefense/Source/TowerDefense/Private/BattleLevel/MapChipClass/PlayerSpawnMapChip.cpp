// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/MapChipClass/PlayerSpawnMapChip.h"

APlayerSpawnMapChip::APlayerSpawnMapChip() {

	//イベントに関数をバインドする
	FScriptDelegate Delegate;
	FScriptDelegate Delegate2;

	Delegate.BindUFunction(this, "ShowRange");
	OnBeginCursorOver.Add(Delegate);

	Delegate2.BindUFunction(this, "HideRange");
	OnEndCursorOver.Add(Delegate2);

	SelectingParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	if (SelectingParticleComp) {
		SelectingParticleComp->SetupAttachment(GetStaticMeshComponent());
		SelectingParticleComp->SecondsBeforeInactive = 1.0f;
		SelectingParticleComp->bAutoActivate = false;
	}

	//現在のフェーズを何もなしに設定
	NowPhase = kNone;
}

void APlayerSpawnMapChip::ShowRange() {

	switch (NowPhase) {

	//フェーズが選択中なら
	case kSelecting:
		//マウスカーソルが自身の上にのったら、
		UE_LOG(LogTemp, Log, TEXT("Call::ShowRange::Selecting"));
		//周囲の道のマテリアルの色を変える
		BaseMapChipInterface->RequestChangeColorMaterial(this);

		break;

	case kNone:

		//そうでなければ何もしない
		UE_LOG(LogTemp, Log, TEXT("Call::ShowRange::None"));

		break;
	}

}

void APlayerSpawnMapChip::HideRange(){

	switch (NowPhase) {

	//フェーズが選択中なら
	case kSelecting:

		UE_LOG(LogTemp, Log, TEXT("Call::HideRange::Selecting"));
		//マウスカーソルが自身の上から無くなったら、色を変えていたマテリアルの色を戻す
		BaseMapChipInterface->RequestResetColorMaterial(this);
		break;

	case kNone:

		UE_LOG(LogTemp, Log, TEXT("Call::HideRange::None"));

		break;
	}


}

void APlayerSpawnMapChip::EmitSelectingParticle(){

	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SelectingEffect, GetActorLocation(), FRotator(0,0,0), FVector(0,0,0));

	if (IsValid(SelectingParticleComp)) {
	
		SelectingParticleComp->Activate();
	
		SelectingParticleComp->SetEmitterEnable(NAME_None, true);
	}
}

void APlayerSpawnMapChip::OffSelectingParticle(){

	if (IsValid(SelectingParticleComp)) {

		SelectingParticleComp->Deactivate();

		SelectingParticleComp->SetEmitterEnable(NAME_None, false);
	}
}
