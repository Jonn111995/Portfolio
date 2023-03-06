// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMainWidgetManager.h"
#include "BattleLevelMainWidget.h"
#include "CharacterLauncharWidget.h"
#include "CharacterIconWidget.h"
#include "../BattleLevel/Interface/BattlelWidgetManagerInterface.h"
#include "../BattleLevel/Interface/CharacterIconEventInterface.h"
#include "../BattleLevel/Interface/IntroductionWidgetInterface.h"
#include "../BattleLevel/StructFile/CharacterIconInfoStruct.h"
#include "WidgetClass/IntroductionWidget.h"
#include "BattleLevelMainWidgetManager.generated.h"

/**
 * 
 */
UCLASS()
/// <summary>
/// ウィジェットの管理や生成を行う
/// </summary>
class ABattleLevelMainWidgetManager : public ABaseMainWidgetManager, public ICharacterIconEventInterface, public IIntroductionWidgetInterface
{
	GENERATED_BODY()

public:

	//Managerのフェーズ
	enum WidgetManagerPhase {

		//何もなし
		kNone,

		//指定の時間までGameStartの表示時間を管理するフェーズ
		kWaitHideGameStartMessage,

		//GameStartの表示が消えるのを監視するフェーズ
		kAfterWaitHideGameStartMessage

	};

	/// <summary>
	/// マネージャのフェーズのセッター
	/// </summary>
	/// <param name="Phase"></param>
	void SetWidgetManagerPhase(WidgetManagerPhase Phase) { NowPhase = Phase; };

	/// <summary>
	/// ゲームモードで実行し、ゲームスタート前のUI表示の管理を行う
	/// </summary>
	/// <param name="DeltaTime">Tickの毎フレーム時間</param>
	/// <returns>UIの監視が終わったかどうか</returns>
	bool PreStartWidgetProcessing(float DeltaTime);

	/// <summary>
	/// WidgetManagerの初期化を実行する関数
	/// </summary>
	void InitializeMainWidgetManager();

	/// <summary>
	/// ワールドのポインタ
	/// </summary>
	void SetWorldPtr(UWorld* world) { WorldPtr = world; };

	/// <summary>
	/// ゲームモードにキャラをスポーンさせるイベントの通知を行う
	/// </summary>
	virtual void RequestLaunchCharacter(int TypeId, float NeedCost, int x, int y, int StartRange) override;

	/// <summary>
	/// CharacterIconWIdgetから呼ばれ、キャラクターのステータスUIを表示する
	/// </summary>
	/// <param name="NeedCost"></param>
	/// <param name="Hp"></param>
	/// <param name="Attack"></param>
	/// <param name="Defense"></param>
	/// <param name="StopEnemyNum"></param>
	/// <param name="AttackSpanNum"></param>
	virtual void RequestShowCharaStatus(float NeedCost, int Hp, int Attack, int Defense, int StopEnemyNum, float AttackSpanNum) override;

	/// <summary>
	/// CharacterIconWIdgetから呼ばれ、キャラクターステータスUI表示を隠す
	/// </summary>
	virtual void RequestHideCharaStatus() override;

	/// <summary>
	/// IntroductionWidgetから呼ばれ、IntroductionWidetを閉じて、BattleLevelMainWIdgetを開く。
	/// </summary>
	virtual void RequestCloseIntroductionWidget() override;

	/// <summary>
	/// ゲームモードからインターフェースを貰う
	/// </summary>
	/// <param name="Interface"></param>
	void SetInterface(IBattlelWidgetManagerInterface* Interface) { WidgetInterface = Interface; };

	/// <summary>
	/// GameStartやGameOver,ClearのUI表示が終わったかどうかのフラグを確認する関数を呼ぶ
	/// </summary>
	/// <returns></returns>
	bool RequestGetbIsFinishShowMessage();

	/// <summary>
	/// コスト表示の値を初期化
	/// </summary>
	/// <param name="cost"></param>
	void InitializeCostDisplay(float cost);

	/// <summary>
	/// 時間表示の値を初期化
	/// </summary>
	/// <param name="time"></param>
	void InitializeTime(float time);

	/// <summary>
	/// 現在のコスト表示を更新
	/// </summary>
	/// <param name="UpdateCost"></param>
	void UpdateCost(float UpdateCost);

	/// <summary>
	/// 現在の制限時間の表示を更新
	/// </summary>
	/// <param name="time"></param>
	void RequestUpdateTime(float time);

	/// <summary>
	/// MainWidgetのGame～を表示させる
	/// </summary>
	/// <param name="message"></param>
	void RequestShowMessage(FString message);

	/// <summary>
	/// MainWidgetのGame～のメッセージを消す
	/// </summary>
	void RequestHideMessage();

