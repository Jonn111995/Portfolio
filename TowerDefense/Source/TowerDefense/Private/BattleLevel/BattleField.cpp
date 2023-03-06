// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/BattleField.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABattleField::ABattleField()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABattleField::SetMapChipClass(const TArray<TSubclassOf<AStaticMeshActor>>& map_chip) {

	MapChip = map_chip;
}

void ABattleField::SpawnMapChip() {

	/*キャラのポインタを格納し、マップのどこにいるか確認するためのマップ情報
	まず一次元をリサイズ*/
	FieldCharacterMap.SetNum(FieldMap.Num());
	//次に二次元をリサイズ
	for (int i = 0; i < FieldMap.Num(); i++) {

		for (int n = 0; n < FieldMap[i].Num(); n++) {
		
			TArray<FInnerInnerArray>& SecondDimensionArray = FieldCharacterMap[i].ArrayOfInnerArray;
			SecondDimensionArray.SetNum(FieldMap[n].Num());

		}
	}

	//まずキャラのフィールドマップの行の要素数分回す
	for (int i = 0; i < FieldCharacterMap.Num(); i++) {

		//次に要素の列分回す
		for (int m = 0; m < FieldCharacterMap[i].ArrayOfInnerArray.Num(); m++) {

			//配列を宣言し、
			TArray<ABaseCharacter*> Map;

			TArray<ABaseCharacter*>& ArrayOfBaseCharacterInSecondDimensitonArray = FieldCharacterMap[i].ArrayOfInnerArray[m].ArrayOfBaseCharacter;
			//指定した座標に配列を格納する
			ArrayOfBaseCharacterInSecondDimensitonArray = Map;
		}
	}

	//まず一次元をリサイズ
	MapChipArrary.SetNum(FieldMap.Num());
	//次に二次元をリサイズ
	for (int i = 0; i < FieldMap.Num(); i++) {

		for (int n = 0; n < FieldMap[i].Num(); n++) {

			TArray<ABaseMapChipActor*>& SecondDimensionArray = MapChipArrary[i].ArrayOfInnerMapChipArray;
			SecondDimensionArray.SetNum(FieldMap[n].Num());

		}
	}

	FActorSpawnParameters params;
	//マップ配列を回して、数字を確認し、それと対応するマップチップを生成する
	for (int x = 0; x < FieldMap.Num(); x++) {

		for (int y = 0; y < FieldMap[x].Num(); y++) {

			//原点からx方向にいくつ離れているか
			int CalculationX = OriginXPoint - x;
			//原点からy方向へいくつ離れいてるか
			int CalculationY = OriginYPoint + y;
			//生成するアクターのサイズ分マップチップを動かして生成するので、サイズを座標に掛ける。
			FVector position(CalculationX * MapChipXSize, CalculationY * MapChipYSize, MapChipZPosition);
			FRotator rotate(0.0f, 0.0f, 0.0f);

			if (FieldMap[x][y] < kMaxRoadMapChipNum && FieldMap[x][y] > kMinRoadMapChipNum) {

				//道のマップチップを生成
				ARoadMapChip* RoadChip = WorldPtr->SpawnActor<ARoadMapChip>(MapChip[kRoadNum], position, rotate);
				RoadChip->SetXPoint(x);
				RoadChip->SetYPoint(y);
				RoadChip->InitializeMapChip();
				RoadMapChipArrary.Push(RoadChip);
				MapChipArrary[x].ArrayOfInnerMapChipArray[y] = RoadChip;
			}
			else if (FieldMap[x][y] <= kEnemyBase) {
			
				//敵拠点を生成
				WorldPtr->SpawnActor<AStaticMeshActor>(MapChip[kEnemyBaseNum], position, rotate);
			}

			else {

				APlayerSpawnMapChip* SpawnMapChip;
				switch (FieldMap[x][y]) {
					//壁(通れないマス)なら
				case kWall:
					//壁を生成
					WorldPtr->SpawnActor<AStaticMeshActor>(MapChip[kWallNum], position, rotate);

					break;
					//味方キャラを置けるマスなら
				case kCharaPosision:

					//味方キャラを置けるマスを生成
					SpawnMapChip = WorldPtr->SpawnActor<APlayerSpawnMapChip>(MapChip[kCharaPositionNum], position, rotate);
					SpawnMapChip->SetXPoint(x);
					SpawnMapChip->SetYPoint(y);
					PlayerSpawnMapChipArrary.Push(SpawnMapChip);
					MapChipArrary[x].ArrayOfInnerMapChipArray[y] = SpawnMapChip;

					break;
					//自軍の拠点なら
				case kBase:
					//自軍の拠点を生成
					WorldPtr->SpawnActor<AStaticMeshActor>(MapChip[kBaseNum], position, rotate);

					break;

					//敵拠点なら
				//case kEnemyBase:
				//	//敵拠点を生成
				//	WorldPtr->SpawnActor<AStaticMeshActor>(MapChip[kEnemyBaseNum], position, rotate);

				//	break;
				}
			}
		}
	}
}

