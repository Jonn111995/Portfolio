// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/EnemySpawner.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemySpawner::SpawnEnemyCharacter(int TypeId, FVector Position) {

	//受取った引き数の座標を、スポーン地点として使う
	//スポーン地点は敵キャラの基地の座標を指定する。
	//キャラの回転の値
	FRotator rotate(0.0f, 0.0f, 0.0f);
	AEnemyCharacter* SpawnedChara = nullptr;

	const FTransform SpawnTransform = FTransform::Identity;

	switch (TypeId) {
	
	case AEnemyCharacter::kNormal:

		//敵キャラの種類を増やしたら、typeによってスポーンさせる敵キャラのBPを切り替える。
	//キャラをスポーンさせる
		SpawnedChara = WorldPtr->SpawnActorDeferred<AEnemyCharacter>(EnemyCharacterClass, SpawnTransform);
		SpawnedChara->SetEnemyType(AEnemyCharacter::kNormal);

		break;

	case AEnemyCharacter::kLongRange:

		SpawnedChara = WorldPtr->SpawnActorDeferred<AEnemyCharacter>(LongRangeEnemyClass, SpawnTransform);
		SpawnedChara->SetEnemyType(AEnemyCharacter::kLongRange);

		break;
	
	} 

	

	//スポーンしたキャラをアップキャストする
	ABaseCharacter* BaseChara = Cast<ABaseCharacter>(SpawnedChara);

	//キャストが成功すれば
	if (IsValid(BaseChara)) {

		//指定された座標をキャラが持つ自分がどこにいるかの座標を設定する
		BaseChara->SetXPoint(UKismetMathLibrary::Abs(Position.X / MapChipSize));
		BaseChara->SetYPoint(UKismetMathLibrary::Abs(Position.Y / MapChipSize));

		//ｚ座標は固定なので定数を入れる
		Position.Z = EnemyCharaSpawnZPosition;

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
		BaseChara->SetCharacterId(EnemyCharacterArray.Num());
		
		//キャラのポインタをマップにセットする
		CSpawnerInterface->RequestSetCharacterToPtrMap(BaseChara);
		//BaseCharacterのインターフェースを渡す
		CSpawnerInterface->RequestSetBaseCharaInterface(BaseChara);
		//Enemyのインターフェースを渡す
		EnemySpawnerInterface->RequestSetEnemyCharaEventInterface(BaseChara);

		BaseChara->SetHpBarWidgetClass(HpBarWidgetClass);

		//Baseクラスからプレイヤークラスにキャスト
		AEnemyCharacter* EnemyChara = Cast<AEnemyCharacter>(BaseChara);
		if (IsValid(EnemyChara)) {
			//キャラのステータスをセットする
			SetEnemyCharaStatus(EnemyChara);

			//スポーンさせる
			EnemyChara->FinishSpawning(SpawnTransform);
			//配列に追加
			EnemyCharacterArray.Push(EnemyChara);

		}
	}
}

void AEnemySpawner::DeleteEnemyCharacter(AEnemyCharacter* chara){

	if (IsValid(chara)) {
	
		//プレイヤーキャラの配列を検索
		for (auto ArrayInChara : EnemyCharacterArray) {

			if (IsValid(ArrayInChara)) {

				//削除しようとしているキャラと、検索したキャラのIDが同じなら
				if (chara == ArrayInChara) {

					//削除
					//ArrayInChara->Destroy();

					if (ArrayInChara->GetCharacterStatus() == AEnemyCharacter::CharacterStatus::kDead) {
						ArrayInChara->SetLifeSpan(0.1f);
					}
					else {

						ArrayInChara->SetLifeSpan(0.1f);
					}
					//配列からも削除する
					EnemyCharacterArray.Remove(ArrayInChara);

					break;
				}
			}
		}
	
	}
}

void AEnemySpawner::SetEnemyCharaStatus(AEnemyCharacter* EnemyChara){

	//現状は敵キャラのクラスが一つしか無く、データ配列も一つしかないので0を指定している
	//キャラを増やしたら処理を変える

	//キャラクターのステータスをセットする
	//キャラの種類
	EnemyChara->SetCharacterSide(EnemyStatusDataList[EnemyChara->GetEnemyType()].CharaSide);
	//HP
	EnemyChara->SetHp(EnemyStatusDataList[EnemyChara->GetEnemyType()].Hp);
	//攻撃力
	EnemyChara->SetAttack(EnemyStatusDataList[EnemyChara->GetEnemyType()].Attack);
	//防御力
	EnemyChara->SetDefense(EnemyStatusDataList[EnemyChara->GetEnemyType()].Defense);
	//X座標の索敵範囲
	EnemyChara->SetSerchXRange(EnemyStatusDataList[EnemyChara->GetEnemyType()].XRange);
	//Ｙ座標の索敵範囲
	EnemyChara->SetSerchYRange(EnemyStatusDataList[EnemyChara->GetEnemyType()].YRange);
	//攻撃スピード
	EnemyChara->SetAttackSpan(EnemyStatusDataList[EnemyChara->GetEnemyType()].AttackSpan);
	//移動スピード
	EnemyChara->SetWalkSpeed(EnemyStatusDataList[EnemyChara->GetEnemyType()].WalkSpeed);
	//索敵範囲の開始範囲
	EnemyChara->SetStartSerchRangeNum(EnemyStatusDataList[EnemyChara->GetEnemyType()].StartSerchRangeNum);
	//倒されたときに回復するコスト
	EnemyChara->SetHealCostForDefeating(EnemyStatusDataList[EnemyChara->GetEnemyType()].HealCostForDefeating);
}


void AEnemySpawner::DeleteDeadPlayerCharaInTargetEnemy(ABaseCharacter* chara){

	for (int i = 0; i < EnemyCharacterArray.Num(); i++) {
	
	    //死んだキャラクターをターゲットから外す
		EnemyCharacterArray[i]->DeleteTargetEnemy(chara);
		//攻撃されているフラグを降ろす
		EnemyCharacterArray[i]->SetbIsAttacked(false);
	
	}
}

void AEnemySpawner::StopEnemyCharacter(bool clear) {

	for (auto& Enemy : EnemyCharacterArray) {
	
		//キャラクターのステータスをポーズにして、処理を停止させる
		Enemy->SetCharacterStatus(ABaseCharacter::CharacterStatus::kPause);

		//ゲームオーバーなら
		if (clear) {
		
			//敵に勝利モーションを再生する
			Enemy->SetbIsVictoryAnimation(true);
		
		}
		//ゲームクリアなら
		else{

			//敗北モーションを再生する
			Enemy->SetbIsDefeatedAnimation(true);
		}
	}


}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

