// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WidgetManagerEventInterface.h"
#include "BaseController.generated.h"

/**
 * 
 */
UCLASS()
class ABaseController : public APlayerController
{
	GENERATED_BODY()

public:

	/// <summary>
	/// ウィジェットを開かせるイベント通知を行う
	/// </summary>
	virtual void RequestOpenWidget();
	/// <summary>
	/// ウィジェットを閉じさせるイベント通知を行う
	/// </summary>
	virtual void RequestCloseWidget();

	/// <summary>
	/// BaseクラスのWIdgetManagerにイベント通知を行うので、インターフェースを貰う
	/// </summary>
	void SetWidgetManagerEventInterface(IWidgetManagerEventInterface* interface);

private:

	/// <summary>
	/// WidgetManagerからもらうインターフェース
	/// </summary>
	IWidgetManagerEventInterface* WIdgetManagerInterfacePtr;
	
};
