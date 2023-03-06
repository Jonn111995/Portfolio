// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleLevel/MapChipClass/BaseMapChipActor.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "PlayerSpawnMapChip.generated.h"

/**
 * 
 */
UCLASS()
/// <summary>
/// スポーン地点のアクタークラス
/// </summary>
class APlayerSpawnMapChip : public ABaseMapChipActor
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// スポーン地点のフェーズ
	/// </summary>
	enum SpawnMapChipPhase {

		//何もなし
		kNone,

		//キャラ選択中
		kSelecting
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	APlayerSpawnMapChip();

	/// <summary>
	/// 自身の座標から、索敵範囲の道のマテリアルを光らせる
	/// OnBeginCursorOverにバインドする
	/// </summary>
	UFUNCTION()
	void ShowRange();

	/// <summary>
	/// 光らせたマテリアルを元に戻す
	/// OnEndCursorOverにバインド
	/// </summary>
	UFUNCTION()
	void HideRange();

	/// <summary>
	/// フェーズを変更する
	/// </summary>
	/// <param name="phase"></param>
	void SetSpawnMapChipPhase(SpawnMapChipPhase phase) { NowPhase = phase; };

	/// <summary>
	/// 選択中のエフェクトを発生させる
	/// </summary>
	void EmitSelectingParticle();

	/// <summary>
	/// 選択中エフェクトを消す
	/// </summary>
	void OffSelectingParticle();

	/*UPROPERTY(EditAnyWhere)
	UParticleSystem* SelectingEffect;*/

	UPROPERTY(EditAnyWhere)
	UParticleSystemComponent* SelectingParticleComp;

private:

	/// <summary>
	/// 現在のフェーズ
	/// </summary>
	SpawnMapChipPhase NowPhase;

};
