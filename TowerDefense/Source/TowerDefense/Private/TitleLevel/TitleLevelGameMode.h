// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TitleLevel/TitleLevelController.h"
#include "TitleLevel/TitleLevelMainWIdget.h"
#include "TitleLevel/TitleLevelMainWIdgetManager.h"
#include "TitleLevelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ATitleLevelGameMode : public AGameModeBase
{
	GENERATED_BODY()
	

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ATitleLevelGameMode();

	/// <summary>
	/// バトルレベルからカメラのポインタを貰う
	/// </summary>
	/// <param name="camera"></param>
	void SetFieldCamera(AActor* camera, AActor* camera2, AActor* camera3) 
	{ FieldCamera = camera;
	  FieldCamera2 = camera2;
	  FieldCamera3 = camera3;
	};

protected:

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

private:

	/// <summary>
	/// カメラのポインタ
	/// </summary>
	UPROPERTY()
	AActor* FieldCamera;

	UPROPERTY(EditAnywhere)
	AActor* FieldCamera2;

	UPROPERTY(EditAnywhere)
	AActor* FieldCamera3;

	UPROPERTY()
	ATitleLevelController* TitleLevelControllerPtr;

	UPROPERTY()
	ATitleLevelMainWidgetManager* TitleLevelWidgetManagerPtr;

	float CountTime;

	float ChangeTime;

	int NextCameraIndex;

	const int kFirstIndex = 0;

	const float kResetTime = 0.0f;

	const int kLastCameraIndex = 1;

	const float kInitializeChangeTime = 2.0f;
	const float kPlusTime = 1.0f;

	UPROPERTY()
	TArray<AActor*> CameraArray;
};
