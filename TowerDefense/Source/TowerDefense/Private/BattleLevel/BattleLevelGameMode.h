// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../BattleLevel/BattleField.h"
#include "../BattleLevel/PlayerCharacterSpawner.h"
#include "../BattleLevel/EnemySpawner.h"
#include "../BattleLevel/EnemySpawnerManager.h"
#include "../BattleLevel/Interface/PlayerCharaSpawnerEventInterface.h"
#include "../BattleLevel/Interface/CharacterSpawnerEventInterface.h"
#include "../BattleLevel/Interface/CharacterIconEventInterface.h"
#include "../BattleLevel/Interface/BattlelWidgetManagerInterface.h"
#include "../BattleLevel/Interface/BattleControllerEventInterface.h"
#include "../BattleLevel/Interface/EnemyCharacterEventInterface.h"
#include "../BattleLevel/Interface/BaseCharacterEventInterface.h"
#include "../BattleLevel/Interface/EnemySpawnerEventInterface.h"
#include "../BattleLevel/Interface/ESpawnerManagerEventInterface.h"
#include "../BattleLevel/Interface/BattleGameStateEventInterface.h"
#include "../BattleLevel/Interface/PlayerCharacterEventInterface.h"
#include "../BattleLevel/StructFile/CharacterIconInfoStruct.h"
#include "../BattleLevel/Interface/BaseMapChipInterface.h"
#include "HpBarWidget.h"
#include "BattleLevelGameState.h"
#include "BattleLevelMainWidgetManager.h"
#include "BattleLevelController.h"
#include "BattlePlayerState.h"
#include "EnemyCharacter.h"
#include "BattleLevelDataManager.h"
#include "BattleLevelGameMode.generated.h"

/**
 * 
 */
UCLASS()
/// <summary>
/// バトルレベルのゲームモード。ゲームマネージャーの役割を持たせている。
/// </summary>
class ABattleLevelGameMode : public AGameModeBase, public IPlayerCharaSpawnerEventInterface, public ICharacterSpawnerEventInterface, public IBattlelWidgetManagerInterface, public IBattleControllerEventInterface, public IEnemyCharacterEventInterface, public IBaseCharacterEventInterface, public IEnemySpawnerEventInterface, public IESpawnerManagerEventInterface, public IBattleGameStateEventInterface, public IPlayerCharacterEventInterface, public IBaseMapChipInterface
{
	GENERATED_BODY()

public:

	/// <summary>
	/// ゲームモードのフェーズ
	/// </summary>
	enum GameModePhase {

		//何もなし
		kNone,

		//ゲーム説明しているフェーズ
		kIntroduction,

		//ゲーム開始前フェーズ
		kPreStart,

		//ゲーム中フェーズ
		kProcessing,

		//ゲーム終了前フェーズ
		kPreEnd,

		//ゲーム終了フェーズ
		kEnd

	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ABattleLevelGameMode();

	/// <summary>
	/// BattleFieldのポインタをセットする
	/// </summary>
	void SetBattleField(ABattleField* field);
	/// <summary>
	/// プレイヤーキャラスポナーのポインタを渡す
	/// </summary>
	/// <param name="spawner"></param>
	void SetPlayerCharaSpawner(APlayerCharacterSpawner* spawner);

	/// <summary>
	/// エネミースポナーのセッター
	/// </summary>
	/// <param name="spawner"></param>
	void SetEnemySpawner(AEnemySpawner* spawner) { EnemySpawnerPtr = spawner; };
	/// <summary>
	/// エネミースポナーマネージャーのセッター
	/// </summary>
	/// <param name="SpawnerManager"></param>
	void SetEnemySpawnerManager(AEnemySpawnerManager* SpawnerManager) { EnemySpawnerManagerPtr = SpawnerManager; };

	/// <summary>
	/// データマネージャーのセッター
	/// </summary>
	/// <param name="data_manager"></param>
	void SetDataManagerPtr(ABattleLevelDataManager* data_manager) { DataManagerPtr = data_manager; };

	/// <summary>
	/// バトルレベルからカメラのポインタを貰う
	/// </summary>
	/// <param name="camera"></param>
	void SetFieldCamera(AActor* camera);

	/// <summary>
	/// 指定したマスにキャラが配置可能かどうか確認する
	/// </summary>
	/// <param name="position"></param>
	/// <returns></returns>
	virtual bool RequestCheckCanArrange(FVector position) override;
	/// <summary>
	/// スポーンするキャラの向きを決定する
	/// </summary>
	/// <param name="chara"></param>
	virtual void RequestDecideCharaDirection(ACharacter& chara) override;

