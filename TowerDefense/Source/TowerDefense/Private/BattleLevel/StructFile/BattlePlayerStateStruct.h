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
		/// �R�X�g�̍ő�l
		/// </summary>
		float MaxSpawnCost;

		/// <summary>
		/// �������_�̍ő�HP
		/// </summary>
		int PlayerBaseHp;

	};
};
