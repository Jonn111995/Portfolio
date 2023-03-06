// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/BattleLevelDataManager.h"
#include <sstream>
#include <fstream>
#include <map>
#include "Misc/Paths.h"





// Sets default values
ABattleLevelDataManager::ABattleLevelDataManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ABattleLevelDataManager::Initialize(){

    //キャラクターステータスの情報を読み込む
    ReadCharacterData();

    //ステージの情報を読み込む
    ReadFieldData();
   
    //敵のウェーブ情報を読み込む
    ReadWaveInfoData();

    //コストや拠点数などのプレイヤー自身に関わる情報を読み込む
    ReadPlayerStateData();

    //制限時間の情報を読み込む
    ReadGameStateData();

    //ゲーム説明の情報を読み込む
    ReadIntroductionInfoFile();

}

void ABattleLevelDataManager::Finalize()
{
}

void ABattleLevelDataManager::ReadCharacterData(){

    std::string Data;
    std::string ConmmaData;

    std::vector<std::string> CharaInfo;

    FString ProjectPath = FPaths::ProjectDir();
    CharacterListFile = ProjectPath + CharacterListFile;

    // 読み込むcsvファイルを開く(std::ifstreamのコンストラクタで開く)
    std::ifstream IfsCsvFile(*CharacterListFile);

    //読み込みの開始位置を取得
    auto  SartPos = IfsCsvFile.tellg();

    //一行読み込む
    std::getline(IfsCsvFile, Data);

    //一行分のサイズを取得
    auto  FirstLine = IfsCsvFile.tellg();

    //最初の一行分読み込み位置を動かしてから読み込む
    IfsCsvFile.seekg(FirstLine, std::ios_base::beg);

    // getline関数で1行ずつ読み込む(読み込んだ内容はstr_bufに格納)
    while (std::getline(IfsCsvFile, Data)) {
        // 「,」区切りごとにデータを読み込むためにistringstream型にする
        std::istringstream IStream(Data);

        // 「,」区切りごとにデータを読み込む
        while (std::getline(IStream, ConmmaData, ',')) {

            //配列に情報を追加
            CharaInfo.push_back(ConmmaData);
        }

        //キャラクターサイドの変数を宣言
        ABaseCharacter::CharacterSide Side;
        //読み取ったキャラの種類がkPlayerだったら
        if (CharaInfo[0] == "0") {
            //変数にkPlayerを代入
            Side = ABaseCharacter::kPlayer;
        }
        //読み取ったキャラの種類がkEnemyだったら
        else if (CharaInfo[0] == "1") {
            //変数にkEnemyを代入
            Side = ABaseCharacter::kEnemy;
        }

        //intに変換してHPへ
        int Hp = atoi(CharaInfo[1].c_str());
        int Attack = atoi(CharaInfo[2].c_str());
        int Defense = atoi(CharaInfo[3].c_str());
        int XRange = atoi(CharaInfo[4].c_str());
        int YRange = atoi(CharaInfo[5].c_str());
        //floatに変換して攻撃スピードへ
        float AttackSpan = std::stof(CharaInfo[6].c_str());
        float WalkSpeed = std::stof(CharaInfo[7].c_str());
        int TypeId = atoi(CharaInfo[8].c_str());
        int StartSerchRangeNum = atoi(CharaInfo[9].c_str());
        int StopEnemyNum = atoi(CharaInfo[10].c_str());
        float NeedCost = std::stof(CharaInfo[11].c_str());
        float HealCostForDefeating = std::stof(CharaInfo[12].c_str());
        FString IconPath = CharaInfo[13].c_str();

        //構造体を宣言し初期化
        CharacterStruct::CharaStruct CharaInfoStruct{ Side,Hp,Attack,Defense,XRange,YRange,AttackSpan,WalkSpeed,TypeId, StartSerchRangeNum, StopEnemyNum, NeedCost, HealCostForDefeating, IconPath};

        //構造体に入っているキャラの種類がkPlayerなら
        if (CharaInfoStruct.CharaSide == ABaseCharacter::kPlayer) {

            //Playerリストに追加
            PlayerCharacterDataList.Add(CharaInfoStruct);
        }
        //構造体に入っているキャラの種類がkEnemyなら
        else if (CharaInfoStruct.CharaSide == ABaseCharacter::kEnemy) {
            //Enemyリストに追加
            EnemyCharacterDataList.Add(CharaInfoStruct);
        }

        //情報をリセット。しないと前のアイテム情報が残ってしまう
        CharaInfo.clear();

    }
    //CSVファイルを閉じる
    IfsCsvFile.close();
}

