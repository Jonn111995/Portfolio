// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/PlayerCharacterSpawner.h"
#include "BattleLevel/BaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APlayerCharacterSpawner::APlayerCharacterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool APlayerCharacterSpawner::SpawnPlayerCharacter(int TypeId, FVector Position){
	
	//受取った引き数の座標を、スポーン地点として使う
	//キャラの回転の値
	FRotator rotate(0.0f, 0.0f, 0.0f);
	APlayerCharacter* SpawnedChara = nullptr;

	//BattleLevelGameModeにキャラ配置をするイベント通知を行う。
	//指定した座標がキャラが置けるところか確認して、trueであればスポーンさせる
    bool bIsCanArrange = SpawnerInterface->RequestCheckCanArrange(Position);
	
	//キャラが置けると判断されれば、
	if (bIsCanArrange) {

		const FTransform SpawnTransform = FTransform::Identity;


		switch (TypeId) {
		
		
		case APlayerCharacter::kNormal:

			//キャラをスポーンさせる
			SpawnedChara = WorldPtr->SpawnActorDeferred<APlayerCharacter>(PlayerCharacterClass, SpawnTransform);
			SpawnedChara->SetPlayerCharaType(APlayerCharacter::kNormal);

			break;

		case APlayerCharacter::kLongRange:

			//キャラをスポーンさせる
			SpawnedChara = WorldPtr->SpawnActorDeferred<APlayerCharacter>(LongRangeCharacterClass, SpawnTransform);
			SpawnedChara->SetPlayerCharaType(APlayerCharacter::kLongRange);

			break;

		case APlayerCharacter::kDefense:

			//キャラをスポーンさせる
			SpawnedChara = WorldPtr->SpawnActorDeferred<APlayerCharacter>(DefenseCharacterClass, SpawnTransform);
			SpawnedChara->SetPlayerCharaType(APlayerCharacter::kDefense);

		}
		


	//スポーンしたキャラをアップキャストする
		ABaseCharacter* BaseChara = Cast<ABaseCharacter>(SpawnedChara);

		//キャストが成功すれば
		if (IsValid(BaseChara)) {
		
			//指定された座標をキャラが持つ自分がどこにいるかの座標を設定する
			BaseChara->SetXPoint(UKismetMathLibrary::Abs( Position.X/100));
			BaseChara->SetYPoint(UKismetMathLibrary::Abs(Position.Y/100));

			//ｚ座標は固定なので定数を入れる
			Position.Z = PlayerCharaSpawnZPosition;

			//キャラの向きを決定したいので、インターフェースを通して向きを決める関数を呼ぶ
			CSpawnerInterface->RequestDecideCharaDirection(*BaseChara);

			//キャラの方角を確認
			switch (BaseChara->GetNowDirection()) {

			//北なら
			case ABaseCharacter::CharacterDirection::kNorth:
				//そのまま
				rotate.Yaw = 0.0f;

				break;
			//南なら
			case ABaseCharacter::CharacterDirection::kSouth:
				//真逆に回転
				rotate.Yaw = 180.0f;

				break;
			//東なら時計回りに90度回転
			case ABaseCharacter::CharacterDirection::kEast:

				rotate.Yaw = 90.0f;

				break;
			//西なら反時計回りに90度回転
			case ABaseCharacter::CharacterDirection::kWest:

				rotate.Yaw = -90.0f;

				break;
			};

			//決定したキャラの位置と回転をスポーンするキャラにセット
			BaseChara->SetActorLocation(Position);
			BaseChara->SetActorRotation(rotate);

			//キャラクターIDを設定
			BaseChara->SetCharacterId(PlayerCharacterArray.Num());

			CSpawnerInterface->RequestSetCharacterToPtrMap(BaseChara);
			CSpawnerInterface->RequestSetBaseCharaInterface(BaseChara);
			SpawnerInterface->RequestSetPCharaEventInterface(BaseChara);

			BaseChara->SetHpBarWidgetClass(HpBarWidgetClass);

			UE_LOG(LogTemp, Log, TEXT("PlayerCharaSpawner::FinishSpawning"));

			//Baseクラスからプレイヤークラスにキャスト
		    APlayerCharacter* PlayerChara= Cast<APlayerCharacter>(BaseChara);
			if (IsValid(PlayerChara)) {

				//キャラのステータスをセットする
				SetPlayerCharaStatus(PlayerChara);

				PlayerChara->SetCharaPhase(APlayerCharacter::PlayerCharaPhase::kSpawn);

				//PlayerChara->BindFunction();

				PlayerChara->FinishSpawning(SpawnTransform);

				//配列に追加
				PlayerCharacterArray.Push(PlayerChara);
				UE_LOG(LogTemp, Log, TEXT("PlayerCharaSpawner::AddArrayChara"));

				return true;
			}

		}
		else {

			UE_LOG(LogTemp, Log, TEXT("PlayerCharaSpawner::CantCast"));

			return false;
		}
	
	}
	else {
	
		//trueなのにここでブレイクに引っかかる時がある。
		return false;
	}
	
	return false;
}

