// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "../../BattleLevel/Interface/BaseMapChipInterface.h"
#include "BaseMapChipActor.generated.h"

/**
 * 
 */
UCLASS()
/// <summary>
///　マップチップアクターのベースクラス
/// </summary>
class ABaseMapChipActor : public AStaticMeshActor {

	GENERATED_BODY()

public:

	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ABaseMapChipActor();

	/// <summary>
	/// 自身のX座標のセッターゲッター
	/// </summary>
	void SetXPoint(int x) { XPoint = x; };
	int GetXPoint() { return XPoint; };

	/// <summary>
	/// 自身のY座標のセッターゲッター
	/// </summary>
	void SetYPoint(int y) { YPoint = y; };
	int GetYPoint() { return YPoint; };

	/// <summary>
	/// X座標の索敵範囲のセッターゲッター
	/// </summary>
	/// <param name="x"></param>
	void SetCharacterSerchRangeX(int x) { CharacterSerchRangeX = x; };
	int GetCharacterSerchRangeX() { return CharacterSerchRangeX; };

	/// <summary>
	/// Y座標の索敵範囲のセッターゲッター
	/// </summary>
	/// <param name="x"></param>
	void SetCharacterSerchRangeY(int y) { CharacterSerchRangeY = y; };
	int GetCharacterSerchRangeY() { return CharacterSerchRangeY; };

	/// <summary>
	/// 索敵開始範囲のセッターゲッター
	/// </summary>
	/// <param name="x"></param>
	void SetSerchRangeStart(int start) { SerchRangeStart = start; };
	int GetSerchRangeStart() { return SerchRangeStart; };

	/// <summary>
	/// BaseMapChipインターフェースのセッターゲッター
	/// </summary>
	/// <param name="Interface"></param>
	void SetBaseMapChipInterface(IBaseMapChipInterface* Interface) { BaseMapChipInterface = Interface; };

protected:

	/// <summary>
	/// 自身のX座標
	/// </summary>
	int XPoint;

	/// <summary>
	/// 自身のY座標のセッターゲッター
	/// </summary>
	int YPoint;

	/// <summary>
	/// X座標の索敵範囲
	/// </summary>
	int CharacterSerchRangeX;

	/// <summary>
	/// Y座標の索敵範囲
	/// </summary>
	int CharacterSerchRangeY;

	/// <summary>
	/// 索敵開始範囲
	/// </summary>
	int SerchRangeStart;

	/// <summary>
	/// BaseMapChipInterfaceの変数
	/// </summary>
	IBaseMapChipInterface* BaseMapChipInterface;

	
	
	
};
