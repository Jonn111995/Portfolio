// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseController.h"
#include "Interface/TitleLevelControllerInterface.h"
#include "TitleLevelController.generated.h"

/**
 * 
 */
UCLASS()
class ATitleLevelController : public ABaseController
{
	GENERATED_BODY()
	
public: 

	void SetTitleLevelControllerInterface(ITitleLevelControllerInterface* Interface) { TitleLevelControllerInterface = Interface; };


protected:

	//キーと関数をバインド
	virtual void SetupInputComponent() override;

private:

	void MouseUp();

	void MouseDown();

	ITitleLevelControllerInterface* TitleLevelControllerInterface;
};