void ABattleField::SetWorldPtr(UWorld* world) {
	//ワールドのポインタを受取って設定
	WorldPtr = world;
}

bool ABattleField::CheckMapChip(FVector position) {

	//指定された座標のXとYを取得。
	//インデックスを指定するので、intにキャスト
	int x = static_cast<int>(UKismetMathLibrary::Abs(position.X / 100.0f));
	int y = static_cast<int>(UKismetMathLibrary::Abs(position.Y / 100.0f));

	//取得した座標がフィールドの大きさを超えていないか確認
	if (x >= FieldMap.Num()) {

		//超えていたらキャラを配置させない
		return false;
	}
	else if (y >= FieldMap[x].Num()) {
	
		return false;
	}

	//取得した座標がフィールドの大きさを超えていないか確認
	if (x < 0 || y < 0) {

		//超えていたらキャラを配置させない
		return false;
	}

	TArray<ABaseCharacter*>& ArrayOfBaseCharacterInSecondDimensitonArray = FieldCharacterMap[x].ArrayOfInnerArray[y].ArrayOfBaseCharacter;

	//指定した座標を確認し、
	switch (FieldMap[x][y]) {
		//キャラが置けるマスなら
	case kCharaPosision:


		//配列の要素数が0の場合ならキャラを置けると判断する
		if (ArrayOfBaseCharacterInSecondDimensitonArray.Num() == 0) {

			return true;

		}
		else {
			//撤退のバグが起きた後に、キャラがいないはずのマスをクリックすると、
			//そこにポインタが残っているため、ここに分岐してしまう。
			return false;
		}


		break;

		//そうでなければfalse
	default:

		return false;

		break;
	}
	return false;
}

void ABattleField::DecideDirectionCharacter(int x, int y, FieldDirection& direction) {

	//指定した座標のマスの方角を確認し、引き数に代入。
	direction = FieldDirectionMap[x][y];

}

void ABattleField::SetCharacterToPtrMap(ABaseCharacter* chara) {

	if (IsValid(chara)) {

		//座標を取得し、
		int XPoint = chara->GetXPoint();
		int YPoint = chara->GetYPoint();

		TArray<ABaseCharacter*>& ArrayOfBaseCharacterInSecondDimensitonArray = FieldCharacterMap[XPoint].ArrayOfInnerArray[YPoint].ArrayOfBaseCharacter;

		//マップにキャラのポインタを格納
		ArrayOfBaseCharacterInSecondDimensitonArray.Add(chara);
	}
}

void ABattleField::ChangeToNullPtrMapInCharacter(ACharacter* chara) {

	ABaseCharacter* BaseChara = Cast<ABaseCharacter>(chara);

	if (IsValid(BaseChara)) {
		//座標を取得し、
		int XPoint = BaseChara->GetXPoint();
		int YPoint = BaseChara->GetYPoint();

		TArray<ABaseCharacter*>& ArrayOfBaseCharacterInSecondDimensitonArray = FieldCharacterMap[XPoint].ArrayOfInnerArray[YPoint].ArrayOfBaseCharacter;

		//キャラクターのフィールドマップの要素に入っている、配列の要素の数だけ回す
		for (int i = 0; i < ArrayOfBaseCharacterInSecondDimensitonArray.Num(); i++) {

			if (IsValid(ArrayOfBaseCharacterInSecondDimensitonArray[i])) {
				//配列の要素にある、配列の要素を一つずつ見て、そこに入っているキャラのポインタを参照する
				//そして、そのキャラのIDを取得し、引き数のキャラのIDを比較する
				if (ArrayOfBaseCharacterInSecondDimensitonArray[i] == BaseChara) {

					//一致すれば、その要素を配列から削除する
					ArrayOfBaseCharacterInSecondDimensitonArray.RemoveAt(i);

				}
			}
		}
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("CantDeletePtr"));

		return;
	}
}

