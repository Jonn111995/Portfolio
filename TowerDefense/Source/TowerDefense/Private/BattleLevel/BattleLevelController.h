// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseController.h"
#include "../BattleLevel/../BattleLevel/Interface/BattleControllerEventInterface.h"
#include "BattleLevelController.generated.h"

/**
 * 
 */
UCLASS()

/// <summary>
/// バトルレベルで使うコントローラー
/// </summary>
class ABattleLevelController : public ABaseController
{
	GENERATED_BODY()

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ABattleLevelController();

	/// <summary>
	/// コントローラーのフェーズ。フェーズによって呼び出す処理を切り替える
	/// </summary>
	enum BattleLevelControllerPhase {

		//通常。キャラを押すと撤退させる
		Normal,
		//キャラを配置させるフェーズ
		Arrange,

		Wait

	};

	/// <summary>
	/// フェーズのセッター
	/// </summary>
	/// <param name="phase"></param>
	void SetPhase(BattleLevelControllerPhase phase) { NowPhase = phase; };
	/// <summary>
	/// フェーズのゲッター
	/// </summary>
	/// <returns></returns>
	BattleLevelControllerPhase GetPhase() { return NowPhase; };

	/// <summary>
	/// ゲームモードに設定されたインターフェースを受取る
	/// </summary>
	/// <param name="Interface"></param>
	void SetInterface(IBattleControllerEventInterface* Interface) { ControllerInterface = Interface; };

	/// <summary>
	/// 出撃させるキャラのタイプIDのセッター
	/// </summary>
	/// <param name="id"></param>
	void SetReservedSpawnCharaTypeId(int id) { ReservedSpawnCharaTypeId = id; };

	/// <summary>
	/// 出撃させるキャラに必要なコストのセッター
	/// </summary>
	/// <param name="cost"></param>
	void SetReservedNeedCost(float cost) { ReservedNeedCost = cost; };
	
protected:

	/// <summary>
	/// キーと関数のバインドを行う
	/// クリックを押すと各処理が呼ばれるようにしている
	/// </summary>
	void SetupInputComponent() override;

private:
	/// <summary>
	/// マップチップをクリックしたときにそのマスにキャラをスポーンさせる処理を呼び出す
	/// クリックを押すと呼び出される。バインドされている
	/// </summary>
	void OnClickMapChip();

	/// <summary>
	/// コントローラーのフェーズ
	/// </summary>
	BattleLevelControllerPhase NowPhase;

	/// <summary>
	/// ゲームモードから貰うインターフェース
	/// </summary>
	IBattleControllerEventInterface* ControllerInterface;

	/// <summary>
	/// 出撃させるキャラのタイプIDを保存
	/// </summary>
	int ReservedSpawnCharaTypeId;

	/// <summary>
	/// 出撃させるのに必要なコストを保存
	/// </summary>
	float ReservedNeedCost;
};
