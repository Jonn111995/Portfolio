//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "Blueprint/UserWidget.h"
//#include "Components/TextBlock.h"
//#include "Components/Image.h"
//#include "Components/CanvasPanel.h"
//#include "Components/Button.h"
//#include "Components/Border.h"
//#include "Widget/CreditScrollBox.h"
//#include "Widget/CreditTextBox.h"
//#include "Interface/CreditWidgetInterface.h"
//#include "StructFile/CreditTextStruct.h"
//#include "CreditWidget.generated.h"
//
///**
// *
// */
//UCLASS()
//class UCreditWidget : public UBaseMainWidget
//{
//	GENERATED_BODY()
//
//public:
//
//	//現在のフェーズ
//	enum  EPhase {
//
//		None,
//
//		Processing
//
//	};
//
//	//メンバ変数
//	//テキストの下敷きとなる部分
//	UPROPERTY(meta = (BindWidget))
//	UBorder* BackImage;
//
//	//テキスト表示ボックス
//	UPROPERTY(meta = (BindWidget))
//	UTextBlock* CreditText;
//
//	//スクロールウィンドウの大きさを決める用のCanvas
//	UPROPERTY(meta = (BindWidget))
//	UCanvasPanel* CanvasPanelForScrollWindow;
//
//	//スクロールウィンドウの大きさ
//	UPROPERTY()
//	FVector2D SizeScrollWindow;
//
//	//スクロールバーの表示の下敷き
//	UPROPERTY(meta = (BindWidget))
//	UImage* BarPlatform;
//
//	//実際にバーが動く部分
//	UPROPERTY(meta = (BindWidget))
//	UImage* BarBody;
//
//	//スクロールウィンドウのYサイズ
//	UPROPERTY()
//	float WindowHeight;
//
//	//テキストボックスのYサイズ
//	UPROPERTY()
//	float TextBlockHeight;
//
//	//スクロールしたときに動く量
//	UPROPERTY()
//	float ScrollHeight;
//
//	//その量を決める値の変数
//	UPROPERTY(EditAnywhere)
//	float AmountOfScroll = 10.0f;
//
//	//スクロールの下限値
//	float ScrollLimit;
//
//	//スクロールが必要かどうかを判断する
//	bool bIsScrollable;
//
//	//テキストを実際にどれくらい動かすかの距離
//	FVector2D DestinationPos;
//
//	//テキストボックスの新しい座標を入れ、そこが移動可能かどうかを確認するための一時変数
//	float TempPos;
//
//	//スクロールバーの位置
//	FVector2D scrollbarpos;
//	//スクロールバーのサイズ
//	FVector2D BarSize;
//
//	//クレジット画面を閉じるためのボタン
//	UPROPERTY(meta = (BindWidget))
//    UButton* CloseButton;
//
//	//見えている範囲の割合を格納する。ウィドウサイズ÷テキストブロックサイズ
//	float ViewRangeRate;
//
//	//一度コンストラクタを実行したことがあるかどうかを判断する
//	bool bIsDoOnceOpenCredit = false;
//
//	//現在のフェーズ
//	EPhase NowPhase = EPhase::None;
//
//	//メンバ関数
//protected:
//
//	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
//	virtual void NativeConstruct() override;
//	virtual void NativeDestruct() override;
//
//public:
//
//	void InitializeCreditWidget();
//
//	UFUNCTION()
//	void OnCloseButton();
//
//	void BindDelegateFunction();
//
//	////クレジット画面を開く
//	//void OpenScrollWidget();
//
//	////クレジット画面を閉じる
//	////UFUNCTIONが無いと、バインドされない
//	//UFUNCTION()
//	//	void CloseScrollWidget();
//
//	//テキストをセットする
//	void InSetText();
//
//	//テキストブロックのサイズを確認し、スクロ―ルが必要かどうか確認
//	void CheckTextBlockSize(FVector2D Size);
//
//	//スクロールの上と下の処理
//	void CalculateGoUp();
//	void CalculateGoDown();
//
//	//実際にスクロールを実行する処理
//	void Scroll();
//
//	//スクロールバーのサイズを計算
//	void SetUpScrollBar();
//
//	//フェーズをUIマネージャーから変更する
//	void SetPhase(EPhase Phase);
//
//	////クレジット画面を閉じる。
//	//void Close();
//
//	void SetText();
//
//	void SetCreditWidgetInterface(ICreditWidgetInterface* Interface) { CreditInterface = Interface; };
//
//	void SetTextDataArray(TArray<CreditTextStruct::CreditText> Array) { TextDataArray = Array; };
//
//	void SetCreditTextBoxWidgetClass(TSubclassOf<UCreditTextBox> TextBoxClass) { CreditTextBoxWidgetClass = TextBoxClass; };
//
//	void SetCreditScrollBoxWidgetPtr(UCreditScrollBox* ScrollBox) { CreditScrollBoxWidgetPtr = ScrollBox; };
//
//	void SetTitleLevelWorld(UWorld* world) { TitleLevelWorld = world; };
//
//	void AddCreditScrollBoxWidgetToMain(UCreditScrollBox* ScrollBox);
//
//private:
//	ICreditWidgetInterface* CreditInterface;
//
//	TArray<CreditTextStruct::CreditText> TextDataArray;
//
//	FString ForSetTextString;
//
//	FText TextForSet;
//
//	std::string ForSetString;
//
//	TArray<FText> FTextArray;
//	TArray<FString> StringTextArray;
//
//	int RimitBoxNum;
//
//	int MaxTextArrayNum;
//
//	float DifferTopFromUnder;
//
//	int NowArrayIndexTopText;
//	int NowArrayIndexUnderText;
//
//	float VerticalY;
//
//	float TextBoxY;
//
//
//	UPROPERTY()
//	UWorld* TitleLevelWorld;
//
//	UPROPERTY()
//	TSubclassOf<UCreditTextBox> CreditTextBoxWidgetClass;
//
//	UPROPERTY()
//	UCreditScrollBox* CreditScrollBoxWidgetPtr;
//
//	UPROPERTY()
//	TArray<UCreditTextBox*> CreditTextBoxArray;
//
//};