bool ABattleField::CheckMapInfoAraundEnemy(ABaseCharacter& chara, int& NextPointX, int& NextPointY) {

	//敵キャラの現在の座標を取得する
	int x = chara.GetXPoint();
	int y = chara.GetYPoint();

	//四方向の配列を宣言初期化	
	TArray<FieldDirection> DirectionList = { kNorth,kSouth,kEast,kWest };

	//四方向の配列を回す
	for (int i = 0; i < DirectionList.Num(); i++) {

		int NewX = 0;
		int NewY = 0;

		switch (DirectionList[i]) {

			//北を見る
		case kNorth:

			//北方向の座標を見る為今いる座標に-１
			NewX = x - kAdjustNumCheckDirection;

			//値が0を下回ったら
			if (NewX < 0) {
				//現在の座標と同じにする
				NewX = 0;
			}
			 
			//CheckXMinOrMax(NewX);

			//北方向の座標が道かプレイヤー拠点であり、
			if (FieldMap[NewX][y] <= kMaxRoadMapChipNum || FieldMap[NewX][y] == kBase){
				//かつ今いる座標のマスの数字より、北方向のマスの数字の方が大きければ
				if (FieldMap[x][y] < FieldMap[NewX][y]) {

					//次へ向かう座標に代入する
					NextPointX = NewX;
					NextPointY = y;
					return true;

				}

			}
			break;

		case kSouth:

			//南方向の座標を見る為今いる座標に+1
			NewX = x + kAdjustNumCheckDirection;

			//CheckXMinOrMax(NewX);

			//+1をして配列の要素数を超えてしまったら
			if (NewX >= FieldMap.Num()) {

				//今いるＸ座標の値と同じにする
				NewX = FieldMap.Num() - 1;
			}
			//南方向の座標が道かプレイヤー拠点であり、
			if (FieldMap[NewX][y] <= kMaxRoadMapChipNum || FieldMap[NewX][y] == kBase) {
				//かつ今いる座標のマスの数字より、南方向のマスの数字の方が大きければ
				if (FieldMap[x][y] < FieldMap[NewX][y]) {

					//次へ向かう座標に代入する
					NextPointX = NewX;
					NextPointY = y;
					return true;

				}

			}
			break;

			//東なら
		case kEast:

			//東方向を見る為、今いる座標にy方向へ＋１
			NewY = y + kAdjustNumCheckDirection;

			//CheckYMinOrMax(x,NewY);

			//足した結果、要素数を超えてしまったら
			if (NewY >= FieldMap[x].Num()) {

				//今いる座標と同じにする
				NewY = FieldMap[x].Num() - 1;
			}

			//東方向の座標が道かプレイヤー拠点であり
			if (FieldMap[x][NewY] <= kMaxRoadMapChipNum || FieldMap[x][NewY] == kBase) {
				//かつ今いる座標のマスの数字より、東方向のマスの数字の方が大きければ
				if (FieldMap[x][y] < FieldMap[x][NewY]) {
					//次へ向かう座標に代入する
					NextPointX = x;
					NextPointY = NewY;
					return true;

				}

			}
			break;

			//西方向なら
		case kWest:

			//西方向の座標を見るため、今いる座標から-1
			NewY = y - kAdjustNumCheckDirection;


			//CheckYMinOrMax(x, NewY);

			//引いた結果、0を下回ったら、
			if (NewY < 0) {

				//現在いる座標と同じにする
				NewY = 0;
			}
			//西方向の座標が道かプレイヤーの拠点であり、
			if (FieldMap[x][NewY] <= kMaxRoadMapChipNum || FieldMap[x][NewY] == kBase) {
				//かつ今いる座標のマスの数字より、西方向のマスの数字の方が大きければ
				if (FieldMap[x][y] < FieldMap[x][NewY]) {
					//次へ向かう座標に代入する
					NextPointX = x;
					NextPointY = NewY;
					return true;
				}
			}
			break;

		default:

			return false;
			break;
		}


	}
	return false;
}