	/// <summary>
	/// バトルコントローラーのフェーズを変える
	/// </summary>
	virtual void RequestChangePlayerControllerPhase(int TypeId, float NeedCost, int x, int y, int StartRange) override;

	/// <summary>
	/// キャラをスポーンする処理を呼び出す
	/// </summary>
	/// <param name="actor">クリックしたところのアクター。位置情報を使う</param>
	/// <returns></returns>
	virtual bool RequestSpawnCharacter(AActor* actor, int TypeId, float NeedCost) override;

	/// <summary>
	/// フィールドのキャラ用のマップにスポーンしたキャラの位置をセットする
	/// </summary>
	/// <param name="chara"></param>
	virtual void RequestSetCharacterToPtrMap(ACharacter* chara) override;

	/// <summary>
	/// キャラの撤退をさせる処理を呼び出す
	/// </summary>
	/// <param name="actor"></param>
	/// <returns></returns>
	virtual bool RequestRetreatPlayerCharacter(AActor* actor) override;

	/// <summary>
	/// エネミーから呼ばれる。自身がいる周囲のマスと拠点の位置を確認する
	/// </summary>
	virtual bool RequestCheckMapInfo(AActor* actor) override;

	//フィールドのキャラマップのポインタをnullにする
	virtual void RequestCharacterPtrToNull(ACharacter* chara) override;

	/// <summary>
	/// フィールドの情報からキャラクターの敵となるポインタを探す
	/// </summary>
	/// <param name="actor"></param>
	virtual void RequestSerchEnemy(AActor* actor) override;

	/// <summary>
	/// キャラが死んだらそのキャラを削除する
	/// 今のところはここでデストロイしているが、最終的にはスポナーで削除処理を行う
	/// </summary>
	/// <param name="character"></param>
	virtual void RequestDeleteCharacter(ACharacter* character) override;

	/// <summary>
	/// ゲームモードがもつBaseCHaraInterfaceをキャラ生成時に渡す。
	/// </summary>
	/// <param name="chara"></param>
	virtual void RequestSetBaseCharaInterface(ACharacter* chara) override;

	/// <summary>
	/// エネミーキャラのインターフェースをセットする。スポナーから呼ぶ
	/// </summary>
	/// <param name="chara"></param>
	virtual void RequestSetEnemyCharaEventInterface(ACharacter* chara) override;

	/// <summary>
	/// Fieldクラスにあるキャラクターのポインタマップのポインタの位置を更新する
	/// </summary>
	/// <param name="chara">更新するキャラのポインタ</param>
	/// <param name="x">新しいX座標</param>
	/// <param name="y">新しいY座標</param>
	virtual void RequestUpdatePtr(ACharacter* chara, const int x, const int y) override;

	/// <summary>
	/// Fieldクラスにある、敵拠点の座標を検索し座標配列を返す関数を呼ぶ
	/// </summary>
	/// <returns></returns>
	virtual TArray<EnemyBasePointStruct::EnemyBasePoint> RequestGetEnemyBasePosition() override;

	/// <summary>
	/// 味方拠点のHPが0になったらアクターを削除する
	/// </summary>
	/// <param name="BaseActor"></param>
	virtual void RequestDeletePlayerBaseActor(AActor* BaseActor) override;

	/// <summary>
	/// 味方拠点に着いたかどうかを確認する
	/// </summary>
	/// <param name="chara"></param>
	/// <returns></returns>
	virtual bool RequestCheckReachPlayerBase(ACharacter* chara) override;

	/// <summary>
	/// 拠点にEnemyが着いたらダメージを拠点にあたえる処理を行う。
	/// </summary>
	/// <param name="chara"></param>
	virtual void RequestReachPlayerBaseEvent(ACharacter* chara) override;

	/// <summary>
	/// BattleLevelクラスでロードしたHpBarのWIdgetのポインタをセットする。
	/// これを味方拠点やキャラクターに渡す
	/// </summary>
	/// <param name="HpBarclass"></param>
	void SetHpBarWidgetClass(TSubclassOf<class UHpBarWidget> HpBarclass) { PlayerBaseHpBarWidgetClass = HpBarclass; };

	/// <summary>
	/// 現在の制限時間をWIdgetに渡して表示を更新する
	/// </summary>
	/// <param name="time"></param>
	virtual void RequestGiveUpdateTime(float time) override;

	/// <summary>
	/// スポナーに毎フレームの時間を渡して、スポーン処理の実行させる
	/// </summary>
	/// <param name="time"></param>
	virtual void RequestGiveTickTimetToEnemySpawnerManager(float PassedTime, float DeltaTime) override;

