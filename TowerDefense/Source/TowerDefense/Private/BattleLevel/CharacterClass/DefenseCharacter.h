// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleLevel/PlayerCharacter.h"
#include "DefenseCharacter.generated.h"

/**
 * 
 */
 /// <summary>
 /// 盾持ち兵士のクラス
 /// </summary>
UCLASS()
class ADefenseCharacter : public APlayerCharacter
{
	GENERATED_BODY()

public:

	//オーバーライドして処理の中身を変える
	virtual void SetTargetEnemy(ABaseCharacter* chara) override;

protected:

	virtual void Tick(float DeltaTime) override;

	
};