TArray<ABaseCharacter*> ABattleField::SerchEnemy(ABaseCharacter* serching_chara) {

	//キャラの現在の座標を取得する
	int x = serching_chara->GetXPoint();
	int y = serching_chara->GetYPoint();
	//キャラの索敵範囲を取得する
	int CharaXRange = serching_chara->GetSerchXRange();
	int CharaYRange = serching_chara->GetSerchYRange();
	int SerchStartRange = serching_chara->GetStartSerchRangeNum();


	ABaseCharacter::CharacterSide SerchingCharaSide = serching_chara->GetCharacterSide();

	TArray<FInnerInnerArray>& SecondDimensionArray = FieldCharacterMap[x].ArrayOfInnerArray;


	XMax = FieldCharacterMap.Num() -kAdjustNumCheckSerch;
	YMax = SecondDimensionArray.Num() - kAdjustNumCheckSerch;

	//見つけたキャラのポインタを格納する配列
	TArray<ABaseCharacter*> BaseCharaArray;
	//8方向の配列を宣言初期化	
	TArray<FieldDirection> DirectionList = { kNorth, kSouth, kEast, kWest, kNorthEast, kNorthWest, kSouthEast, kSouthWest };

	//8方向の配列を回す
	for (int i = 0; i < DirectionList.Num(); i++) {

		//現在の座標を代入
		int NewX = x;
		int NewY = y;

		bool bIsOverYMin = false;
		bool bIsOverYMax = false;
		bool bIsOverXMin = false;
		bool bIsOverXMax = false;

		bool CheckOutOfRange = false;
		switch (DirectionList[i]) {

			//北を見る
		case kNorth:

			//北方向の座標を1ループ毎に引いていく
			for (int g = SerchStartRange; g <= CharaXRange; g++) {

				NewX = x - g;

				if (NewX < 0) {

					continue;
				}
				//xの座標が最小値か最大値を超えているかどうかを確認し、当てはまれば調整した値を返す
				CheckXMinOrMax(NewX, bIsOverXMin, bIsOverXMax);

				CheckOutOfRange = CheckOutOfXRange(CharaXRange, NewX, x);

				if (!CheckOutOfRange) {
					//更新した座標に敵がいるかどうかを確認する
					SerchEnemyForMap(NewX, y, BaseCharaArray, SerchingCharaSide);
				}
				
			}
			break;

		//南を見る
		case kSouth:

			//南方向の座標を1ループ毎に足していく
			for (int g = SerchStartRange; g <= CharaXRange; g++) {

				NewX = x + g;

				if (NewX > XMax) {
				
					continue;
				}
				//xの座標が最小値か最大値を超えているかどうかを確認し、当てはまれば調整した値を返す
				CheckXMinOrMax(NewX, bIsOverXMin, bIsOverXMax);

				CheckOutOfRange = CheckOutOfXRange(CharaXRange, NewX, x);

				if (!CheckOutOfRange) {
					//更新した座標に敵がいるかどうかを確認する
					SerchEnemyForMap(NewX, y, BaseCharaArray, SerchingCharaSide);
				}
			}
			break;

			//東なら
		case kEast:

			//南方向の座標を1ループ毎に足していく
			for (int g = SerchStartRange; g <= CharaYRange; g++) {

				NewY = y + g;

				if (NewY > YMax) {
				
					continue;
				}

				//yの座標が最小値か最大値を超えているかどうかを確認し、当てはまれば調整した値を返す
				CheckYMinOrMax(x, NewY, bIsOverYMin, bIsOverYMax);
				CheckOutOfRange = CheckOutOfYRange(CharaYRange, NewY, y);

				if (!CheckOutOfRange) {

					//更新した座標に敵がいるかどうかを確認する
					SerchEnemyForMap(x, NewY, BaseCharaArray, SerchingCharaSide);
				}
			}
			break;

			//西方向なら
		case kWest:

			//西方向の座標を1ループ毎に足していく
			for (int g = SerchStartRange; g <= CharaYRange; g++) {

				NewY = y - g;

				if (NewY < 0) {
				
					continue;
				}
				//yの座標が最小値か最大値を超えているかどうかを確認し、当てはまれば調整した値を返す
				CheckYMinOrMax(x, NewY, bIsOverYMin, bIsOverYMax);

				CheckOutOfRange = CheckOutOfYRange(CharaYRange, NewY, y);

				if (!CheckOutOfRange) {

					//更新した座標に敵がいるかどうかを確認する
					SerchEnemyForMap(x, NewY, BaseCharaArray, SerchingCharaSide);
				}
			}
			break;

		//北東なら
		case kNorthEast:

			//東方向にプラスする
			for (int f = CharaYRange; 0 <= f; f--) {
				
				NewY = y + f;
				//yの座標が最小値か最大値を超えているかどうかを確認し、当てはまれば調整した値を返す
				CheckYMinOrMax(x, NewY, bIsOverYMin, bIsOverYMax);

				//北方向にマイナスする
				for (int g = kCheckSerchStartNum; g <= CharaXRange; g++) {
					
					NewX = x - g;
					//xの座標が最小値か最大値を超えているかどうかを確認し、当てはまれば調整した値を返す
					CheckXMinOrMax(NewX, bIsOverXMin, bIsOverXMax);

					if (bIsOverYMax) {

						CheckOutOfRange = CheckOutOfXRange(SerchStartRange, NewX, x);
					}

					if (!CheckOutOfRange) {

						//更新した座標に敵がいるかどうかを確認する
						SerchEnemyForMap(NewX, NewY, BaseCharaArray, SerchingCharaSide);
					}
					
				}
				
			}	
			break;

		//北西なら
		case kNorthWest:

			//y座標をマイナスする
			//yの索敵範囲分マイナスしていく。
			for (int f = CharaYRange; 0 <= f; f--) {

				NewY = y - f;
				//yの座標が最小値か最大値を超えているかどうかを確認し、当てはまれば調整した値を返す
				CheckYMinOrMax(x, NewY, bIsOverYMin, bIsOverYMax);
				//x座標をマイナスしていく。
				//ｘの索敵範囲分マイナスしていく。
				for (int g = kCheckSerchStartNum; g <= CharaXRange; g++) {

					NewX = x - g;
					//xの座標が最小値か最大値を超えているかどうかを確認し、当てはまれば調整した値を返す
					CheckXMinOrMax(NewX, bIsOverXMin, bIsOverXMax);

					if (bIsOverYMin) {

						CheckOutOfRange = CheckOutOfXRange(SerchStartRange, NewX, x);
					}

					if (!CheckOutOfRange) {

						//更新した座標に敵がいるかどうかを確認する
						SerchEnemyForMap(NewX, NewY, BaseCharaArray, SerchingCharaSide);
					}

				}
			}
			break;
			
		//南東なら
		case kSouthEast:

			//y座標をプラスする
			//yの索敵範囲分プラスしていく。
			for (int f = CharaYRange; 0 <= f; f--) {

				NewY = y + f;
				//yの座標が最小値か最大値を超えているかどうかを確認し、当てはまれば調整した値を返す
				CheckYMinOrMax(x, NewY, bIsOverYMin, bIsOverYMax);

				//x座標をプラスする
				//xの範囲分プラスしていく
				for (int g = kCheckSerchStartNum; g <= CharaXRange; g++) {

					NewX = x + g;
					//xの座標が最小値か最大値を超えているかどうかを確認し、当てはまれば調整した値を返す
					CheckXMinOrMax(NewX , bIsOverXMin, bIsOverXMax);

					if (bIsOverYMax) {

						CheckOutOfRange = CheckOutOfXRange(SerchStartRange, NewX, x);
					}

					if (!CheckOutOfRange) {
						//更新した座標に敵がいるかどうかを確認する
						SerchEnemyForMap(NewX, NewY, BaseCharaArray, SerchingCharaSide);
					}
				}
			}

			break;

		//南西なら
		case kSouthWest:

			//y座標をマイナスしていく
			//ｙの索敵範囲分マイナスしていく
			for (int f = CharaYRange; 0 <= f; f--) {

				NewY = y - f;
				//yの座標が最小値か最大値を超えているかどうかを確認し、当てはまれば調整した値を返す
				CheckYMinOrMax(x, NewY, bIsOverYMin, bIsOverYMax);
				//x座標をプラスしていく
				//xの索敵範囲分マイナスしていく
				for (int g = kCheckSerchStartNum; g <= CharaXRange; g++) {

					NewX = x + g;
					//xの座標が最小値か最大値を超えているかどうかを確認し、当てはまれば調整した値を返す
					CheckXMinOrMax(NewX, bIsOverXMin, bIsOverXMax);

					if (bIsOverYMin) {
						CheckOutOfRange = CheckOutOfXRange(SerchStartRange, NewX, x);
					}

					if (!CheckOutOfRange) {
						//更新した座標に敵がいるかどうかを確認する
						SerchEnemyForMap(NewX, NewY, BaseCharaArray, SerchingCharaSide);
					}
				}
			}

			break;
		default:

			return BaseCharaArray;
			break;
		}
	}
	return BaseCharaArray;
	}


	TArray<EnemyBasePointStruct::EnemyBasePoint> ABattleField::SerchEnemySpawnPoint(){

		//敵拠点の座標を格納した構造体の配列
		TArray<EnemyBasePointStruct::EnemyBasePoint> EnemyBasePointArray;

		//まずキャラのフィールドマップの行の要素数分回す
		for (int i = 0; i < FieldMap.Num(); i++) {

			//次に要素の列分回す
			for (int m = 0; m < FieldMap[i].Num(); m++) {

				//敵拠点の数字以下であれば、
				if (FieldMap[i][m] <= kEnemyBase) {

					//ワールドでのX座標を計算
					float WorldXPoint = i * MapChipXSize * kConvertSingToMinus;
					//ワールドでのY座標を計算
					float WorldYPoint = m * MapChipYSize;
					//見つけた拠点にIDを付与
					int Id = EnemyBasePointArray.Num() + kAdjustNumForCreatingId;
				
					//構造体を宣言し、値を代入し初期化
					EnemyBasePointStruct::EnemyBasePoint EnemyBasePoint{Id, i, m, WorldXPoint, WorldYPoint };

					//配列に追加
					EnemyBasePointArray.Add(EnemyBasePoint);

				}
			}
		}

		//見つけた拠点の配列を返す
		return EnemyBasePointArray;
	}

	TArray<PlayerBaseDataStruct::PlayerBaseData> ABattleField::SerchPlayerBase(){

		//味方拠点の座標を格納した構造体の配列
		TArray<PlayerBaseDataStruct::PlayerBaseData> PlayerBaseArray;

		//まずキャラのフィールドマップの行の要素数分回す
		for (int i = 0; i < FieldMap.Num(); i++) {

			//次に要素の列分回す
			for (int m = 0; m < FieldMap[i].Num(); m++) {

				//味方拠点の数字以下であれば、
				if (FieldMap[i][m] >= kBase) {

					//X座標
					int XPoint = i;
					//Y座標
					int YPoint = m;

					//ワールドでのX座標を計算
					float WorldXPoint = i * MapChipXSize * kConvertSingToMinus;
					//ワールドでのY座標を計算
					float WorldYPoint = m * MapChipYSize;

					float WorldZPoint = kActorZPosition;
					//見つけた拠点にIDを付与
					int Id = PlayerBaseArray.Num() + kAdjustNumForCreatingId;

					//構造体を宣言し、値を代入し初期化
					PlayerBaseDataStruct::PlayerBaseData PlayerBase{ Id, XPoint, YPoint, WorldXPoint, WorldYPoint, WorldZPoint };

					//配列に追加
					PlayerBaseArray.Add(PlayerBase);

				}
			}
		}

		return PlayerBaseArray;
	}

	bool ABattleField::CheckReachPlayerBaseForEnemy(ACharacter* chara){
		
		ABaseCharacter* Enemy = Cast<ABaseCharacter>(chara);

		if (IsValid(Enemy)) {
		
			//敵の現在の座標が、味方拠点の地点であれば、
			if (FieldMap[Enemy->GetXPoint()][Enemy->GetYPoint()] == kBase) {
			
				//着いたことを示す
				return true;
			}
		}
		return false;
	}

	void ABattleField::RequestSetMapChipInterface(IBaseMapChipInterface* Interface){

		for (int i = 0; i < MapChipArrary.Num(); i++) {
		
		    //マップチップのアクターにBaseMapChipインターフェースを渡す
			for (int j = 0; j < MapChipArrary[i].ArrayOfInnerMapChipArray.Num(); j++) {
			
				if (IsValid(MapChipArrary[i].ArrayOfInnerMapChipArray[j])) {
				
					MapChipArrary[i].ArrayOfInnerMapChipArray[j]->SetBaseMapChipInterface(Interface);
				}

			}
		
		}
	}

	void ABattleField::RequestSetSpawnMapChipPhase(APlayerSpawnMapChip::SpawnMapChipPhase phase){

		//スポーン地点のマップチップのフェーズを変更する
		//キャラを選択中以外はマウスカーソルを置いても処理をさせないように、フェーズを一括で変更する
		//キャラ選択中はkSelecting、そうでないときはkNone
		for (auto& SpawnMapChip : PlayerSpawnMapChipArrary) {
		
			if (IsValid(SpawnMapChip)) {
		
				SpawnMapChip->SetSpawnMapChipPhase(phase);		
			}
		}
	}

	void ABattleField::RequestSetSpawnMapChipShowRange(int x, int y, int StartRange){

		//スポーン地点のマップチップのアクターに、出撃しようとしているキャラの索敵範囲と索敵開始範囲を代入する
		for (auto& SpawnMapChip : PlayerSpawnMapChipArrary) {

			if (IsValid(SpawnMapChip)) {

				//索敵X座標
				SpawnMapChip->SetCharacterSerchRangeX(x);
				//索敵Y座標
				SpawnMapChip->SetCharacterSerchRangeY(y);
				//索敵開始距離
				SpawnMapChip->SetSerchRangeStart(StartRange);
			}
		}
	}

	void ABattleField::CallChangeColorMaterial(AActor* actor){

		APlayerSpawnMapChip* SpawnMapChip = Cast<APlayerSpawnMapChip>(actor);

		if (IsValid(SpawnMapChip)) {
		
			//スポーン地点のXY座標
			int SpawnXPoint = SpawnMapChip->GetXPoint();
			int SpawnYPoint = SpawnMapChip->GetYPoint();

			//選択中のキャラの索敵範囲
			int RangeX = SpawnMapChip->GetCharacterSerchRangeX();
			int RangeY = SpawnMapChip->GetCharacterSerchRangeY();

			//索敵範囲の開始距離
			int StartRange = SpawnMapChip->GetSerchRangeStart();

			//スポーン地点から索敵範囲を足した座標
			//北方向
			int NewNorthX = SpawnXPoint - RangeX;
			//南方向
			int NewSouthX = SpawnXPoint + RangeX;
			//東方向
			int NewEastY = SpawnYPoint + RangeY;
			//西方向
			int NewWestY = SpawnYPoint - RangeY;

			//道のマップチップの配列を回す
			for (int i = 0; i < RoadMapChipArrary.Num(); i++) {
			
				//変数に代入
				ARoadMapChip* Road = RoadMapChipArrary[i];
				
				//索敵範囲の外かどうか
				bool bIsOut = false;
				//道の座標を取得する
				int RoadX = Road->GetXPoint();
				int RoadY = Road->GetYPoint();
				
				//スポーン地点と道のそれぞれのXY座標の絶対値を求める
				int DifferX = UKismetMathLibrary::Abs(SpawnXPoint - RoadX);
				int DifferY = UKismetMathLibrary::Abs(SpawnYPoint - RoadY);

				//道のX座標がスポーン地点から索敵範囲の距離を足した北方向の座標よりも大きく、かつ南方向の範囲よりも小さく、
				if (RoadX >= NewNorthX && RoadX <= NewSouthX) {
					//道のY座標が、スポーン地点から索敵範囲の距離を足した東方向の範囲より小さく、かつ西方向の座標より大きければ、
					if (RoadY <= NewEastY && RoadY >= NewWestY) {

						//道の座標とスポーン地点との差の絶対値が、索敵範囲外であれば、
						if (DifferX < StartRange && DifferY < StartRange) {

							//範囲外であるフラグを立てる
							bIsOut = true;
						}

						//範囲外でなければ、
						if (!bIsOut) {
							//道のフェーズを発光フェーズへ
							Road->SetRoadChipPhase(ARoadMapChip::RoadChipPhase::kEmit);
							//マテリアルの色を変える
							Road->ChangeMaterialColor();
						}
					}
				}	
			}
		}
	}

	void ABattleField::CallResetColorMaterial() {

		for (auto& Road : RoadMapChipArrary) {
		
		
			if (IsValid(Road)) {

				if (Road->GetRoadChipPhase() == ARoadMapChip::RoadChipPhase::kEmit) {
				
				
					Road->ResetMaterialColor();
					Road->SetRoadChipPhase(ARoadMapChip::RoadChipPhase::kNone);
				
				}
			}
		}
	}