	/// <summary>
	/// ゲームクリアした場合の処理
	/// </summary>
	virtual void RequestGameClear() override;
	/// <summary>
	/// ゲームオーバーの場合の処理
	/// </summary>
	virtual void RequestGameOver() override;
	
	/// <summary>
	/// 味方キャラの撤退時に呼び出し、戦っていた敵キャラのフェーズを変更させる
	/// </summary>
	/// <param name="character"></param>
	virtual void FinishBattleForRetreat(ACharacter* character) override;

	/// <summary>
	/// 味方キャラのイベントインターフェースのセッターを入れる関数
	/// </summary>
	/// <param name="chara"></param>
	virtual void RequestSetPCharaEventInterface(ACharacter* chara) override;

	/// <summary>
	/// 道のマテリアルの色を変える関数を呼ぶ
	/// </summary>
	/// <param name="actor"></param>
	virtual void RequestChangeColorMaterial(AActor* actor) override;
	/// <summary>
	/// 道のマテリアルの色を元に戻す関数を呼ぶ
	/// </summary>
	/// <param name="actor"></param>
	virtual void RequestResetColorMaterial(AActor* actor) override;

	/// <summary>
	/// WidgetManagerから呼ばれ、ゲーム説明が終わったことをGameModeに通知する
	/// </summary>
	virtual void InformFInishIntroduction() override;

	/// <summary>
	/// 時間を置いてレベルを切り替えたいので、デリゲートにバインドするための関数
	/// </summary>
	void OpenNextLevel();

	void InitializeGameMode();

	bool GetbIsInitializeGameMode() { return bIsInitializeGameMode; };

protected:

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;
	
private:

	bool bIsInitializeGameMode;

	/// <summary>
	/// GameModeの現在のフェーズ
	/// </summary>
	GameModePhase NowPhase;
	
	/// <summary>
	/// HpBarWidgetのクラス
	/// </summary>
	UPROPERTY()
	TSubclassOf<class UHpBarWidget> PlayerBaseHpBarWidgetClass;

	/// <summary>
	/// カメラのポインタ
	/// </summary>
	AActor* FieldCamera;

	/// <summary>
	/// バトルフィールドのポインタ
	/// </summary>
	UPROPERTY()
	ABattleField* Field = nullptr;

	/// <summary>
	/// プレイヤーキャラスポナーのポインタ
	/// </summary>
	UPROPERTY()
	APlayerCharacterSpawner* PlayerCharaSpawnerPtr = nullptr;

	/// <summary>
	/// プレイヤーキャラスポナーのポインタ
	/// </summary>
	UPROPERTY()
	AEnemySpawner* EnemySpawnerPtr = nullptr;

	/// <summary>
	/// エネミースポナーマネージャーのポインタ
	/// </summary>
	UPROPERTY()
	AEnemySpawnerManager* EnemySpawnerManagerPtr = nullptr;

	/// <summary>
	/// バトルレベルコントローラーのポインタ
	/// </summary>
	UPROPERTY()
	ABattleLevelController* BattleLevelControllerPtr;

	/// <summary>
	/// BattlePlayerStateのポインタ
	/// </summary>
	UPROPERTY()
	ABattlePlayerState* BattlePlayerState;

	/// <summary>
	/// BattleLevelGameStateのポインタ
	/// </summary>
	UPROPERTY()
	ABattleLevelGameState* BattleGameState;
	/// <summary>
	/// バトルレベルのWidgetManagerのポインタ
	/// </summary>
	UPROPERTY()
	ABattleLevelMainWidgetManager* BattleLevelWidgetManagerPtr;

	/// <summary>
	/// DataManagerのポインタ
	/// </summary>
	UPROPERTY()
	ABattleLevelDataManager* DataManagerPtr;

	/// <summary>
	/// 生成したプレイヤーの拠点アクターのポインタ配列
	/// </summary>
	UPROPERTY()
	TArray<APlayerBase*> PlayerBaseArray;

	/// <summary>
	/// 味方キャラを表す番号
	/// </summary>
	const int kPlayerCharaSide = 0;
	/// <summary>
	/// 敵キャラを表す番号
	/// </summary>
	const int kEnemyCharaSide = 1;

	/// <summary>
	/// キャラクターのステータス情報の配列から、キャラアイコンに渡す必要のある情報を抜き出して構造体に入れ、その構造体を配列に入れる
	/// </summary>
	/// <param name="IconInfoArray">構造体を入れる配列の参照</param>
	void SetCharacterIconInfoArray(TArray<CharacterIconInfoStruct::IconInfo>& IconInfoArray);
};
