// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/BattleLevelMainWidgetManager.h"
#include "../../Public/TowerDefenseGameInstance.h"
#include "Kismet/GamePlayStatics.h"
#include "../BattleLevel/StructFile/CharacterIconInfoStruct.h"
#include "Engine/Texture2D.h"
 
void ABattleLevelMainWidgetManager::PreInitializeComponents() {
	Super::PreInitializeComponents();

	NowPhase = kNone;
}

bool ABattleLevelMainWidgetManager::PreStartWidgetProcessing(float DeltaTime) {

	//現在のフェーズを確認
	switch (NowPhase) {

	case kWaitHideGameStartMessage:

		//毎フレーム時間をカウント時間に足していく
		CountTimeForShowingGameStartUI += DeltaTime;

		//合計時間が、UIを表示する時間を超えたら
		if (CountTimeForShowingGameStartUI >= kGameStartUIAppearTime) {

			//GameStartUIを隠す
			RequestHideMessage();

			//合計計測時間を0にする
			CountTimeForShowingGameStartUI = kResetTimeZero;

			//次のUIが隠れるのを監視するフェーズへ遷移する
			NowPhase = kAfterWaitHideGameStartMessage;
			return false;
		}
		break;

	case kAfterWaitHideGameStartMessage:

		//UIアニメーションから終了通知が来たら、
		if (RequestGetbIsFinishShowMessage()) {

			//GameUIを表示する
			MainWidget->ShowGameUI();

			//フェーズを終了させ、UI表示が終わったことをGameModeに伝える
			NowPhase = kNone;
			return true;
		}

		break;
	}

	return false;
}


//ゲームモードにコントローラーのフェーズを変えるイベント通知を行う
void ABattleLevelMainWidgetManager::RequestLaunchCharacter(int TypeId, float NeedCost, int x, int y, int StartRange) {

	//コントローラーのフェーズ変えて、引き数の値をコントローラーに保存しておく。
	//ステージのスポーン地点をクリックしたときに、この引き数の値を使ってキャラをスポーンさせたり、
	//カーソルをスポーン地点に重ねたときは索敵範囲を示している
	WidgetInterface->RequestChangePlayerControllerPhase(TypeId, NeedCost, x, y, StartRange);

	//すでに選択中のアイコンが無いかを確認。
	CheckAndResetIconUIAndPhase(TypeId);

}

void ABattleLevelMainWidgetManager::RequestShowCharaStatus(float NeedCost, int Hp, int Attack, int Defense, int StopEnemyNum, float AttackSpanNum){

	Launchar->SetCharacterStatusUIParam(NeedCost, Hp, Attack, Defense, StopEnemyNum, AttackSpanNum);

	Launchar->CallShowStatus();

}

void ABattleLevelMainWidgetManager::RequestCloseIntroductionWidget() {

	//現在開いているWidgetを閉じる
	CloseWidget();
	
	//次に開くWIdgetのポインタを渡す
	BaseMainWidgetPtr = MainWidget;

	//GameModeにゲーム説明WIdgetの表示が終わったことを知らせる
	WidgetInterface->InformFInishIntroduction();
}

void ABattleLevelMainWidgetManager::ABattleLevelMainWidgetManager::RequestHideCharaStatus(){

}