void ABattleField::RequestSpawnSelectingParticle(){

	for (int i = 0; i < PlayerSpawnMapChipArrary.Num(); i++) {
	
	
		if (IsValid(PlayerSpawnMapChipArrary[i])) {
		
			PlayerSpawnMapChipArrary[i]->EmitSelectingParticle();
		
		
		}
	
	}

	//for (auto& SpawnMapChip : PlayerSpawnMapChipArrary) {

	//	if (IsValid(SpawnMapChip)) {

	//		//エフェクトを発生させる
	//		SpawnMapChip->EmitSelectingParticle();

	//	}
	//}
}

void ABattleField::RequestOffSelectingParticle(){

	for (auto& SpawnMapChip : PlayerSpawnMapChipArrary) {

		if (IsValid(SpawnMapChip)) {

			//エフェクトを発生させる
			SpawnMapChip->OffSelectingParticle();

		}
	}
}

// Called when the game starts or when spawned
void ABattleField::BeginPlay() {

	Super::BeginPlay();

}

// Called every frame
void ABattleField::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void ABattleField::SerchEnemyForMap(int x, int y, TArray<ABaseCharacter*>& BaseCharaArray, ABaseCharacter::CharacterSide CharaSide){

	bool checkSameCharaExist = false;
	TArray<ABaseCharacter*>& ArrayOfBaseCharacterInSecondDimensitonArray = FieldCharacterMap[x].ArrayOfInnerArray[y].ArrayOfBaseCharacter;
	
	//座標に格納されたキャラのポインタ配列を検索
	for (int j = 0; j < ArrayOfBaseCharacterInSecondDimensitonArray.Num(); j++) {
		UE_LOG(LogTemp, Log, TEXT("Call::SerchEnemyForMap::x::%d"),x);
		UE_LOG(LogTemp, Log, TEXT("Call::SerchEnemyForMap::y::%d"),y);
		
		//配列の要素にポインタが格納されていれば
		if (ArrayOfBaseCharacterInSecondDimensitonArray.IsValidIndex(j)) {

			if (IsValid(ArrayOfBaseCharacterInSecondDimensitonArray[j])) {

				//見つけた敵と索敵しているキャラの敵味方の種類が異なれば
				if (ArrayOfBaseCharacterInSecondDimensitonArray[j]->GetCharacterSide() != CharaSide) {


					for (int i = 0; i < BaseCharaArray.Num(); i++) {
					
					
						if (BaseCharaArray[i] == ArrayOfBaseCharacterInSecondDimensitonArray[j]) {
						
						
							checkSameCharaExist = true;
						}
					}

					if (!checkSameCharaExist) {
						//そのポインタを格納する
						BaseCharaArray.Add(ArrayOfBaseCharacterInSecondDimensitonArray[j]);
					}
				}
			}

		}

	}	
}