void ABattleLevelDataManager::ReadFieldData(){

    //生成するマップチップの情報を読み込む
    ReadMapChipData();

    //マップチップに置かれたときのキャラの向きを規定している情報を読み込む
    ReadMapDirectionData();
   
}

void ABattleLevelDataManager::ReadMapChipData(){

    std::string Data;
    std::string ConmmaData;

    std::vector<std::string> MapInfo;

    FString ProjectPath = FPaths::ProjectDir();
    FieldMapChipFile = ProjectPath + FieldMapChipFile;
    // 読み込むcsvファイルを開く(std::ifstreamのコンストラクタで開く)
    std::ifstream IfsCsvFile(TCHAR_TO_ANSI(*FieldMapChipFile));

    //読み込みの開始位置を取得
    auto  SartPos = IfsCsvFile.tellg();

    //一行読み込む
    std::getline(IfsCsvFile, Data);

    //一行分のサイズを取得
    auto  FirstLine = IfsCsvFile.tellg();

    //最初の一行分読み込み位置を動かしてから読み込む
    IfsCsvFile.seekg(FirstLine, std::ios_base::beg);

    // getline関数で1行ずつ読み込む(読み込んだ内容はstr_bufに格納)
    while (std::getline(IfsCsvFile, Data)) {
        // 「,」区切りごとにデータを読み込むためにistringstream型にする
        std::istringstream IStream(Data);

        // 「,」区切りごとにデータを読み込む
        while (std::getline(IStream, ConmmaData, ',')) {

            //配列に情報を追加
            MapInfo.push_back(ConmmaData);

        }

        //一行分の配列を入れる
        TArray<int> OneLineMapData;
        //一行分の配列のサイズ分配列を回す
        for (int i = 0; i < MapInfo.size(); i++) {

            //stringなのでintに変換して配列に追加
            OneLineMapData.Add(atoi(MapInfo[i].c_str()));
        }

        //追加し終わったら、二次元配列の方へ一行分の配列を入れる
        FieldMapData.Add(OneLineMapData);

        //アイテム情報をリセット。しないと前のアイテム情報が残ってしまう
        MapInfo.clear();

    }
    //CSVファイルを閉じる
    IfsCsvFile.close();
}

void ABattleLevelDataManager::ReadMapDirectionData(){

    std::string Data;
    std::string ConmmaData;

    std::vector<std::string> MapInfo;

    FString ProjectPath = FPaths::ProjectDir();
    FieldDirectionFile = ProjectPath + FieldDirectionFile;

    // 読み込むcsvファイルを開く(std::ifstreamのコンストラクタで開く)
    std::ifstream IfsCsvFile(*FieldDirectionFile);

    //読み込みの開始位置を取得
    auto  SartPos = IfsCsvFile.tellg();

    //一行読み込む
    std::getline(IfsCsvFile, Data);

    //一行分のサイズを取得
    auto  FirstLine = IfsCsvFile.tellg();

    //最初の一行分読み込み位置を動かしてから読み込む
    IfsCsvFile.seekg(FirstLine, std::ios_base::beg);

    // getline関数で1行ずつ読み込む(読み込んだ内容はstr_bufに格納)
    while (std::getline(IfsCsvFile, Data)) {
        // 「,」区切りごとにデータを読み込むためにistringstream型にする
        std::istringstream IStream(Data);

        // 「,」区切りごとにデータを読み込む
        while (std::getline(IStream, ConmmaData, ',')) {

            //配列に情報を追加
            MapInfo.push_back(ConmmaData);

        }

        std::map<std::string, ABattleField::FieldDirection> EnemyTypeEnumMap = {

         {"kNone", ABattleField::FieldDirection::kNone},
          {"kNorth", ABattleField::FieldDirection::kNorth},
          {"kSouth", ABattleField::FieldDirection::kSouth},
          {"kEast", ABattleField::FieldDirection::kEast},
          {"kWest", ABattleField::FieldDirection::kWest}
    
        };

        //一行分の配列を入れる
        TArray<ABattleField::FieldDirection> OneLineMapData;
        //一行分の配列のサイズ分配列を回す
        for (int i = 0; i < MapInfo.size(); i++) {

            OneLineMapData.Add(EnemyTypeEnumMap[MapInfo[i]]);
        }

        //追加し終わったら、二次元配列の方へ一行分の配列を入れる
        FieldDirectionData.Add(OneLineMapData);

        //アイテム情報をリセット。しないと前のアイテム情報が残ってしまう
        MapInfo.clear();

    }
    //CSVファイルを閉じる
    IfsCsvFile.close();
}

