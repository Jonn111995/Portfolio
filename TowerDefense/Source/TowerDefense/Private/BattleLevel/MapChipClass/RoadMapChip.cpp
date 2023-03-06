// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/MapChipClass/RoadMapChip.h"


ARoadMapChip::ARoadMapChip() {
}

void ARoadMapChip::InitializeMapChip(){

	//マテリアルインスタンスを生成する
	MaterialInstance = GetStaticMeshComponent()->CreateAndSetMaterialInstanceDynamic(0);
}

void ARoadMapChip::ChangeMaterialColor() {

	//マテリアルの中に設定した、MapChipColorというノードの値をkRedにする
	MaterialInstance->SetVectorParameterValue(TEXT("MapChipColor"), kRed);
}

void ARoadMapChip::ResetMaterialColor() {

	//マテリアルの中に設定した、MapChipColorというノードの値をkResetにする
	MaterialInstance->SetVectorParameterValue(TEXT("MapChipColor"), kReset);

}
