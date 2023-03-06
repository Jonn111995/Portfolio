// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/BaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//コンポーネントを生成
	HpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBarWIdget"));
	//生成したコンポーネントをアタッチする
	HpBarWidget->SetupAttachment(GetMesh());
	//HpBarWidget->SetWidgetClass(HpBarWidgetClass);
	//Widgetの見え方を設定
	HpBarWidget->SetWidgetSpace(EWidgetSpace::Screen);

	NiagaraAttachedComp = CreateDefaultSubobject<USceneComponent>(TEXT("AttachedComp"));
	NiagaraAttachedComp->SetupAttachment(GetMesh());
	//UArrowComponent* arrow = GetArrowComponent();

    ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow2"));
	ArrowMesh->SetupAttachment(GetMesh());
	ArrowMesh->SetVisibility(false);

	//arrow->SetHiddenInGame(false);
//	arrow->ArrowLength = GetDistanceTo(TargetEnemy[kFirstAttackEnemyIndex]);
	//arrow->ArrowColor = FColor::Red;
	
}

void ABaseCharacter::SetTargetEnemy(ABaseCharacter* chara) {

	//ターゲットエネミー配列にまだ誰も入っていなければ、
	if (TargetEnemy.Num() == 0) {

		//引き数のキャラをターゲットにする
		TargetEnemy.Add(chara);

		bIsRimitTarget = true;
	}
}

ABaseCharacter* ABaseCharacter::GetTargetEnemy() {

	if (TargetEnemy.IsValidIndex(kFirstAttackEnemyIndex)) {

		return TargetEnemy[kFirstAttackEnemyIndex];
	}
	return nullptr;
}

bool ABaseCharacter::GiveDamage() {

	//配列の0番目を優先で攻撃したいので、0指定にしている
	//有効であれば、
	if (TargetEnemy.IsValidIndex(kFirstAttackEnemyIndex)) {

		//かつポインタが有効であれば、
		if (IsValid(TargetEnemy[kFirstAttackEnemyIndex])) {

			//キャラのステータスが死亡で無ければ、
			if (TargetEnemy[kFirstAttackEnemyIndex]->GetCharacterStatus() != ABaseCharacter::kDead) {

				//ターゲットの防御力を取得する
				int EnemyDefense = TargetEnemy[kFirstAttackEnemyIndex]->GetDefense();

				//自身の攻撃力から防御力を引いて、ダメージ量を計算
				int Damage = AttackNum - EnemyDefense;

				//そのダメージ量が0だったらダメージをあたえずに処理を終了
				if (Damage <= 0) {

					return false;
				}
				//そうでなければ、
				else {
					//UArrowComponent* arrow = GetArrowComponent();
					//arrow->ArrowLength = GetDistanceTo(TargetEnemy[kFirstAttackEnemyIndex]);
					
					//arrow->ArrowLength = 999;
					//arrow->SetEditorScale(100);

					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, TargetEnemy[kFirstAttackEnemyIndex]->GetActorLocation(),FRotator(0), FVector(0.3f,0.3f,0.3f));

					if (FireEffectMuzzle) {

						//エフェクトを飛ばす方向。自身と同じ向きの方向へ飛ばす
						FRotator Direction = GetActorRotation();
						
						//Niagaraエフェクトをワールドにスポーン
						NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(FireEffectMuzzle, GetMesh(), NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true, true);
						
						//NiagaraのDirection変数の値を、キャラの回転値*速度の値にする
						NiagaraComp->SetNiagaraVariableVec3(FString("Direction"), Direction.Vector() * 400.0f);
						//NiagaraComp->SetNiagaraVariableVec3(FString("ArrowEffectRotation"), GetActorRotation().Vector());

					}

					//計算したダメージ量をターゲットに渡す。
					//キャラが死亡したかどうかをboolで返している。
					//trueであれば死亡している。
					bool CheckDeadEnemy = TargetEnemy[kFirstAttackEnemyIndex]->GetDamage(Damage, TargetEnemy[kFirstAttackEnemyIndex]);

					if (CheckDeadEnemy) {

						if (IsValid(NiagaraComp)) {

							NiagaraComp->DestroyInstance();
						}
					}

					return CheckDeadEnemy;
				}
				return false;
			}
			else {

				return true;
			}
		}
		else {
		
			return true;
		}
	}
	return false;
}

bool ABaseCharacter::GetDamage(int damage, ABaseCharacter* Target) {

	//貰ったダメージ量を現在のHPから引いて、現在のHPを計算
	HP -= damage;

	//WidgetComponentから使用しているWidgetを取得し、それをキャストして変数に保存
	//こうすることで、そのWIdgetの関数や変数が使える
	UHpBarWidget* widget = Cast<UHpBarWidget>(HpBarWidget->GetWidget());


	//キャストが成功していれば
	if (IsValid(widget)) {
	
		//HpBarWidgetクラスのHp更新関数を呼び出す。
		widget->UpdateHpBar(HP);
	
	}

	//HPが0になったら、
	if (HP <= 0) {

		bIsAttackToEnemy = false;
		//bIsDeadAnimation = true;
		//キャラのステータスを死亡状態にする
		NowStatus = kDead;

		//if (IsValid(this)) {
		//	
		//	//ここでゲームモードにイベント通知を行って、Fieldのマップのポインタ削除と、スポナーに削除依頼を行う
		//	BaseCharacterInterface->RequestDeleteCharacter(this);

		//	
		//}
		//終わったらtrueを返して、死亡したことを示す
		return true;
	}

	return false;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	//WidgetComponentから使用しているWidgetを取得し、それをキャストして変数に保存
	//こうすることで、そのWIdgetの関数や変数が使える
	UHpBarWidget* widget = Cast<UHpBarWidget>(HpBarWidget->GetWidget());

	//キャストが成功していたら
	if (IsValid(widget)) {

		//ウィジェットの最大HPをセット。
		widget->SetMaxHp(HP);
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){

	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


//void ABaseCharacter::CreateMesh() {
//
//	Vertices.Add(FVector(-50, 0, 50));
//	Vertices.Add(FVector(-50, 0, -50));
//	Vertices.Add(FVector(50, 0, 50));
//	Vertices.Add(FVector(50, 0, -50));
//
//	UVs.Add(FVector2D(0, 0));
//	UVs.Add(FVector2D(0, 1));
//	UVs.Add(FVector2D(1, 0));
//	UVs.Add(FVector2D(1, 1));
//
//	//Triangle1
//	Triangles.Add(0);
//	Triangles.Add(1);
//	Triangles.Add(2);
//
//	//Triangle2
//	Triangles.Add(2);
//	Triangles.Add(1);
//	Triangles.Add(3);
//
//	ProcMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UVs, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
//
//	if (Material)
//	{
//		ProcMesh->SetMaterial(0, Material);
//	}
//
//}
//
//
