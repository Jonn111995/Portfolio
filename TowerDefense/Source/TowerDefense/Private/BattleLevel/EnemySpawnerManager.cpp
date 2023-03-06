// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/EnemySpawnerManager.h"
#include "EnemySpawnerManager.h"

// Sets default values
AEnemySpawnerManager::AEnemySpawnerManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CountTimeForDelay = 0.0f;
}

void AEnemySpawnerManager::SetEnemyBasePointList(){

	//ゲームモードに敵座標取得イベントの通知。
	EnemyBasePointList = ESpawnerManagerInterface->RequestGetEnemyBasePosition();
}

// Called when the game starts or when spawned
void AEnemySpawnerManager::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(EnemySpawner)) {
		
	}

	SetWave();
}

void AEnemySpawnerManager::ExecuteSpawn(float PassedTime, float DeltaTime) {

	CountTime = PassedTime;

	switch (NowPhase) {

	case kWait:


		break;


	case kSpawning:

		//現在のWaveのスポーン開始時間をカウント時間が超えたら
		if (CountTime >= NowWave.SpawnTime) {

			//スポーンをずらすための処理
			//スポーンさせる関数を呼ぶまでの時間から、毎フレームの時間を引く
			CountTimeForDelay -= DeltaTime;

			//そのずらす時間が0以下になったら、
			if (CountTimeForDelay <= 0) {

				//スポーンをリクエストする
				RequestSpawn(NextSpawnTypeIdIndex);

				//スポーンさせる敵キャラのタイプIDが入った配列の要素を指定するインデックスをインクリメント
				NextSpawnTypeIdIndex++;

				//次のフレームですぐにRequestSpawnを呼ばない為、3秒間待つようにする。
				CountTimeForDelay += DelayTime;

			}

			//現在のWaveで、スポーンさせる敵を最後までスポーンさせたら、
			if (NextSpawnTypeIdIndex == NowWave.SpanwTypeIdArray.Num()) {

				//スポーン間隔の時間をリセット
				CountTimeForDelay=0.0f;
				//次のWaveに移った時に配列を0番目から指定するため0にリセット
				NextSpawnTypeIdIndex = kFirstSpawnEnemyIndexNum;

				//次のWaveをセットする
				SetWave();
			}
		}

	}

}

// Called every frame
void AEnemySpawnerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AEnemySpawnerManager::RequestSpawn(int Id) {

	//ここは仮の処理
	//エネミーのスポーン地点をFieldで検索して、その座標からスポーンさせるようにする
	FVector EnemyPosition;
	
	//スポーンさせる座標をセット
	bool IsFind = SetSpawnPosition(EnemyPosition);

	//現在のウェーブで指定されたスポーン地点が、現在のマップに存在していなければ、
	if (IsFind == false) {

		//一つ目のスポーン地点にスポーンさせる
		float EnemySpanwXPoint = EnemyBasePointList[kFirstBaseIndex].XPointInWorld;
		float EnemySpanwYPoint = EnemyBasePointList[kFirstBaseIndex].YPointInWorld;

		EnemyPosition.X = EnemySpanwXPoint;
		EnemyPosition.Y = EnemySpanwYPoint;
		EnemyPosition.Z = kZPointInWorld;
	}

	//スポーンさせる
	EnemySpawner->SpawnEnemyCharacter(NowWave.SpanwTypeIdArray[Id], EnemyPosition);

}



void AEnemySpawnerManager::SetWave() {

	//まだWaveがセットされてなければ
	if (NowWave.WaveId== kSetWaveIsNone) {
	
		//最初のWaveをセットする
		NowWave = EnemyWaveInfoList[FirstWaveIndex];

		NowWaveIndex = FirstWaveIndex;
	}
	else {
	
		//エネミーWaveの配列数を取得
		int ArrayNum = EnemyWaveInfoList.Num();

		//現在のWaveIdが、Wave数の最大数を超えてなければ
		if (!(NowWave.WaveId >= ArrayNum)) {

			NowWaveIndex++;

			//次のWaveをセット
			NowWave = EnemyWaveInfoList[NowWaveIndex];
		}
		//超えていたら
		else if (NowWave.WaveId >= ArrayNum) {
		
			//スポーン処理を終わらせる
			NowPhase = kWait;

		}
	
	}

}

bool AEnemySpawnerManager::SetSpawnPosition(FVector& Enemyposition){

	//敵拠点座標配列を検索
	for (int i = 0; i < EnemyBasePointList.Num(); i++) {

		//現在のウェーブで指定されたスポーン地点と、敵拠点座標リストの中に一致するスポーン地点があれば、
		if (NowWave.SpawnPointId == EnemyBasePointList[i].EnemyBaseId) {

			//そのスポーン地点の座標をセット
			float EnemySpanwXPoint = EnemyBasePointList[i].XPointInWorld;
			float EnemySpanwYPoint = EnemyBasePointList[i].YPointInWorld;

			Enemyposition.X = EnemySpanwXPoint;
			Enemyposition.Y = EnemySpanwYPoint;
			Enemyposition.Z = kZPointInWorld;

			return true;
		}
	}

	return false;
}

