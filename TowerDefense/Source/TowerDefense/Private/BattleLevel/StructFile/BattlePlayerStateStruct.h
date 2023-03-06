// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class BattlePlayerStateStruct{

public:
	BattlePlayerStateStruct();
	~BattlePlayerStateStruct();

	struct PlayerStateData {

		/// <summary>
		/// コストの最大値
		/// </summary>
		float MaxSpawnCost;

		/// <summary>
		/// 味方拠点の最大HP
		/// </summary>
		int PlayerBaseHp;

	};
};
