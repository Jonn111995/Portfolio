// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "BaseCharacter.h"
#include "../BattleLevel/StructFile/EnemyBasePointStruct.h"
#include "../BattleLevel/StructFile/PlayerBaseDataStruct.h"
#include "MapChipClass/BaseMapChipActor.h"
#include "MapChipClass/RoadMapChip.h"
#include "MapChipClass/PlayerSpawnMapChip.h"
#include "BattleField.generated.h"

USTRUCT()
struct FInnerInnerArray{

	GENERATED_BODY()

	UPROPERTY()
	TArray<ABaseCharacter*> ArrayOfBaseCharacter;
};


USTRUCT()
struct FInnerArray{

	GENERATED_BODY()

	UPROPERTY()
	TArray<FInnerInnerArray> ArrayOfInnerArray;
};

USTRUCT()
struct FInnerMapChipArray {

	GENERATED_BODY()

		UPROPERTY()
		TArray<ABaseMapChipActor*> ArrayOfInnerMapChipArray;
};


UCLASS()
/// <summary>
/// マップの情報を保持するクラス
/// </summary>
class ABattleField : public AActor {

	GENERATED_BODY()

public:

	/// <summary>
	/// マップチップの種類。マップのマスの番号と対応
	/// </summary>
	enum MapType {
		//道
		kRoad = 1,
		//味方キャラクターを置けるマス
		kCharaPosision = 100,
		//壁(通れないマス)
		kWall = 200,
		//自軍の拠点
		kBase = 1000,
		//敵拠点
		kEnemyBase = -2000

	};

	/// <summary>
	/// フィールドの方角を表す
	/// </summary>
	enum FieldDirection {

		//無し
		kNone,
		//北
		kNorth,
		//南
		kSouth,
		//東
		kEast,
		//西
		kWest,
		//北東
		kNorthEast,
		//北西
		kNorthWest,
		//南東
		kSouthEast,
		//南西
		kSouthWest
	};


	// Sets default values for this actor's properties
	ABattleField();

	/// <summary>
	/// マップに生成するBPのクラスの配列をセット
	/// </summary>
	/// <param name="map_chip"></param>
	void SetMapChipClass(const TArray <TSubclassOf<AStaticMeshActor>>& map_chip);
	/// <summary>
	/// マップを生成する関数
	/// </summary>
	/// <param name="world"></param>
	void SpawnMapChip();

	/// <summary>
	/// ワールドのポインタをセットする
	/// </summary>
	/// <param name="world"></param>
	void SetWorldPtr(UWorld* world);

	/// <summary>
	//指定のマスにキャラが置けるかどうかを確認する
	/// </summary>
	/// <param name="position"></param>
	/// <returns></returns>
	bool CheckMapChip(FVector position);
	/// <summary>
	/// 指定のマスに設定された方角を確認し、引き数で渡された方角の変数に代入する
	/// </summary>
	/// <param name="x">指定X座標</param>
	/// <param name="y">指定Y座標</param>
	/// <param name="direction"></param>
	void DecideDirectionCharacter(int x, int y, FieldDirection& direction);

	/// <summary>
	/// スポーンしたキャラがマップのどの位置にいるかをマップに書き込む関数
	/// </summary>
	/// <param name="chara">スポーンしたキャラ</param>
	void SetCharacterToPtrMap(ABaseCharacter* chara);
	/// <summary>
	/// キャラクターがマップのどこにいるかのマップを確認し、引き数のキャラがいる座標を見つけたら、そこをnullにする
	/// </summary>
	/// <param name="chara"></param>
	void ChangeToNullPtrMapInCharacter(ACharacter* chara);

	/// <summary>
	/// 敵が次に進む座標のマップチップの種類を確認して、進めるかどうかを確認する
	/// </summary>
	/// <param name="chara"></param>
	/// <param name="NextPointX"></param>
	/// <param name="NextPointY"></param>
	/// <returns></returns>
	bool CheckMapInfoAraundEnemy(ABaseCharacter& chara, int& NextPointX, int& NextPointY);

	/// <summary>
	/// 敵を索敵する関数
	/// </summary>
	/// <param name="serching_chara">索敵しているキャラのポインタ</param>
	/// <returns>見つけたキャラのポインタ</returns>
	TArray<ABaseCharacter*> SerchEnemy(ABaseCharacter* serching_chara);

	/// <summary>
	/// マップチップの配置情報の配列のセッター
	/// </summary>
	/// <param name="Map"></param>
	void SetFieldMap(TArray<TArray<int>> Map) { FieldMap = Map; };

	/// <summary>
	/// マップの各マスにキャラをスポーンさせたときにどこを向かせるかの情報配列のセッター
	/// </summary>
	/// <param name="Map"></param>
	void SetFieldDirectionMap(TArray<TArray<FieldDirection>> Map) { FieldDirectionMap = Map; };

	/// <summary>
	/// 敵拠点の座標を検索し、構造体に座標情報を入れて配列として返す
	/// </summary>
	/// <returns></returns>
	TArray<EnemyBasePointStruct::EnemyBasePoint> SerchEnemySpawnPoint();

	TArray<PlayerBaseDataStruct::PlayerBaseData> SerchPlayerBase();

	bool CheckReachPlayerBaseForEnemy(ACharacter* chara);

	void RequestSetMapChipInterface(IBaseMapChipInterface* Interface);
	void RequestSetSpawnMapChipPhase(APlayerSpawnMapChip::SpawnMapChipPhase phase);
	void RequestSetSpawnMapChipShowRange(int x, int y, int StartRange);
	void CallChangeColorMaterial(AActor* actor);
	void CallResetColorMaterial();

