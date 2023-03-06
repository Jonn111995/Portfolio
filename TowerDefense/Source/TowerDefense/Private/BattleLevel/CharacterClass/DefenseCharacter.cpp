// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/CharacterClass/DefenseCharacter.h"

void ADefenseCharacter::SetTargetEnemy(ABaseCharacter* chara) {

	//�^�[�Q�b�g�̏���𒴂��Ă����
	if (bIsRimitTarget) {
	
		return;
	}

	if (IsValid(chara)) {

		//�^�[�Q�b�g�G�l�~�[�z��ɂ܂��N�������Ă��Ȃ���΁A
		if (TargetEnemy.Num() == 0) {

			//�������̃L�������^�[�Q�b�g�ɂ���
			TargetEnemy.Add(chara);
		}
		//�^�[�Q�b�g�ɓG�����݂��Ă��āA
		else{

			for (int i = 0; i < TargetEnemy.Num(); i++) {

				if (TargetEnemy.IsValidIndex(i)) {

					if (IsValid(TargetEnemy[i])) {

						//�܂��^�[�Q�b�g�z��Ɉ������̃L���������݂��Ȃ���΁A
						if (TargetEnemy[i] != chara) {

							//�������̃L�������^�[�Q�b�g�ɂ���
							TargetEnemy.Add(chara);

						}
					}
				}
			}

			//�^�[�Q�b�g�̏���ɂȂ�΁A
			if (TargetEnemy.Num() >= StopEnemyNum) {
				//�^�[�Q�b�g�����Ȃ��t���O��ON�ɂ���
				bIsRimitTarget = true;
			}
		}
	}
}

void ADefenseCharacter::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	//�L����������ł�����A���������Ȃ�
	switch(NowStatus){

	case kActive:

		if (NowCharaPhase == APlayerCharacter::PlayerCharaPhase::kBattle) {

			//�^�[�Q�b�g���������łɈ�̈ȏ�͂��āA
			if (TargetEnemy.Num() != 0) {

				//���A�~�߂���G�̐��ɂ܂��]�T������A
				if (bIsNoMoreStopEnemy == false) {

					//����Ƀ^�[�Q�b�g�̔z��ɂ��܂���������
					if (bIsRimitTarget == false) {

						//���G����������
						BaseCharacterInterface->RequestSerchEnemy(this);
					}
				}
			}

		}

		//BaseCharacter��Tick�����s����
		APlayerCharacter::Tick(DeltaTime);

		break;
	}
}
