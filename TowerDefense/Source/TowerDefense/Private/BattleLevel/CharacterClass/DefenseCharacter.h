// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleLevel/PlayerCharacter.h"
#include "DefenseCharacter.generated.h"

/**
 * 
 */
 /// <summary>
 /// ���������m�̃N���X
 /// </summary>
UCLASS()
class ADefenseCharacter : public APlayerCharacter
{
	GENERATED_BODY()

public:

	//�I�[�o�[���C�h���ď����̒��g��ς���
	virtual void SetTargetEnemy(ABaseCharacter* chara) override;

protected:

	virtual void Tick(float DeltaTime) override;

	
};
