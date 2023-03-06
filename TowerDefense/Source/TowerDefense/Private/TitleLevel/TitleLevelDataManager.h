//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
//#include <vector>
//#include "Misc/Paths.h"
//#include "StructFile/CreditTextStruct.h"
//#include "TitleLevelDataManager.generated.h"
//
//UCLASS()
//class ATitleLevelDataManager : public AActor
//{
//	GENERATED_BODY()
//	
//public:	
//	// Sets default values for this actor's properties
//	ATitleLevelDataManager();
//
//	/// <summary>
//	/// 各ファイルの読み込みを行う関数を呼ぶ
//	/// </summary>
//	void Initialize();
//	/// <summary>
//	/// 配列のアイテムのポインタの削除と配列の削除を行う
//	/// </summary>
//	void Finalize();
//
//	TArray<CreditTextStruct::CreditText> GetTextDataArray() { return TextDataArray; };
//
//private:
//	void ReadCreditTextData();
//
//	TArray<CreditTextStruct::CreditText> TextDataArray;
//
//	FString CreditTextDataFile = "CreditTextDataFile.csv";
//
//	std::vector<std::string> TextInfo;
//
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//};