	/// <summary>
	///　キャラ選択中に発生させるエフェクトをスポーンさせる
	/// </summary>
	void RequestSpawnSelectingParticle();

	/// <summary>
	///　キャラ選択中に発生させるエフェクトを消す
	/// </summary>
	void RequestOffSelectingParticle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	/// <summary>
	/// マップの情報配列
	/// マップのサイズと、マスの種類が規定されている
	/// </summary>
	TArray<TArray<int>> FieldMap;

	/// <summary>
	/// どの方向へキャラが向けばよいかの方角が一マス毎にかかれたマップ
	/// </summary>
	TArray<TArray<FieldDirection>> FieldDirectionMap;

	/// <summary>
	/// マップのどの位置にキャラクターがいるかを確認するマップ
	/// </summary>
	UPROPERTY()
	TArray<FInnerArray> FieldCharacterMap;

	/// <summary>
	/// 生成に使うマップチップのＢＰクラスの配列
	/// </summary>
	UPROPERTY()
	TArray <TSubclassOf<AStaticMeshActor>> MapChip;

	UPROPERTY()
	TArray<FInnerMapChipArray> MapChipArrary;

	UPROPERTY()
	TArray<ARoadMapChip*> RoadMapChipArrary;

	UPROPERTY()
	TArray<APlayerSpawnMapChip*> PlayerSpawnMapChipArrary;

	/// <summary>
	/// 現在開いているワールドのポインタ
	/// </summary>
	UPROPERTY()
	UWorld* WorldPtr;

	//以下は配列の要素番号を指定する定数。とりあえず暫定で使っている
	/// <summary>
	/// MapChip配列の道のBPが格納されたインデックス番号
	/// </summary>
	const int kRoadNum = 0;
	/// <summary>
	/// MapChip配列の壁のBPが格納されたインデックス番号
	/// </summary>
	const int kWallNum = 1;
	/// <summary>
	/// MapChip配列の味方キャラクターが置けるマスのBPが格納されたインデックス番号
	/// </summary>
	const int kCharaPositionNum = 2;
	/// <summary>
	/// MapChip配列の自軍拠点のBPが格納されたインデックス番号
	/// </summary>
	const int kBaseNum = 3;
	/// <summary>
	/// MapChip配列の敵拠点のBPが格納されたインデックス番号
	/// </summary>
	const int kEnemyBaseNum = 4;

	//マップの原点Xを表す
	const int OriginXPoint = 0;
	//マップの原点Yを表す
	const int OriginYPoint = 0;
	//生成するマップチップのXのサイズ
	const float MapChipXSize = 100.0f;
	//生成するマップチップのYのサイズ
	const float MapChipYSize = 100.0f;
	//マップチップを生成するZの位置
	const float MapChipZPosition = 0.0f;

	const float kActorZPosition = 100.0f;
	/// <summary>
	/// 現在の座標から4方向を確認するときに、配列の要素指定数を調整するための定数
	/// </summary>
	const int kAdjustNumCheckDirection = 1;
	/// <summary>
	/// 索敵処理の時に、配列数の調整に使う
	/// </summary>
	const int kAdjustNumCheckSerch = 1;

	/// <summary>
	/// エネミー拠点にIDを付与するときに使う定数
	/// </summary>
	const int kAdjustNumForCreatingId = 1;

	const int kConvertSingToMinus = -1;

	/// <summary>
	/// X座標の最大値
	/// </summary>
	int XMax;
	/// <summary>
	/// Y座標の最大値
	/// </summary>
	int YMax;

	/// <summary>
	/// ｘ座標の最小値
	/// </summary>
	const int kXMin = 0;

	/// <summary>
	/// y座標の最小値
	/// </summary>
	const int kYMin = 0;

	const int kMaxRoadMapChipNum = 99;

	const int kMinRoadMapChipNum = 0;

	const int kCheckSerchStartNum = 1;

	/// <summary>
	/// 座標を渡して、その座標に敵がいるかどうかを確認する
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="BaseCharaArray">見つけた敵を確認する</param>
	void SerchEnemyForMap(int x, int y, TArray<ABaseCharacter*>& BaseCharaArray, ABaseCharacter::CharacterSide CharaSide);

	/// <summary>
	/// 更新したＸ座標がマップのＸ座標の最小値最大値をこえていないかを確認する
	/// </summary>
	/// <param name="x"></param>
	void CheckXMinOrMax(int& x, bool& OverMin, bool& OverMax);

	/// <summary>
	/// 更新したＹ座標がマップのＹ座標の最小値最大値を超えていないかを確認する
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void CheckYMinOrMax(int x, int& y, bool& OverMin, bool& OverMax);

	/// <summary>
	/// X座標が攻撃範囲内かどうかを確認する
	/// </summary>
	/// <param name="XRange"></param>
	/// <param name="NewX"></param>
	/// <param name="OriginX"></param>
	/// <returns></returns>
	bool CheckOutOfXRange(int XRange, int NewX, int OriginX);
	/// <summary>
	/// Y座標が攻撃範囲内かどうかを確認する
	/// </summary>
	/// <param name="YRange"></param>
	/// <param name="NewY"></param>
	/// <param name="OriginY"></param>
	/// <returns></returns>
	bool CheckOutOfYRange(int YRange, int NewY, int OriginY);

};
