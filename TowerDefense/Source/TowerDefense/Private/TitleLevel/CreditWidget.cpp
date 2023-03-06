//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "TitleLevel/CreditWidget.h"
//#include "Kismet/GamePlayStatics.h"
//#include "Blueprint/WidgetLayoutLibrary.h"
//#include "Components/CanvasPanel.h"
//#include "Components/CanvasPanelSlot.h"
//#include "Components/Button.h"
//#include "TitleLevelMainWidgetManager.h"
//#include "../../Public/TowerDefenseGameInstance.h"
//#include "Kismet/KismetMathLibrary.h"
//
//void UCreditWidget::NativeConstruct() {
//
//	Super::NativeConstruct();
//
//	////消したり開いたりするので、何度もコンストラクタを実行させないようにする
//	//if (bIsDoOnceOpenCredit == false) {
//
//	//	//スクロールウィンドウのサイズを取得する。
//	//	SizeScrollWindow = UWidgetLayoutLibrary::SlotAsCanvasSlot(CanvasPanelForScrollWindow)->GetSize();
//
//	//	//上のY軸のサイズを変数に格納
//	//	WindowHeight = SizeScrollWindow.Y;
//
//	//	//一回の処理でどれくらいスクロールするかを決める。
//	//	//ウィンドウサイズを任意の値で割った分動かす。
//	//	ScrollHeight = WindowHeight / AmountOfScroll;
//
//	//	//その行の中のTextという列名のデータを取得し、テキストボックスにセットする用の変数に、値を格納する。
//	//	//TextForSet = ScrollMessage->Text;
//
//	//	//スクロールウィンドウのテキストボックスに抽出したテキストデータをセットする。
//	//	//InSetText();
//	////	SetText();
//
//	//NowPhase = Processing;
//	//	//もう実行されないように、一回実行したことを示す真偽値をtrueにする。
//	//	bIsDoOnceOpenCredit = true;
//
//	//}
//}
//
////デストラクタ
//void UCreditWidget::NativeDestruct() {
//	Super::NativeDestruct();
//}
//
////毎フレーム処理。
//void UCreditWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
//
//	Super::NativeTick(MyGeometry, InDeltaTime);
//
//	//処理中フェーズ
//	switch (NowPhase) {
//
//	case EPhase::Processing:
//
//		if (bIsScrollable == true) {
//
//			//W,上矢印、上スクロールをしたら、GoUp
//
//			//S,下矢印、下スクロースをしたらGoDown
//
//			//常に実行し、上や下スクロールが実行されたら、即座にテキストの位置を変更する。
//			//Scrollをする
//			Scroll();
//
//		}
//		break;
//	}
//}
//
//void UCreditWidget::InitializeCreditWidget(){
//
//	//スクロールウィンドウのサイズを取得する。
//	SizeScrollWindow = UWidgetLayoutLibrary::SlotAsCanvasSlot(CanvasPanelForScrollWindow)->GetSize();
//
//	//上のY軸のサイズを変数に格納
//	WindowHeight = SizeScrollWindow.Y;
//
//	//一回の処理でどれくらいスクロールするかを決める。
//	//ウィンドウサイズを任意の値で割った分動かす。
//	ScrollHeight = WindowHeight / AmountOfScroll;
//
//	SetText();
//
//	InSetText();
//
//	SetUpScrollBar();
//
//	NowPhase = Processing;
//}
//
//void UCreditWidget::OnCloseButton(){
//
//	CreditInterface->RequestOpenMainWidget();
//}
//
//void UCreditWidget::BindDelegateFunction(){
//
//	//閉じるボタンを押したときに実行される関数をバインドする。
//	CloseButton->OnClicked.AddDynamic(this, &UCreditWidget::OnCloseButton);
//
//}
//
//
////ウィンドウのテキストを設定する。
////テキストはCSVと連携したデータテーブルから取得している
//void UCreditWidget::InSetText() {
//
//
//	////for (int i = 0; i < FTextArray.Num(); i++) {
//
//	////	if (IsValid(CreditTextBoxWidgetClass)) {
//
//	////		CreditTextBoxWidgetを生成
//	////		UUserWidget* Widget = CreateWidget(TitleLevelWorld, CreditTextBoxWidgetClass);
//	////		UCreditTextBoxにキャスト
//	////		UCreditTextBox* CreditTextTemp = Cast<UCreditTextBox>(Widget);
//
//	////		if (IsValid(CreditTextTemp)) {
//	////			生成したTextBoxにテキストをセット
//	////			CreditTextTemp->SetTextToBox(FTextArray[i]);
//	////			生成したものをWidgetの配列に入れる
//	////			CreditTextBoxArray.Push(CreditTextTemp);
//	////		}
//
//	////	}
//	////}
//
//
//	for (int i = 0; i < StringTextArray.Num(); i++) {
//	
//		ForSetTextString += StringTextArray[i];
//	}
//
//	CreditText->SetText(FText::FromString(ForSetTextString));
//
//	TextBlockHeight = CreditText->GetDesiredSize().Y;
//
//	ForSetTextString = "";
//
//	for (int i = 0; i < StringTextArray.Num(); i++) {
//	
//	
//		ForSetTextString += StringTextArray[i];
//
//		CreditText->SetText(FText::FromString(ForSetTextString));
//
//		if (CreditText->GetDesiredSize().Y > WindowHeight) {
//		
//			//超えていたらスクロール出来るフラグを立てる
//			bIsScrollable = true;
//
//		//スクロールの限界を決める。
//		//先頭から、テキストブロックのサイズからCanvasのサイズを引いた分までスクロール出来るようにする。
//			ScrollLimit = 0.0f - (TextBlockHeight - WindowHeight);
//
//			//一番上のテキストWidgetの配列の要素番号
//			NowArrayIndexTopText = 0;
//
//			//現在の一番下のテキストWIdgetの配列の要素数を保持。
//			NowArrayIndexUnderText = i;
//
//			DifferTopFromUnder = UKismetMathLibrary::Abs(NowArrayIndexTopText - NowArrayIndexUnderText);
//
//			//何ボックス表示出来るか最大数を保存
//			RimitBoxNum = i;
//
//
//			break;
//		
//		
//		}
//
//	
//	}
//
//
//	///*スクロールボックスにTextWidgetの配列を渡す
//	//CreditScrollBoxWidgetPtr->SetCreditTextBoxArray(CreditTextBoxArray);
//
//	//TextWidgetの最大数を取得。
//	//MaxTextArrayNum = CreditTextBoxArray.Num();
//
//	//TextBoxY = CreditTextBoxArray[0]->GetTextBlokYSize();
//
//	//for (int i = 0; i < MaxTextArrayNum; i++) {
//
//	//	スクロールボックスのVertivcalBoxに生成したTextWidgetを一つずつ入れていく。
//	//	CreditScrollBoxWidgetPtr->SetCreditTextBlockToVertical(CreditTextBoxArray[i]);
//	//	VerticalY = TextBoxY * (i + 1);
//	//	入れたらVerticalBoxのサイズが変わるので、そのサイズが、表示サイズを超えていないか確認する。
//	//	if (WindowHeight <= VerticalY) {
//	//	
//	//		超えていたらスクロール出来るフラグを立てる
//	//		bIsScrollable = true;
//
//
//
//	//		一番上のテキストWidgetの配列の要素番号
//	//		NowArrayIndexTopText = 0;
//
//	//		現在の一番下のテキストWIdgetの配列の要素数を保持。
//	//		NowArrayIndexUnderText = i;
//
//	//		DifferTopFromUnder = UKismetMathLibrary::Abs(NowArrayIndexTopText - NowArrayIndexUnderText);
//
//	//		何ボックス表示出来るか最大数を保存
//	//		RimitBoxNum = i;
//	//		
//
//	//		break;
//	//	}
//	//}*/
//
//	////テキスト内容をセット
//	//CreditText->SetText(TextForSet);
//
//	//CreditText->ForceLayoutPrepass();
//	////テキストを設定後の、テキストブロックのサイズを取得し、スクロールするべきか確認する。
//	//CheckTextBlockSize(CreditText->GetDesiredSize());
//
//
//}
//
////スクロールするべきかどうかをテキストブロックのサイズから確認する。
//void UCreditWidget::CheckTextBlockSize(FVector2D Size) {
//
//	//Y軸のサイズを取得。
//	TextBlockHeight = Size.Y;
//
//	//テキストブロックのサイズが、テキストブロックの親であるCanvasより大きければ、
//	if (TextBlockHeight >= WindowHeight) {
//
//		//スクロール出来るようにする
//		bIsScrollable = true;
//
//		//スクロールの限界を決める。
//		//先頭から、テキストブロックのサイズからCanvasのサイズを引いた分までスクロール出来るようにする。
//		ScrollLimit = 0.0f - (TextBlockHeight - WindowHeight);
//	}
//	else {
//
//		bIsScrollable = false;
//	}
//
//}
//
////上へのスクロール処理
//void UCreditWidget::CalculateGoUp() {
//
//	/*if (bIsScrollable) {
//		bool IsRimitUp = false;
//
//		NowArrayIndexTopText -= 1;
//
//		if (NowArrayIndexTopText < 0) {
//
//			NowArrayIndexTopText = 0;
//			IsRimitUp = true;
//		}
//
//		if (!IsRimitUp) {
//			CreditScrollBoxWidgetPtr->AddTextToTop(NowArrayIndexTopText);
//			CreditScrollBoxWidgetPtr->RemoveUnderText(NowArrayIndexUnderText);
//
//			if (!(DifferTopFromUnder < UKismetMathLibrary::Abs(NowArrayIndexUnderText - NowArrayIndexUnderText))) {
//
//				NowArrayIndexUnderText -= 1;
//			}
//
//
//		}
//
//	}*/
//	//スクロールの動かす距離を足す。
//	DestinationPos.Y += ScrollHeight;
//
//	//それを一旦別の変数へ
//	TempPos = DestinationPos.Y;
//
//	//その値が、プラスになったら０にする。
//
//	//先頭が０なので、それ以上上には行かせないようにする。
//	if (TempPos >= 0.0f) {
//
//		TempPos = 0.0f;
//	}
//
//	//目的地と一時変数を同じ値にする。
//	DestinationPos.Y = TempPos;
//}
//
////下スクロールの位置を計算する
//void UCreditWidget::CalculateGoDown() {
//
//	//bool IsRimitDown = false;
//
//	//if (bIsScrollable) {
//
//	//	NowArrayIndexUnderText += 1;
//
//	//	if (NowArrayIndexUnderText >= CreditTextBoxArray.Num()) {
//
//	//		NowArrayIndexUnderText = CreditTextBoxArray.Num();
//	//		IsRimitDown = true;
//
//	//	}
//
//	//	if (!IsRimitDown) {
//	//		CreditScrollBoxWidgetPtr->AddTextToUnder(NowArrayIndexUnderText);
//	//		CreditScrollBoxWidgetPtr->RemoveTopText(NowArrayIndexTopText);
//
//	//		if (!(DifferTopFromUnder < UKismetMathLibrary::Abs(NowArrayIndexUnderText - NowArrayIndexUnderText))) {
//	//			NowArrayIndexTopText += 1;
//	//		}
//
//	//	}
//	//}
//	//スクロールの動かす距離を引く。
//	DestinationPos.Y -= ScrollHeight;
//
//	//それを一旦別の変数に入れて、
//	TempPos = DestinationPos.Y;
//
//	//それがスクロールの限界になったら、
//	//スクロールの限界値はマイナスの値になっている。
//	if (TempPos <= ScrollLimit) {
//
//		//限界の値と同じにする。それ以上下には行かせない。
//		TempPos = ScrollLimit;
//
//	}
//
//	DestinationPos.Y = TempPos;
//}
//
////スクロールを実行する関数
//void UCreditWidget::Scroll() {
//
//	//現在のテキストボックスの座標を取得する。
//	FVector2D NowPosition = UWidgetLayoutLibrary::SlotAsCanvasSlot(CreditText)->GetPosition();
//
//	//計算した動かす距離から現在の座標を引いて、目的の座標を計算する。
//	//それに0.1かけることで、少しずつその目的地に動かす。
//	//毎フレーム呼んでいるので少しずつ動く。
//	//掛けないと一期に移動する。
//	NowPosition += ((DestinationPos - NowPosition) * 0.1f);
//
//	//その座標をセットする
//	UWidgetLayoutLibrary::SlotAsCanvasSlot(CreditText)->SetPosition(NowPosition);
//
//	//スクロールバーの座標も変える。目的の座標に見えている範囲を掛ける。
//	scrollbarpos = NowPosition * (ViewRangeRate * -1.0f);
//
//	//計算した値をセットする。
//	UWidgetLayoutLibrary::SlotAsCanvasSlot(BarBody)->SetPosition(scrollbarpos);
//
//}
//
////スクロールバーの大きさを計算する処理
//void UCreditWidget::SetUpScrollBar() {
//
//	//UWidgetLayoutLibrary::SlotAsCanvasSlot(BarBody)->GetSize().X;
//
//	//スクロールウィジェットのテキストが全体のどれくらい表示されているかを計算する
//	ViewRangeRate = WindowHeight / TextBlockHeight;
//
//	//スクロールバーの横サイズを取得する。
//	float BarSizeX = UWidgetLayoutLibrary::SlotAsCanvasSlot(BarBody)->GetSize().X;
//
//	//バーの大きさを計算する。
//	BarSize = FVector2D(BarSizeX, (ViewRangeRate * WindowHeight));
//
//	//計算した大きさを設定する。
//	UWidgetLayoutLibrary::SlotAsCanvasSlot(BarBody)->SetSize(BarSize);
//}
//
////フェーズをUIマネージャーから変更する
//void UCreditWidget::SetPhase(EPhase Phase) {
//
//	NowPhase = Phase;
//}
//
//void UCreditWidget::SetText(){
//
//
//	for (int i = 0; i < TextDataArray.Num(); i++) {
//		
//		//std::string string = TextDataArray[i].Title;
//		ForSetTextString = TextDataArray[i].Title + " " + TextDataArray[i].URLString + "\n";
//		StringTextArray.Push(ForSetTextString);
//
//		TextForSet = FText::FromString(ForSetTextString);
//		FTextArray.Push(TextForSet);
//	}
//}
//
//void UCreditWidget::AddCreditScrollBoxWidgetToMain(UCreditScrollBox* ScrollBox) {
//
//	CanvasPanelForScrollWindow->AddChildToCanvas(ScrollBox);
//
//}