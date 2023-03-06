// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/PlayerBase.h"

// Sets default values
APlayerBase::APlayerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//WidgetComponentを生成する
	HpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBarWIdget"));
	//生成したコンポーネントをアタッチする
	HpBarWidget->SetupAttachment(RootComponent);
	//Widgetの見えかたを設定する
	HpBarWidget->SetWidgetSpace(EWidgetSpace::Screen);

}

void APlayerBase::Initialize(TSubclassOf<class UHpBarWidget> HpBarclass){

	//WidgetComponentで使用するWIdgetクラスを変数にセット
	SetHpBarWidgetClass(HpBarclass);

	//WidgetComponentにセットしたクラスを設定する。
	//コンストラクタでこの処理をしてもクラスのポインタがまだないので、設定されないため、ここで呼び出す。
	HpBarWidget->SetWidgetClass(HpBarWidgetClass);

	//WidgetComponentから使用しているWidgetのポインタを取得、キャストし変数に代入
	UHpBarWidget* widget = Cast<UHpBarWidget>(HpBarWidget->GetWidget());

	//キャストが有効なら、
	if (IsValid(widget)) {

		//最大HPをセットする
		widget->SetMaxHp(BaseHp);

	}
}

bool APlayerBase::GetDamage(int damage){

	//ダメージをHPから引いて現在のHPを更新
	BaseHp -= damage;

	//WidgetComponentから使用しているWidgetのポインタを取得、キャストし変数に代入
	UHpBarWidget* widget = Cast<UHpBarWidget>(HpBarWidget->GetWidget());

	//キャストが有効なら、
	if (IsValid(widget)) {

		//HPを更新する
		widget->UpdateHpBar(BaseHp);

	}

	//もしHPが0以下になれば、
	if (BaseHp <= 0) {
	
		//死んだことを通知
		return true;
	}

	return false;
}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay(){
	Super::BeginPlay();
}

// Called every frame
void APlayerBase::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