void ABattleLevelMainWidgetManager::InitializeMainWidgetManager() {

	//ゲームインスタンスを取得
	UTowerDefenseGameInstance* GameInstance = Cast<UTowerDefenseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	//取得出来ていれば
	if (IsValid(GameInstance)) {
		//LauncharのBPをロードする
		FString Path = GameInstance->GetCharacterLauncharPath();
		LauncharWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*Path)).LoadSynchronous();
		//MainWidgetのBPをロードする
		Path = GameInstance->GetBattleLevelHUDPath();
		MainWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*Path)).LoadSynchronous();
		//CharacterIconWidgetのBPをロードする
		Path = GameInstance->GetCharacterIconPath();
		CharacterIconWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*Path)).LoadSynchronous();

		//IntroductionWidgetのBPをロードする
		Path = GameInstance->GetIntroductionWidgetPath();
		IntroductionWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*Path)).LoadSynchronous();

		//MainWidgetのクラス情報があれば
		if (IsValid(MainWidgetClass)) {

			//MainWidgetを作る
			UUserWidget* Widget = CreateWidget(GetWorld(), MainWidgetClass);
			MainWidget = Cast<UBattleLevelMainWidget>(Widget);
		}

		//CharacterIconのクラス情報があれば
		if (IsValid(CharacterIconWidgetClass)) {
			//CharacterIconを作る

			//キャラアイコンの情報構造体の要素数だけ回す
			for (int i = 0; i < IconInfoArray.Num(); i++) {
				//IconWidgetを生成
				UUserWidget* Widget = CreateWidget(GetWorld(), CharacterIconWidgetClass);
				//IconWIdgetにキャスト
				UCharacterIconWidget* Icon = Cast<UCharacterIconWidget>(Widget);

				//キャストが成功していれば、
				if (IsValid(Icon)) {
					//アイコンの画像に使うテクスチャ―をロードする。
					TSoftObjectPtr<UTexture2D> IconTexture = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(*IconInfoArray[i].IconTexture));
					//生成したアイコンに出撃するキャラに必要なコストを代入
					Icon->SetNeedCost(IconInfoArray[i].NeedCost);
					//出撃させるキャラのタイプIDを代入
					Icon->SetSpawnCharaTypeId(IconInfoArray[i].TypeId);
					Icon->SetHp(IconInfoArray[i].Hp);
					Icon->SetAttack(IconInfoArray[i].Attack);
					Icon->SetDefense(IconInfoArray[i].Defense);
					Icon->SetSerchXRange(IconInfoArray[i].XRange);
					Icon->SetSerchYRange(IconInfoArray[i].YRange);
					Icon->SetAttackSpan(IconInfoArray[i].AttackSpan);
					Icon->SetStopEnemyNum(IconInfoArray[i].StopEnemyNum);
					Icon->SetStartSerchRangeNum(IconInfoArray[i].StartSerchRangeNum);

					//アイコンの画像をロードしたテクスチャ―に差し替える
					Icon->IconImage->SetBrushFromTexture(IconTexture.LoadSynchronous());

					//アイコンの配列にPushする
					CharacterIcon.Push(Icon);
				}

			}

		}
		//CharacterLauncharWidgetのクラス情報があれば
		if (IsValid(LauncharWidgetClass)) {
			//CharacterLauncharWidgetを作る
			UUserWidget* Widget = CreateWidget(GetWorld(), LauncharWidgetClass);
			Launchar = Cast<UCharacterLauncharWidget>(Widget);

		}

		if (IsValid(IntroductionWidgetClass)) {
			UUserWidget* Widget = CreateWidget(GetWorld(), IntroductionWidgetClass);
			IntroductionWidget = Cast<UIntroductionWidget>(Widget);

			IntroductionWidget->SetIIntroductionWidgetInterface(this);
			IntroductionWidget->SetIntroductionInfoArray(IntroductionInfoArray);
			IntroductionWidget->SetAnimationIntoArray();
			IntroductionWidget->SetPageContext();
		}

		//MainWidgetにLauncharのポインタを渡す
		MainWidget->SetLaunchar(Launchar);
		//MainWidgetにCharacterIconのポインタを渡す
		MainWidget->SetCharacterIcon(CharacterIcon);

		for (int i = 0;i < CharacterIcon.Num(); i++) {
			//CharacterIconに、アイコンがクリックされたときに呼び出すイベントを呼ぶインターフェースを呼ぶ
			//インターフェースはBattleLevelWidgetManagerに実装されている
			CharacterIcon[i]->SetInterface(this);
		}

		//Managerの基底クラスにMainWidgetのポインタを渡す
		//基底クラスの方で、ウィジェットの開け閉めを行っているため
		BaseMainWidgetPtr = IntroductionWidget;
	}

}