void ABattleLevelDataManager::ReadWaveInfoData(){
    
    //1行分のデータを入れる
    std::string Data;
    //1セル毎のデータを入れる
    std::string ConmmaData;

    //読み込んだ敵のWave情報
    std::vector<std::string> WaveInfo;

    //.uprojectファイルがあるディレクトリまでのパスを取得
    FString ProjectPath = FPaths::ProjectDir();
    //取得したパスと.uprojectファイルがある場所からCSVファイルがある
    //フォルダまでのパスが入った変数を足し合わせて、絶対パスを間接的に取得
    EnemyWaveInfoFile = ProjectPath + EnemyWaveInfoFile;

    // 読み込むcsvファイルを開く(std::ifstreamのコンストラクタで開く)
    std::ifstream IfsCsvFile(*EnemyWaveInfoFile);

    //読み込みの開始位置を取得
    auto  SartPos = IfsCsvFile.tellg();

    //一行読み込む
    std::getline(IfsCsvFile, Data);

    //一行分のサイズを取得
    auto  FirstLine = IfsCsvFile.tellg();

    //最初の一行分読み込み位置を動かしてから読み込む
    IfsCsvFile.seekg(FirstLine, std::ios_base::beg);

    // getline関数で1行ずつ読み込む(読み込んだ内容はstr_bufに格納)
    while (std::getline(IfsCsvFile, Data)) {
        // 「,」区切りごとにデータを読み込むためにistringstream型にする
        std::istringstream IStream(Data);

        // 「,」区切りごとにデータを読み込む
        while (std::getline(IStream, ConmmaData, ',')) {

            //空白は飛ばす
            if (ConmmaData != "") {
             
                //配列に情報を追加
                WaveInfo.push_back(ConmmaData);
            }
        }

        //敵WaveのWaveID
        int GroupID = atoi(WaveInfo[0].c_str());

        //このWaveの敵のスポーン位置
        int SpawnPointId = atoi(WaveInfo[1].c_str());

        //ゲーム開始からどれくらいで出現させるか
        float RespawnTime = std::stof(WaveInfo[2].c_str());

        //出現させる敵のIDの配列を入れる
        TArray<int> EnemyIdArray;

        //IDが記されたCSVの列から取得した情報の配列を回す
        for (int i = kEnemyTypeColumnStartNum; i < WaveInfo.size(); i++) {

            //IDを配列に入れていく
            EnemyIdArray.Add(atoi(WaveInfo[i].c_str()));
        }

        //敵のWave情報一つ分の情報を構造体に入れる
        EnemyWaveInfoStruct::WaveInfo Wave{ GroupID, SpawnPointId, RespawnTime, EnemyIdArray };

        //追加し終わったら、構造体配列の方へ一行分のデータを入れる
        EnemyWaveInfoData.Add(Wave);

        //取得した情報をリセット。しないと今回のループの情報が残ってしまう
        WaveInfo.clear();
    }

    //CSVファイルを閉じる
    IfsCsvFile.close();
}

void ABattleLevelDataManager::ReadPlayerStateData(){

    std::string Data;
    std::string ConmmaData;

    std::vector<std::string> PlayerStateInfo;

    FString ProjectPath = FPaths::ProjectDir();
    PlayerStateFile = ProjectPath + PlayerStateFile;

    // 読み込むcsvファイルを開く(std::ifstreamのコンストラクタで開く)
    std::ifstream IfsCsvFile(*PlayerStateFile);

    //読み込みの開始位置を取得
    auto  SartPos = IfsCsvFile.tellg();

    //一行読み込む
    std::getline(IfsCsvFile, Data);

    //一行分のサイズを取得
    auto  FirstLine = IfsCsvFile.tellg();

    //最初の一行分読み込み位置を動かしてから読み込む
    IfsCsvFile.seekg(FirstLine, std::ios_base::beg);

    // getline関数で1行ずつ読み込む(読み込んだ内容はstr_bufに格納)
    while (std::getline(IfsCsvFile, Data)) {
        // 「,」区切りごとにデータを読み込むためにistringstream型にする
        std::istringstream IStream(Data);

        // 「,」区切りごとにデータを読み込む
        while (std::getline(IStream, ConmmaData, ',')) {

            if (ConmmaData != "") {

                //配列に情報を追加
                PlayerStateInfo.push_back(ConmmaData);
            }


        }

        float MaxSpawnCost = std::stof(PlayerStateInfo[0].c_str());
        int PlayerBaseHp = atoi(PlayerStateInfo[1].c_str());

        BattlePlayerStateStruct::PlayerStateData Player{ MaxSpawnCost, PlayerBaseHp };

        //追加し終わったら、二次元配列の方へ一行分の配列を入れる
        PlayerState = Player;

        //アイテム情報をリセット。しないと前のアイテム情報が残ってしまう
        PlayerStateInfo.clear();
    }

    //CSVファイルを閉じる
    IfsCsvFile.close();
}