void ABattleField::CheckXMinOrMax(int& x , bool& OverMin, bool& OverMax){

	//マイナスしてx座標の最小値を下回ったら
	if (x < kXMin) {
	
		//x座標をxの最小値にする
		x = kXMin;

		OverMin = true;
	}
	//+1をしてy座標の要素数を超えてしまったら
	else if (x >= FieldCharacterMap.Num()) {
	
		//Ｘ座標の最大値と同じにする
		x = FieldCharacterMap.Num() - kAdjustNumCheckSerch;

		OverMax = true;
	}
}

void ABattleField::CheckYMinOrMax(int x, int& y, bool& OverMin, bool& OverMax){

	//マイナスしてy座標の最小値を下回ったら
	if (y < kYMin) {
		//y座標をyの最小値にする
		y = kYMin;

		OverMin = true;

	}
	//+1をしてy座標の要素数を超えてしまったら
	else if (y >= FieldCharacterMap[x].ArrayOfInnerArray.Num()) {

		//y座標の最大値と同じにする
		y = YMax;

		OverMax = true;
	}
}

bool ABattleField::CheckOutOfXRange(int XRange, int NewX, int OriginX){

	int DifferX = UKismetMathLibrary::Abs(NewX - OriginX);

	if (DifferX < XRange) {
	
		return true;
	}

	return false;
}

bool ABattleField::CheckOutOfYRange(int YRange, int NewY, int OriginY){

	int DifferY = UKismetMathLibrary::Abs(NewY - OriginY);

	if (DifferY < YRange) {

		return true;
	}

	return false;
}

