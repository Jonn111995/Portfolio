// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class EnemyBasePointStruct
{
public:
	EnemyBasePointStruct();
	~EnemyBasePointStruct();

	/// <summary>
	/// 敵拠点の座標とIDを入れた構造体
	/// </summary>
	struct EnemyBasePoint {

		//拠点ID
		int EnemyBaseId;

		//X座標
		int XPoint;

		//Y座標
		int YPoint;

		//ワールドでのX座標
		float XPointInWorld;
		
		//ワールドでのY座標
		float YPointInWorld;

	};
};
