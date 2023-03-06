// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/BattleLevelGameState.h"

ABattleLevelGameState::ABattleLevelGameState() {

 PrimaryActorTick.bCanEverTick = true;

 NowPhase = kNone;

}


void ABattleLevelGameState::BeginPlay() {
	 Super::BeginPlay();
}

void ABattleLevelGameState::Tick(float DeltaTime) {
		
	Super::Tick(DeltaTime);
	//�o�ߎ��Ԃ����邽�ߏ�����
	float PassedTime = 0.0f;

	switch (NowPhase) {

	case kTimer:
		//���݂̎��Ԃ��疈�t���[���̎��Ԃ�����
		NowTime = NowTime - DeltaTime;

		//�c�莞�Ԃ�0�ł���΁A
		if (NowTime <= kNoLeftLimitiTime) {
		
			//���݂̎��Ԃ�0�ɂ��āA
			NowTime = kNoLeftLimitiTime;
			//�N���A�̃t���O�𗧂Ă�
			GameClear = true;
		
		}

		//�J�n���牽�b�����������v�Z
		PassedTime = LimitSeconds - NowTime;

		//�o�ߎ��ԂƖ��t���[�����Ԃ�n���āA�X�|�[���������Ă�
		BattleGameStateInterface->RequestGiveTickTimetToEnemySpawnerManager(PassedTime, DeltaTime);
		//���݂̎��Ԃ�Widget�̕��ɓn�����߁A�C�x���g�ʒm
		BattleGameStateInterface->RequestGiveUpdateTime(NowTime);

		//�Q�[���N���A�����Ă���΁A
		if (GameClear) {
			
			//�N���A�̃C�x���g�ʒm������
			BattleGameStateInterface->RequestGameClear();
				
		}

		break;

	//�I���t�F�[�Y�B�Ȃɂ������Ȃ�
	case kFinish:

		break;
	}
}


void ABattleLevelGameState::DamageToBase(int damage, int x, int y){

	//�������_�̔z�����
	for (int i = 0; i < PlayerBaseArray.Num(); i++) {
	
		//�������_�̍��W��n��
		int BaseX = PlayerBaseArray[i]->GetXPoint();
		int BaseY = PlayerBaseArray[i]->GetYPoint();

		//�������_�̍��W�ƈ������̓G�̍��W����v����΁A
		if (BaseX == x && BaseY == y) {
		
			//���_�Ƀ_���[�W��^����
			bool IsDead = PlayerBaseArray[i]->GetDamage(damage);

			//���_��HP�������Ȃ�����B
			if (IsDead) {
			
				//�Q�[���}�l�[�W���\�ɍ폜�˗����s���B
				BattleGameStateInterface->RequestDeletePlayerBaseActor(PlayerBaseArray[i]);
			
				//�폜�����A�N�^�[�̃|�C���^���폜
				PlayerBaseArray.RemoveAt(i);
			}

			//���_���S�ł����
			if (PlayerBaseArray.Num() == kAllBaseDestroy) {
				
				//�Q�[���I�[�o�[�̃C�x���g�ʒm���s��
				BattleGameStateInterface->RequestGameOver();
					
			}
		}
	}
}

void ABattleLevelGameState::StartTimer() {

	//���݂̎��Ԃɐ������Ԃ����ď���������
	NowTime = LimitSeconds;

}
