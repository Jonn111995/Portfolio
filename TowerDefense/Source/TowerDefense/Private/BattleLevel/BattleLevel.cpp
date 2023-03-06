// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/BattleLevel.h"
#include "Kismet/GamePlayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Animation/SkeletalMeshActor.h"
#include "../../Public/TowerDefenseGameInstance.h"

void ABattleLevel::PreInitializeComponents() {

	Super::PreInitializeComponents();

	//ゲームンスタンスを取得する
	UTowerDefenseGameInstance* GameInstance = Cast<UTowerDefenseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//マップチップのクラスを格納する配列を宣言
	TArray <TSubclassOf<AStaticMeshActor>> ChipClassArray;

	if (IsValid(GameInstance)) {
		//ゲームインスタンスのRoadChipパスを取得する。
		FString RoadChipPath = GameInstance->GetRoadChipPath();
		//RoadChipのクラスを取得する。
		RoadChipClass = TSoftClassPtr<AStaticMeshActor>(FSoftObjectPath(*RoadChipPath)).LoadSynchronous();

		//ゲームインスタンスのWallChipパスを取得する。
		FString WallChipPath = GameInstance->GetWallChipPath();
		//WallChipPathのクラスを取得する。
		WallChipClass = TSoftClassPtr<AStaticMeshActor>(FSoftObjectPath(*WallChipPath)).LoadSynchronous();

		//ゲームインスタンスのCharacterSetPositionChipPathを取得する。
		FString CharacterSetPositionChipPath = GameInstance->GetCharacterSetPositionChipPath();
		//CharacterSetPositionChipPathのクラスを取得する。
		CharacterSetPositionChipClass = TSoftClassPtr<AStaticMeshActor>(FSoftObjectPath(*CharacterSetPositionChipPath)).LoadSynchronous();

		//ゲームインスタンスのDefenseBaseChipPathを取得する。
		FString DefenseBaseChipPath = GameInstance->GetDefenseBaseChipPath();
		//DefenseBaseChipPathクラスを取得する。
		DefenseBaseChipClass = TSoftClassPtr<AStaticMeshActor>(FSoftObjectPath(*DefenseBaseChipPath)).LoadSynchronous();

		//ゲームインスタンスのEnemyBaseChipPathを取得する。
		FString EnemyBaseChipPath = GameInstance->GetEnemyBaseChipPath();
		//EnemyBaseChipPathクラスを取得する。
		EnemyBaseChipClass = TSoftClassPtr<AStaticMeshActor>(FSoftObjectPath(*EnemyBaseChipPath)).LoadSynchronous();

		//ゲームインスタンスのPlayerCharacterPathを取得する。
		FString PlayerCharacterPath = GameInstance->GetPlayerCharacterPath();
		//PlyerCharacterPathクラスを取得する。
		PlayerCharacterClass = TSoftClassPtr<ACharacter>(FSoftObjectPath(*PlayerCharacterPath)).LoadSynchronous();

		//ゲームインスタンスのEnemyCharacterPathを取得する。
		FString EnemyCharacterPath = GameInstance->GetEnemyCharacterPath();
		//EnemyCharacterPathクラスを取得する。
		EnemyCharacterClass = TSoftClassPtr<ACharacter>(FSoftObjectPath(*EnemyCharacterPath)).LoadSynchronous();

		//ゲームインスタンスのHpBarWidgetPathを取得
		FString HpBarWidgetPath = GameInstance->GetHpBarWidgetPath();
		//HpBarWidgetのクラスを取得する
		HpBarWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*HpBarWidgetPath)).LoadSynchronous();

		//ゲームインスタンスのHpBarWidgetPathを取得
		FString PlayerBaseHpBarWidgetPath = GameInstance->GetPlayerBaseHpBarWidgetPath();
		//HpBarWidgetのクラスを取得する
		PlayerBaseHpBarWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*PlayerBaseHpBarWidgetPath)).LoadSynchronous();

		//ゲームインスタンスのLongRangePlayerCharaClassを取得
		FString LongRangePlayerCharaPath = GameInstance->GetLongRangePlayerCharaPath();
		//LongRangePlayerCharaClassのクラスを取得する
		LongRangePlayerCharaClass = TSoftClassPtr<ACharacter>(FSoftObjectPath(*LongRangePlayerCharaPath)).LoadSynchronous();

		//ゲームインスタンスのDefensePlayerCharaPathを取得
		FString DefensePlayerCharaPath = GameInstance->GetDefensePlayerCharaPath();
		//DefensePlayerCharaPathのクラスを取得する
		DefensePlayerCharaClass = TSoftClassPtr<ACharacter>(FSoftObjectPath(*DefensePlayerCharaPath)).LoadSynchronous();

		//ゲームインスタンスのLongRangeEnemyCharaClassを取得
		FString LongRangeEnemyCharaPath = GameInstance->GetLongRangeEnemyPath();
		//LongRangeEnemyCharaClassのクラスを取得する
		LongRangeEnemyCharaClass = TSoftClassPtr<ACharacter>(FSoftObjectPath(*LongRangeEnemyCharaPath)).LoadSynchronous();

		//取得したクラスを配列に入れる
		//道
		ChipClassArray.Add(RoadChipClass);
		//壁
		ChipClassArray.Add(WallChipClass);
		//味方キャラを置くマス
		ChipClassArray.Add(CharacterSetPositionChipClass);
		//味方拠点
		ChipClassArray.Add(DefenseBaseChipClass);
		//敵拠点
		ChipClassArray.Add(EnemyBaseChipClass);

		//DataManagerを生成する
		DataManager = NewObject<ABattleLevelDataManager>();
		//DataManagerの初期化処理を呼ぶ
		//ここでCSVから各種ファイルのデータを読み取る
		DataManager->Initialize();
		
		//BattleFieldを生成する
		Field = NewObject<ABattleField>();
		//マップチップ配列を渡す
		Field->SetMapChipClass(ChipClassArray);
		//現在開いているワールドのポインタを渡す
		Field->SetWorldPtr(GetWorld());
		//読み取ったフィールドのマップチップの配置情報をFieldに渡す
		Field -> SetFieldMap(DataManager->GetFieldMapData());
		//読み取ったフィールドの各マスに置いた時にどこを向かせるかの情報を渡す
		Field->SetFieldDirectionMap(DataManager->GetFieldDirectionData());
		//マップを生成する
		Field->SpawnMapChip();

		//プレイヤーキャラのスポナーを生成する
        PlayerCharaSpawner = NewObject<APlayerCharacterSpawner>();
		//スポナーにワールドのポインタを渡す
		PlayerCharaSpawner->SetWorldPtr(GetWorld());
		//スポナーに生成するキャラのクラス情報を渡す
		PlayerCharaSpawner->SetPlayerCharacterClass(PlayerCharacterClass);
		//スポナーに生成する遠距離キャラのクラス情報を渡す
		PlayerCharaSpawner->SetLongRangeCharacterClass(LongRangePlayerCharaClass);
		//スポナーに生成する複数止められるキャラのクラス情報を渡す
		PlayerCharaSpawner->SetDefenseCharacterClass(DefensePlayerCharaClass);
		//味方キャラスポナーにHpBarのWidgetクラスを渡す
		PlayerCharaSpawner->SetHpBarWidgetClass(HpBarWidgetClass);

		//エネミースポナーを生成
		EnemySpawner = NewObject<AEnemySpawner>();
		//ワールドのポインタをセット
		EnemySpawner->SetWorldPtr(GetWorld());
		//生成する敵のBPクラス情報を渡す
		EnemySpawner->SetEnemyCharacterClass(EnemyCharacterClass);
		//生成する遠距離タイプの敵のBPクラス情報を渡す
		EnemySpawner->SetLongRangeEnemyCharacterClass(LongRangeEnemyCharaClass);
		//敵スポナーにHpBarのWIdgetクラスを渡す
		EnemySpawner->SetHpBarWidgetClass(HpBarWidgetClass);

		//エネミースポナーマネージャーを生成し、ワールドにスポーンさせる
		EnemySpawnerManager = GetWorld()->SpawnActor<AEnemySpawnerManager>();

		//ゲームモードを取得し、自作のゲームモードにキャストする
		BattleLevelGameModePtr = Cast<ABattleLevelGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

		//キャストがされていれば
		if (IsValid(BattleLevelGameModePtr)) {
		
			//ゲームモードにバトルフィールドのポインタを渡す
			BattleLevelGameModePtr->SetBattleField(Field);

			//プレイヤーキャラスポナーのポインタを渡す
			BattleLevelGameModePtr->SetPlayerCharaSpawner(PlayerCharaSpawner);
			//敵スポナーのポインタを渡す
			BattleLevelGameModePtr->SetEnemySpawner(EnemySpawner);
			//敵スポナーのマネージャーのポインタを渡す
			BattleLevelGameModePtr->SetEnemySpawnerManager(EnemySpawnerManager);
			//HpBarWidgetのポインタを渡す
			BattleLevelGameModePtr->SetHpBarWidgetClass(PlayerBaseHpBarWidgetClass);
			//生成したDataManagerのポインタをGameModeに渡す
			BattleLevelGameModePtr->SetDataManagerPtr(DataManager);

			//レベルBPにカメラが設定されていれば
			if (IsValid(FieldCamera)) {

				//ゲームモードにカメラのポインタを渡す。
				BattleLevelGameModePtr->SetFieldCamera(FieldCamera);
			}

			BattleLevelGameModePtr->InitializeGameMode();


		}

	}
}

void ABattleLevel::BeginPlay() {
	Super::BeginPlay();

	/*if (IsValid(BattleLevelGameModePtr)) {

		BattleLevelGameModePtr->InitializeGameMode();
	}*/
}