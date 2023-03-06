// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HpBarWidget.h"
#include "Components/WidgetComponent.h"
#include "HpBarWidget.h"
#include "PlayerBase.generated.h"

UCLASS()
/// <summary>
/// 味方拠点のクラス
/// </summary>
class APlayerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerBase();

	/// <summary>
	/// 拠点HPのセッターゲッター
	/// </summary>
	/// <param name="hp"></param>
	void SetHp(int hp) { BaseHp = hp; };
	int GetHp() { return BaseHp; };

	/// <summary>
	/// 拠点があるXの座標
	/// </summary>
	/// <param name="x"></param>
	void SetXPoint(int x) { XPoint = x; };
	int GetXPoint() { return XPoint; };

	/// <summary>
	/// 拠点があるYの座標
	/// </summary>
	/// <param name="y"></param>
	void SetYPoint(int y) { YPoint = y; };
	int GetYPoint() { return YPoint; };

	/// <summary>
	/// 拠点のIDのセッターゲッター
	/// </summary>
	/// <param name="id"></param>
	void SetId(int id) { BaseId = id; };
	int GetId() { return BaseId; };
	
	/// <summary>
	/// HpBarWidgetのクラスへのポインタ
	/// </summary>
	/// <param name="HpBarclass"></param>
	void SetHpBarWidgetClass(TSubclassOf<class UHpBarWidget> HpBarclass) { HpBarWidgetClass = HpBarclass; };

	/// <summary>
	/// 使用するWIdgetの設定と、HPの更新を行う
	/// </summary>
	/// <param name="HpBarclass"></param>
	void Initialize(TSubclassOf<class UHpBarWidget> HpBarclass);

	/// <summary>
	/// ダメージを受ける処理
	/// </summary>
	/// <param name="damage"></param>
	/// <returns></returns>
	bool GetDamage(int damage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	/// <summary>
	/// 拠点のID
	/// </summary>
	int BaseId;

	/// <summary>
	/// 拠点のHP
	/// </summary>
	int BaseHp;

	/// <summary>
	/// 拠点のX座標
	/// </summary>
	int XPoint;

	/// <summary>
	/// 拠点のY座標
	/// </summary>
	int YPoint;

	/// <summary>
	/// WidgetComponentに設定する使用するWidgetクラス
	/// </summary>
	UPROPERTY()
	TSubclassOf<class UHpBarWidget> HpBarWidgetClass;

	/// <summary>
	/// アタッチするWidgetComponent
	/// </summary>
	UPROPERTY(EditAnywhere)
	UWidgetComponent* HpBarWidget;

};
