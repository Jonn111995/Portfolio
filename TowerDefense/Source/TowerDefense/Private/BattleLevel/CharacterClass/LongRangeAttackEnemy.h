// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleLevel/EnemyCharacter.h"
#include "LongRangeAttackEnemy.generated.h"

/**
 * 
 */
 /// <summary>
 /// 遠距離タイプの敵クラス
 /// </summary>
UCLASS()
class ALongRangeAttackEnemy : public AEnemyCharacter{

	GENERATED_BODY()


protected:

	virtual void SerchEnemy() override;
};
