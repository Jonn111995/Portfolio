// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../BattleLevel/StructFile/EnemyWaveInfoStruct.h"
#include "EnemySpawner.h"
#include "../BattleLevel/Interface/ESpawnerManagerEventInterface.h"
#include "EnemySpawnerManager.generated.h"

UCLASS()
class AEnemySpawnerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawnerManager();

	//マネージャーのフェーズ
	enum EnemySpawnerManagerPhase {

		//待機
		kWait,

		//スポーンフェーズ
		kSpawning


	};

	/// <summary>
	///　スポナーのセッター
	/// </summary>
	/// <param name="spawner"></param>
	void SetEnemySpawner(AEnemySpawner* spawner) { EnemySpawner = spawner; };

	/// <summary>
	/// スポーンさせる敵の種類とスポーン開始時間を記したデータリスト
	/// </summary>
	/// <param name="list"></param>
	void SetEnemyWaveInfoList(TArray<EnemyWaveInfoStruct::WaveInfo> list) { EnemyWaveInfoList = list; };

	/// <summary>
	/// マネージャーのフェーズのセッター
	/// </summary>
	/// <param name="phase"></param>
	void SetSpawnerManagerPhase(EnemySpawnerManagerPhase phase) { NowPhase = phase; };

	/// <summary>
	/// Managerインターフェースのセッター
	/// </summary>
	/// <param name="Interface"></param>
	void SetESpwnerManagerInterface(IESpawnerManagerEventInterface* Interface) { ESpawnerManagerInterface = Interface; };

	/// <summary>
	/// 敵拠点の座標構造体リストをセット
	/// </summary>
	void SetEnemyBasePointList();

	void ExecuteSpawn(float PassedTime, float DeltaTime);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// <summary>
	/// スポナーのポインタ
	/// </summary>
	AEnemySpawner* EnemySpawner;

	/// <summary>
	/// Managerのインターフェース
	/// </summary>
	IESpawnerManagerEventInterface* ESpawnerManagerInterface;

	/// <summary>
	/// Wave情報のリスト
	/// </summary>
	TArray<EnemyWaveInfoStruct::WaveInfo> EnemyWaveInfoList;

	//現在のWave
	EnemyWaveInfoStruct::WaveInfo NowWave{};

	/// <summary>
	/// 現在のフェーズ
	/// </summary>
	EnemySpawnerManagerPhase NowPhase;

	/// <summary>
	/// 敵拠点の座標構造体リスト
	/// </summary>
	TArray<EnemyBasePointStruct::EnemyBasePoint> EnemyBasePointList;

	/// <summary>
	/// 現在のWaveID
	/// </summary>
	int NowGroupId;

	/// <summary>
	/// リスポーンの開始時間
	/// </summary>
	float RespawnTime;

	/// <summary>
	/// スポーン開始時間を測る時間
	/// </summary>
	float CountTime;

	/// <summary>
	/// スポーンの関数を呼ぶ時間を測る変数
	/// </summary>
	float CountTimeForDelay;

	/// <summary>
	/// 次にセットするWaveIdのインデクス番号
	/// </summary>
	int NextSpawnTypeIdIndex = 0;

	/// <summary>
	/// 現在のWaveId
	/// </summary>
	int NowWaveIndex;

	/// <summary>
	/// 最初にスポーンさせる敵のインデクス番号
	/// </summary>
	const int kFirstSpawnEnemyIndexNum = 0;

	/// <summary>
	/// Wave情報がセットされていないことを示す定数
	/// </summary>
	const int kSetWaveIsNone = 0;

	/// <summary>
	/// 最初のWaveを指定する定数
	/// </summary>
	const int FirstWaveIndex = 0;

private:

	//スポーンさせるZ座標
	//固定なので定数
	const float kZPointInWorld = 100.0f;
	//一つ目の敵拠点を指定するインデクス番号
	const int kFirstBaseIndex = 0;

	/// <summary>
	/// スポーンの間隔をどれぐらい開けるかの時間
	/// </summary>
	const float DelayTime = 3.0f;

	/// <summary>
	/// スポーンをリクエストする
	/// </summary>
	/// <param name="Index"></param>
	void RequestSpawn(int Index);

	/// <summary>
	/// Wave情報をセットする関数
	/// </summary>
	void SetWave();

	//拠点リストの拠点と、現在のウェーブで指定されたスポーンする拠点が一致するか確認し、一致すればその拠点の座標を参照で返す。
	bool SetSpawnPosition(FVector& Enemyposition);

};
