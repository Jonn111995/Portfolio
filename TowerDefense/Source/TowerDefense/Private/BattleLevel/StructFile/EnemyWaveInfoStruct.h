// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 * 
 */

/// <summary>
/// Wave情報を格納する構造体
/// </summary>
class EnemyWaveInfoStruct
{
public:
	EnemyWaveInfoStruct();
	~EnemyWaveInfoStruct();

	/// <summary>
	/// Wave情報
	/// スポーンさせる敵グループの情報構造体
	/// </summary>
	struct WaveInfo {

		//WaveId
		int WaveId;

		//スポーン地点のID
		int SpawnPointId;

		//スポーン開始時間
		float SpawnTime;

		//スポーンさせる敵の種類のID配列
		TArray<int> SpanwTypeIdArray;

	};
};