	/// <summary>
	/// ゲーム終了時に呼び出す
	/// ゲームUIとリザルトメッセージを消して、タイトルとリスタートを選択出来るUIを表示する関数を呼ぶ
	/// </summary>
	void RequestShowButton();

	/// <summary>
	/// 生成するキャラアイコンに必要な情報構造体配列のセッター
	/// </summary>
	/// <param name="InfoArray"></param>
	void SetIconInfoArray(TArray<CharacterIconInfoStruct::IconInfo> InfoArray) { IconInfoArray = InfoArray; };

	/// <summary>
	/// スポーン出来たことをアイコンからメッセージを表示させる
	/// </summary>
	/// <param name="TypeID">表示するアイコンに設定されたキャラタイプID</param>
	/// <param name="message">表示するメッセージ</param>
	void RequestShowSpawnMessage(int TypeID, FString message);

	/// <summary>
	/// アイコンをクリックしたときに選択中のUIを表示させる
	/// </summary>
	/// <param name="TypeId">選択UIを表示させるアイコンのキャラタイプID</param>
	void RequestSelectIn(int TypeId);

	/// <summary>
	/// アイコンをクリックしたときに選択中のUIを消す
	/// </summary>
	/// <param name="TypeId">選択UIを消すアイコンのキャラタイプID</param>
	void RequestSelectOut(int TypeId);

	/// <summary>
	/// ゲーム説明の各ページの情報が入った構造体配列をセットする
	/// </summary>
	/// <param name="Array"></param>
	void SetIntroductionInfoArray(TArray<IntroductionPageInfoStruct::IntroductionPageInfo> Array) { IntroductionInfoArray = Array; };
	
protected:
	
	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;

private:

	const float kGameStartUIAppearTime = 1.50f;
	
	const float kResetTimeZero = 0.0f;

	/// <summary>
	/// GameStartUIの表示時間を計測する
	/// </summary>
	float CountTimeForShowingGameStartUI;

	/// <summary>
	/// Managerの現在のフェーズ
	/// </summary>
	WidgetManagerPhase NowPhase;

	/// <summary>
	/// BattleLevelMinWidgetのクラス情報
	/// </summary>
	UPROPERTY()
	TSubclassOf<UBattleLevelMainWidget> MainWidgetClass;

	/// <summary>
	/// CharacterLauncharWidgetのクラス情報
	/// </summary>
	UPROPERTY()
	TSubclassOf<UCharacterLauncharWidget> LauncharWidgetClass;

	/// <summary>
	/// CharacterIconWidgetのクラス情報
	/// </summary>
	UPROPERTY()
	TSubclassOf<UCharacterIconWidget> CharacterIconWidgetClass;

	/// <summary>
	/// IntroductionWidgetのBPクラス情報
	/// </summary>
	UPROPERTY()
	TSubclassOf<UIntroductionWidget> IntroductionWidgetClass;

	/// <summary>
	/// 生成したBattleLevelMinWidgetのポインタ
	/// </summary>
	UPROPERTY()
	UBattleLevelMainWidget* MainWidget;
	
	/// <summary>
	/// 生成したCharacterLauncharWidgetのポインタ
	/// </summary>
	UPROPERTY()
	UCharacterLauncharWidget* Launchar;

	/// <summary>
	/// 生成したCharacterIconWidgetのポインタ
	/// </summary>
	UPROPERTY()
	TArray<UCharacterIconWidget*> CharacterIcon;

	/// <summary>
	/// 生成したIntroductionWidgetのポインタ
	/// </summary>
	UPROPERTY()
	UIntroductionWidget* IntroductionWidget;

	/// <summary>
	/// ゲーム説明の各ページの情報が入った構造体の配列
	/// </summary>
	TArray<IntroductionPageInfoStruct::IntroductionPageInfo> IntroductionInfoArray;

	/// <summary>
	/// ワールドのポインタ
	/// </summary>
	UPROPERTY()
	UWorld* WorldPtr;

	/// <summary>
	/// バトルレベルゲームモードに設定されたインターフェースのポインタ
	/// </summary>
	IBattlelWidgetManagerInterface* WidgetInterface;

	/// <summary>
	/// 生成するキャラアイコンに必要な情報構造体配列
	/// </summary>
	/// <param name="InfoArray"></param>
	TArray<CharacterIconInfoStruct::IconInfo> IconInfoArray;

	/// <summary>
	/// アイコンが選択されたときに、別のアイコンが選択中ではないかを確認し、あればそのアイコンの表示とフェーズをリセットする
	/// </summary>
	void CheckAndResetIconUIAndPhase(int TypeId);

};