bool ABattleLevelMainWidgetManager::RequestGetbIsFinishShowMessage() {

	return MainWidget->GetbIsFinishShowMessage();
}


void ABattleLevelMainWidgetManager::BeginPlay() {
	Super::BeginPlay();
}

void ABattleLevelMainWidgetManager::InitializeCostDisplay(float cost){
	//コスト表示を初期化する。
	//PlayerStateにあるコストの最大値を代入する。
	MainWidget->InitializeCost(cost);
}

void  ABattleLevelMainWidgetManager::UpdateCost(float UpdateCost){

	//コストの現在値を更新する。
	MainWidget->SetSpawnCost(UpdateCost);

	//その後コストのHUDの表示も同じく更新する
	MainWidget->SetCostDisplay();
}

void ABattleLevelMainWidgetManager::InitializeTime(float time) {
	
	//制限時間の開始値をセットする
	MainWidget->SetLimitSeconds(time);
		
}

void ABattleLevelMainWidgetManager::RequestUpdateTime(float time) {

   //現在の時間表示を更新する
   MainWidget->UpdateTime(time);
			
}

void ABattleLevelMainWidgetManager::RequestShowMessage(FString message) {

	MainWidget->ShowMessage(message);
}

void ABattleLevelMainWidgetManager::RequestHideMessage() {

	MainWidget->HideMessage();
}


void ABattleLevelMainWidgetManager::RequestShowSpawnMessage(int TypeId, FString Message){

	for (auto& Icon : CharacterIcon) {

		if (Icon->GetSpawnCharaTypeId() == TypeId) {

			if (Icon->GetIconPhase() == UCharacterIconWidget::IconPhase::kSelect) {

				Icon->CallShowSpawnMessage(Message);
			}

		}

	}
}

void ABattleLevelMainWidgetManager::RequestSelectIn(int TypeId){

	for (auto& Icon : CharacterIcon) {

		if (Icon->GetSpawnCharaTypeId() == TypeId) {

			if (Icon->GetIconPhase() == UCharacterIconWidget::IconPhase::kSelect) {

				Icon->CallSelectIn();
				
			}

		}

	}
}

void ABattleLevelMainWidgetManager::RequestSelectOut(int TypeId){

	for (auto& Icon : CharacterIcon) {

		if (Icon->GetSpawnCharaTypeId() == TypeId) {

			if (Icon->GetIconPhase() == UCharacterIconWidget::IconPhase::kSelect) {

				Icon->CallSelectOut();
				Icon->SetIconPhase(UCharacterIconWidget::IconPhase::kNoneSelect);
			}

		}

	}
}

void ABattleLevelMainWidgetManager::RequestShowButton() {

	//ゲーム終了後に呼ばれ、タイトルに戻るか、もう一度ゲームするかの選択するボタンを表示する
	//ゲームUIを隠す
	MainWidget->HideInGameUi();

	//ゲームリザルトのメッセージを消す
	//MainWidget->HideMessage();

	//リザルトのボタンを表示する
	MainWidget->ShowResultButton();
}

void ABattleLevelMainWidgetManager::CheckAndResetIconUIAndPhase(int TypeId) {

	//アイコンの配列を回す
	for (auto& Icon : CharacterIcon) {

		//アイコンに設定された、出撃させるキャラのIDと引き数のIDが同じであれば、
		//つまり配列から見つけ出したアイコンとこの関数を呼び出したアイコンが同じアイコンではなくて、
		if (Icon->GetSpawnCharaTypeId() != TypeId) {

			//そのアイコンのフェーズが選択中であれば、
			if (Icon->GetIconPhase() == UCharacterIconWidget::IconPhase::kSelect) {

				//アイコン選択中UIを消して、
				Icon->CallSelectOut();
				//アイコンのフェーズを選択中ではないにする。
				Icon->SetIconPhase(UCharacterIconWidget::IconPhase::kNoneSelect);
			}
		}
	}
}
