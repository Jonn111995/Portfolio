// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PlayerBaseDataStruct
{
public:
	PlayerBaseDataStruct();
	~PlayerBaseDataStruct();

	/// <summary>
	/// 味方拠点のステータスの構造体
	/// </summary>
	struct PlayerBaseData {

		//拠点のID
		int BaseId;

		//X座標
		int XPoint;

		//Y座標
		int YPoint;

		//ワールドでのX座標
		float XPointInWorld;

		//ワールドでのY座標
		float YPointInWorld;

		//ワールドでのY座標
		float ZPointInWorld;
	};

};
