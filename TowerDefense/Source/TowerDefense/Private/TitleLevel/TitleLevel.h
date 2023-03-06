// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "TitleLevelGameMode.h"
#include "TitleLevel.generated.h"

/**
 * 
 */
UCLASS()
class ATitleLevel : public ALevelScriptActor
{
	GENERATED_BODY()

protected:

	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;

private:

	/// <summary>
	/// マップを映しだすカメラのポインタ
	/// </summary>
	UPROPERTY(EditAnywhere)
	AActor* FieldCamera;

	UPROPERTY(EditAnywhere)
	AActor* FieldCamera2;

	UPROPERTY(EditAnywhere)
	AActor* FieldCamera3;

	UPROPERTY()
	ATitleLevelGameMode* TitleLevelGameModePtr;
	
};