void APlayerCharacterSpawner::SetSpawnerInterface(IPlayerCharaSpawnerEventInterface* spawner_interface){

	SpawnerInterface = spawner_interface;
}

void APlayerCharacterSpawner::SetCharacterSpawnerInterface(ICharacterSpawnerEventInterface* Cspawner_interface){

	CSpawnerInterface = Cspawner_interface;
}

void APlayerCharacterSpawner::SetWorldPtr(UWorld* world){

	WorldPtr = world;
}

void APlayerCharacterSpawner::SetPlayerCharacterClass(TSubclassOf<class ACharacter> CharaClass){

	PlayerCharacterClass = CharaClass;
}

void APlayerCharacterSpawner::SetLongRangeCharacterClass(TSubclassOf<class ACharacter> CharaClass){

	LongRangeCharacterClass = CharaClass;
}

void APlayerCharacterSpawner::SetDefenseCharacterClass(TSubclassOf<class ACharacter> CharaClass){

	DefenseCharacterClass = CharaClass;
}

void APlayerCharacterSpawner::DeletePlayerCharacter(APlayerCharacter* chara){

	//プレイヤーキャラの配列を検索
	for (auto ArrayInChara : PlayerCharacterArray) {
	
		//取り出したポインタが有効であれば
		if (IsValid(ArrayInChara)) {
			//削除しようとしているキャラと、検索したキャラのIDが同じなら
			if (chara == ArrayInChara) {

				//撤退してキャラを削除する場合は、
				if (ArrayInChara->GetCharaPhase() == APlayerCharacter::PlayerCharaPhase::kRetreat) {

					ArrayInChara->SetLifeSpan(1.0f);
				}
				//キャラが死亡して削除するなら、
				else if (ArrayInChara->GetCharacterStatus() == APlayerCharacter::CharacterStatus::kDead) {
					ArrayInChara->SetLifeSpan(0.1f);
				}
				
				//配列からも削除する
				PlayerCharacterArray.Remove(ArrayInChara);

				break;
			}
		}
	}
}

void APlayerCharacterSpawner::SetPlayerCharaStatus(APlayerCharacter* PlayerChara){
	//現状は味方キャラのクラスが一つしか無く、データ配列も一つしかないので0を指定している
	//キャラを増やしたら処理を変える

	//キャラクターのステータスをセットする
	//キャラの種類
	PlayerChara->SetCharacterSide(PlayerStatusDataList[PlayerChara->GetPlayerCharaType()].CharaSide);
	//HP
	PlayerChara->SetHp(PlayerStatusDataList[PlayerChara->GetPlayerCharaType()].Hp);
	//攻撃力
	PlayerChara->SetAttack(PlayerStatusDataList[PlayerChara->GetPlayerCharaType()].Attack);
	//防御力
	PlayerChara->SetDefense(PlayerStatusDataList[PlayerChara->GetPlayerCharaType()].Defense);
	//X座標の索敵範囲
	PlayerChara->SetSerchXRange(PlayerStatusDataList[PlayerChara->GetPlayerCharaType()].XRange);
	//Ｙ座標の索敵範囲
	PlayerChara->SetSerchYRange(PlayerStatusDataList[PlayerChara->GetPlayerCharaType()].YRange);
	//攻撃スピード
	PlayerChara->SetAttackSpan(PlayerStatusDataList[PlayerChara->GetPlayerCharaType()].AttackSpan);
	//索敵開始処理
	PlayerChara->SetStartSerchRangeNum(PlayerStatusDataList[PlayerChara->GetPlayerCharaType()].StartSerchRangeNum);
	//止められる敵の数
	PlayerChara->SetStopEnemyNum(PlayerStatusDataList[PlayerChara->GetPlayerCharaType()].StopEnemyNum);
	//出撃に必要なコスト
	PlayerChara->SetNeedCost(PlayerStatusDataList[PlayerChara->GetPlayerCharaType()].NeedCost);
}

void APlayerCharacterSpawner::StopPlayerCharacter(bool clear){

	for (auto& Player : PlayerCharacterArray) {
	
		//キャラクターのステータスをポーズにして、処理を停止させる
		Player->SetCharacterStatus(ABaseCharacter::CharacterStatus::kPause);

		//ゲームをクリアしていれば、
		if (clear) {
		
			//勝利モーションを再生する
			Player->SetbIsVictoryAnimation(true);
		}
		//ゲームオーバーなら
		else {
		
			//敗北モーションを再生する
			Player->SetbIsDefeatedAnimation(true);
		
		}
	}
}

// Called when the game starts or when spawned
void APlayerCharacterSpawner::BeginPlay(){
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacterSpawner::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