void ABattleLevelDataManager::ReadGameStateData(){


    std::string Data;
    std::string ConmmaData;

    std::vector<std::string> GameStateInfo;

    FString ProjectPath = FPaths::ProjectDir();
    GameStateFile = ProjectPath + GameStateFile;

    // 読み込むcsvファイルを開く(std::ifstreamのコンストラクタで開く)
    std::ifstream IfsCsvFile(*GameStateFile);

    //読み込みの開始位置を取得
    auto  SartPos = IfsCsvFile.tellg();

    //一行読み込む
    std::getline(IfsCsvFile, Data);

    //一行分のサイズを取得
    auto  FirstLine = IfsCsvFile.tellg();

    //最初の一行分読み込み位置を動かしてから読み込む
    IfsCsvFile.seekg(FirstLine, std::ios_base::beg);

    // getline関数で1行ずつ読み込む(読み込んだ内容はstr_bufに格納)
    while (std::getline(IfsCsvFile, Data)) {
        // 「,」区切りごとにデータを読み込むためにistringstream型にする
        std::istringstream IStream(Data);

        // 「,」区切りごとにデータを読み込む
        while (std::getline(IStream, ConmmaData, ',')) {

            if (ConmmaData != "") {

                //配列に情報を追加
                GameStateInfo.push_back(ConmmaData);
            }


        }

        LimitTime = std::stof(GameStateInfo[0].c_str());

        //BattlePlayerStateStruct::PlayerStateData Player{ MaxSpawnCost };

        //追加し終わったら、二次元配列の方へ一行分の配列を入れる
       // PlayerState = Player;



        //アイテム情報をリセット。しないと前のアイテム情報が残ってしまう
        GameStateInfo.clear();
    }

    //CSVファイルを閉じる
    IfsCsvFile.close();
}

void ABattleLevelDataManager::ReadIntroductionInfoFile() {

    std::string Data;
    std::string ConmmaData;

    std::vector<std::string> PageInfo;
    
    FString ProjectPath = FPaths::ProjectDir();
    IntroductionPageInfoFile = ProjectPath + IntroductionPageInfoFile;
    
    // 読み込むcsvファイルを開く(std::ifstreamのコンストラクタで開く)
    std::ifstream IfsCsvFile(*IntroductionPageInfoFile);
    
    //読み込みの開始位置を取得
    auto  SartPos = IfsCsvFile.tellg();
    
    //一行読み込む
    std::getline(IfsCsvFile, Data);
    
    //一行分のサイズを取得
    auto  FirstLine = IfsCsvFile.tellg();
    
    //最初の一行分読み込み位置を動かしてから読み込む
    IfsCsvFile.seekg(FirstLine, std::ios_base::beg);
    
    // getline関数で1行ずつ読み込む(読み込んだ内容はstr_bufに格納)
    while (std::getline(IfsCsvFile, Data)) {
    // 「,」区切りごとにデータを読み込むためにistringstream型にする
    std::istringstream IStream(Data);
    
    // 「,」区切りごとにデータを読み込む
    while (std::getline(IStream, ConmmaData, ',')) {
    
        //配列に情報を追加
        PageInfo.push_back(ConmmaData);
    }
            
    IntroductionPageInfoStruct::IntroductionPageInfo IntroductionPageInfoStruct;
    
        int Page = atoi(PageInfo[0].c_str());

        FString Text = UTF8_TO_TCHAR(PageInfo[1].c_str());
            
        FString ImagePath = ((TEXT("%s"), PageInfo[2].c_str()));
    
        IntroductionPageInfoStruct.PageNum = Page;
        IntroductionPageInfoStruct.SetText = Text;
        IntroductionPageInfoStruct.ImagePath = ImagePath;
    
        IntroductionPageInfoArray.Push(IntroductionPageInfoStruct);
         
    //情報をリセット。しないと前のアイテム情報が残ってしまう
    PageInfo.clear();
    
    }
    // CSVファイルを閉じる
    IfsCsvFile.close();
}


// Called when the game starts or when spawned
void ABattleLevelDataManager::BeginPlay(){
	Super::BeginPlay();

   
}

// Called every frame
void ABattleLevelDataManager::Tick(float DeltaTime){
	Super::Tick(DeltaTime);


}

