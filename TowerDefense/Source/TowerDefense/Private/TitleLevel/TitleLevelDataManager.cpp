//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "TitleLevel/TitleLevelDataManager.h"
//#include <sstream>
//#include <fstream>
//
//// Sets default values
//ATitleLevelDataManager::ATitleLevelDataManager()
//{
// 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = false;
//
//}
//
//void ATitleLevelDataManager::Initialize(){
//
//    ReadCreditTextData();
//}
//
//void ATitleLevelDataManager::Finalize()
//{
//}
//
//void ATitleLevelDataManager::ReadCreditTextData(){
//
//    std::string Data;
//    std::string ConmmaData;
//
//    
//
//    FString ProjectPath = FPaths::ProjectDir();
//    CreditTextDataFile = ProjectPath + CreditTextDataFile;
//
//    // 読み込むcsvファイルを開く(std::ifstreamのコンストラクタで開く)
//    std::ifstream IfsCsvFile(*CreditTextDataFile);
//
//    //読み込みの開始位置を取得
//    auto  SartPos = IfsCsvFile.tellg();
//
//    //一行読み込む
//    std::getline(IfsCsvFile, Data);
//
//    //一行分のサイズを取得
//    auto  FirstLine = IfsCsvFile.tellg();
//
//    //最初の一行分読み込み位置を動かしてから読み込む
//    IfsCsvFile.seekg(FirstLine, std::ios_base::beg);
//
//    // getline関数で1行ずつ読み込む(読み込んだ内容はstr_bufに格納)
//    while (std::getline(IfsCsvFile, Data)) {
//        // 「,」区切りごとにデータを読み込むためにistringstream型にする
//        std::istringstream IStream(Data);
//
//        // 「,」区切りごとにデータを読み込む
//        while (std::getline(IStream, ConmmaData, ',')) {
//
//            //配列に情報を追加
//            TextInfo.push_back(ConmmaData);
//        }
//        
//            CreditTextStruct::CreditText CreditTextStruct;
//
//
//            FString Title = UTF8_TO_TCHAR(TextInfo[0].c_str());
//        
//            FString URL = ((TEXT("%s"), TextInfo[1].c_str()));
//
//            //std::string Title = TextInfo[0];
//
//            //std::string URL = TextInfo[1];
//
//            CreditTextStruct.Title = Title;
//            CreditTextStruct.URLString = URL;
//
//            TextDataArray.Push(CreditTextStruct);
//     
//        //情報をリセット。しないと前のアイテム情報が残ってしまう
//        TextInfo.clear();
//
//    }
//   // CSVファイルを閉じる
//    IfsCsvFile.close();
//}
//
//// Called when the game starts or when spawned
//void ATitleLevelDataManager::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}
//
//// Called every frame
//void ATitleLevelDataManager::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
