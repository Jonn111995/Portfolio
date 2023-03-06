// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleLevel/MapChipClass/BaseMapChipActor.h"
#include "RoadMapChip.generated.h"

/**
 * 
 */
UCLASS()
/// <summary>
/// 道のアクタークラス
/// </summary>
class ARoadMapChip : public ABaseMapChipActor
{
	GENERATED_BODY()

public:

	//道のアクターのフェーズ
	enum RoadChipPhase {

		kNone,
		//発光フェーズ
		kEmit

	};

	//コンストラクタ
	ARoadMapChip();

	//マテリアルを取得し、マテリアルインスタンスを生成して変数に保持する
	void InitializeMapChip();
	//フェーズを変更する
	void SetRoadChipPhase(RoadChipPhase phase) { NowPhase = phase; };
	RoadChipPhase GetRoadChipPhase() { return NowPhase; };

	//マテリアルの色を変更する
	void ChangeMaterialColor();

	//マテリアルの色を戻す
	void ResetMaterialColor();
	
	const FVector kRed{ 1, 0, 0 };

	const FVector kReset{ (1, 1, 1) };

private:

	//現在のフェーズ
	RoadChipPhase NowPhase;

	//マテリアルインスタンスの変数
	UPROPERTY()
	UMaterialInstanceDynamic* MaterialInstance;



};
