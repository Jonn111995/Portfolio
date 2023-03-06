// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefenseGameInstance.h"
#include "Misc/ConfigCacheIni.h"

const FString& UTowerDefenseGameInstance::GetRoadChipPath(){
	return RoadChipPath;
}

const FString& UTowerDefenseGameInstance::GetCharacterSetPositionChipPath(){

	return CharacterSetPositionChipPath;
}

const FString& UTowerDefenseGameInstance::GetWallChipPath(){
	return WallChipPath;
}

const FString& UTowerDefenseGameInstance::GetDefenseBaseChipPath(){
	return DefenseBaseChipPath;
}

const FString& UTowerDefenseGameInstance::GetEnemyBaseChipPath(){
	return EnemyBaseChipPath;
}

const FString& UTowerDefenseGameInstance::GetPlayerCharacterPath(){

	return PlayerCharacterPath;
}

const FString& UTowerDefenseGameInstance::GetEnemyCharacterPath(){

	return EnemyCharacterPath;
}

const FString& UTowerDefenseGameInstance::GetBattleLevelHUDPath()
{
	return BattleLevelHUDPath;
}

const FString& UTowerDefenseGameInstance::GetCharacterIconPath(){

	return CharacterIconPath;
}


void UTowerDefenseGameInstance::InitializeGameInstance(){

	FString Path;
	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("RoadChipPath"), Path, GGameIni);
	RoadChipPath = Path;


	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("CharacterSetPositionChipPath"), Path, GGameIni);
	CharacterSetPositionChipPath = Path;


	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("WallChipPath"), Path, GGameIni);
	WallChipPath = Path;


	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("DefenseBaseChipPath"), Path, GGameIni);
	DefenseBaseChipPath = Path;


	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("EnemyBaseChipPath"), Path, GGameIni);
	EnemyBaseChipPath = Path;

	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("PlayerCharacterPath"), Path, GGameIni);
	PlayerCharacterPath = Path;

	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("BattleLevelHUDPath"), Path, GGameIni);
	BattleLevelHUDPath = Path;

	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("CharacterIconPath"), Path, GGameIni);
	CharacterIconPath = Path;

	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("CharacterLauncharDialogPath"), Path, GGameIni);
	CharacterLauncharPath = Path;

	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("EnemyCharacterPath"), Path, GGameIni);
	EnemyCharacterPath = Path;

	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("HpBarWidgetPath"), Path, GGameIni);
	HpBarWidgetPath = Path;

	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("LongRangePlayerCharaPath"), Path, GGameIni);
	LongRangePlayerCharaPath = Path;


	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("DefensePlayerCharaPath"), Path, GGameIni);
	DefensePlayerCharaPath = Path;

	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("LongRangeEnemyCharaPath"), Path, GGameIni);
	LongRangeEnemyPath = Path;

	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("TitleLevelMainWidgetPath"), Path, GGameIni);
	TitleLevelMainWidgetPath = Path;

	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("IntroductionWidgetpath"), Path, GGameIni);
	IntroductionWidgetPath = Path;

	//////ゲーム設定情報からパスを読みだす
	//GConfig->GetString(TEXT("UMGSettings"), TEXT("TitleLevelCreditWidgetPath"), Path, GGameIni);
	//TitleLevelCreditWidgetPath = Path;

	//////ゲーム設定情報からパスを読みだす
	//GConfig->GetString(TEXT("UMGSettings"), TEXT("CreditScrollBoxWidgetPath"), Path, GGameIni);
	//TitleLevelCreditScrollBoxWidgetPath = Path;

	//////ゲーム設定情報からパスを読みだす
	//GConfig->GetString(TEXT("UMGSettings"), TEXT("CreditTextBoxWidgetPath"), Path, GGameIni);
	//TitleLevelCreditTextBoxWidgetPath = Path;

	////ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("PlayerBaseHpBarWidgetPath"), Path, GGameIni);
	PlayerBaseHpBarWidgetPath = Path;

	bIsStartGameInstance = true;

}

void UTowerDefenseGameInstance::OnStart() {

	Super::OnStart();

	FString Path;
	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("RoadChipPath"), Path, GGameIni);
	RoadChipPath = Path;

	
	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("CharacterSetPositionChipPath"), Path, GGameIni);
	CharacterSetPositionChipPath = Path;

	
	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("WallChipPath"), Path, GGameIni);
	WallChipPath = Path;

	
	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("DefenseBaseChipPath"), Path, GGameIni);
	DefenseBaseChipPath = Path;

	
	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("EnemyBaseChipPath"), Path, GGameIni);
	EnemyBaseChipPath = Path;

	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("PlayerCharacterPath"), Path, GGameIni);
	PlayerCharacterPath = Path;

	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("BattleLevelHUDPath"), Path, GGameIni);
	BattleLevelHUDPath = Path;

	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("CharacterIconPath"), Path, GGameIni);
	CharacterIconPath = Path;

	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("CharacterLauncharDialogPath"), Path, GGameIni);
	CharacterLauncharPath = Path;

	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("EnemyCharacterPath"), Path, GGameIni);
	EnemyCharacterPath = Path;

	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("HpBarWidgetPath"), Path, GGameIni);
	HpBarWidgetPath = Path;

	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("LongRangePlayerCharaPath"), Path, GGameIni);
	LongRangePlayerCharaPath = Path;


	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("DefensePlayerCharaPath"), Path, GGameIni);
	DefensePlayerCharaPath = Path;

	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("LongRangeEnemyCharaPath"), Path, GGameIni);
	LongRangeEnemyPath = Path;

	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("TitleLevelMainWidgetPath"), Path, GGameIni);
	TitleLevelMainWidgetPath = Path;

	//ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("IntroductionWidgetpath"), Path, GGameIni);
	IntroductionWidgetPath = Path;

	//////ゲーム設定情報からパスを読みだす
	//GConfig->GetString(TEXT("UMGSettings"), TEXT("TitleLevelCreditWidgetPath"), Path, GGameIni);
	//TitleLevelCreditWidgetPath = Path;

	//////ゲーム設定情報からパスを読みだす
	//GConfig->GetString(TEXT("UMGSettings"), TEXT("CreditScrollBoxWidgetPath"), Path, GGameIni);
	//TitleLevelCreditScrollBoxWidgetPath = Path;

	//////ゲーム設定情報からパスを読みだす
	//GConfig->GetString(TEXT("UMGSettings"), TEXT("CreditTextBoxWidgetPath"), Path, GGameIni);
	//TitleLevelCreditTextBoxWidgetPath = Path;

	////ゲーム設定情報からパスを読みだす
	GConfig->GetString(TEXT("UMGSettings"), TEXT("PlayerBaseHpBarWidgetPath"), Path, GGameIni);
	PlayerBaseHpBarWidgetPath = Path;

	bIsStartGameInstance = true;
}