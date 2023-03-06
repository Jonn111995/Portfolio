// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PlayerBase.h"
#include "../BattleLevel/Interface/BattleGameStateEventInterface.h"
#include "BattleLevelGameState.generated.h"

/**
 * 
 */
UCLASS()
class ABattleLevelGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	/// <summary>
	/// GameState�̃t�F�[�Y
	/// </summary>
	enum GameStatePhase {

		//�����Ȃ�
		kNone,

		//���Ԍv���t�F�[�Y
		kTimer, 

		//�I���t�F�[�Y
		kFinish 
		
	};

	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ABattleLevelGameState();

	/// <summary>
	/// �������_�̔z����Z�b�g
	/// </summary>
	void SetPlayerBaseArray(TArray<APlayerBase*> BaseArray) { PlayerBaseArray = BaseArray; };
	/// <summary>
	/// GameState�̃C���^�[�t�F�[�X
	/// </summary>
	/// <param name="Interface"></param>
	void SetBattleGameStateInterface(IBattleGameStateEventInterface* Interface) { BattleGameStateInterface = Interface; };

	/// <summary>
	/// GameState�̃t�F�[�Y�̃Z�b�^�[
	/// </summary>
	/// <param name="phase"></param>
	void SetPhase(GameStatePhase phase) { NowPhase = phase; };
	GameStatePhase GetPhase() { return NowPhase; };

	/// <summary>
	/// PlayerBase�Ƀ_���[�W��^����
	/// </summary>
	/// <param name="damage">�_���[�W��</param>
	/// <param name="x">�G��X���W</param>
	/// <param name="y">�G��Y���W</param>
	void DamageToBase(int damage,int x, int y);

	/// <summary>
	/// �������Ԃ̊J�n���Ԃ��Z�b�g
	/// </summary>
	/// <param name="time"></param>
	void SetLimitTime(float time) { LimitSeconds = time; };

	/// <summary>
	/// ���݂̎��Ԃ̐������Ԃ̊J�n���Ԃ��Z�b�g����
	/// </summary>
	void StartTimer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	/// <summary>
	/// �������Ԃ̊J�n����
	/// </summary>
	float LimitSeconds;

	/// <summary>
	/// �J�n����
	/// </summary>
	float StartTime;
		
	/// <summary>
	/// ���݂̎���
	/// </summary>
	float NowTime;
	
	/// <summary>
	/// �Q�[�����N���A�������ǂ����̃t���O
	/// </summary>
	bool GameClear = false;

	/// <summary>
	/// �S�Ă̋��_�������Ȃ������Ƃ�����
	/// </summary>
	const int kAllBaseDestroy = 0;

	/// <summary>
	/// �c�莞�Ԃ������Ȃ������Ƃ�����
	/// </summary>
	const float kNoLeftLimitiTime = 0.0f;
		
	/// <summary>
	/// GameState�̌��݂̃t�F�[�Y
	/// </summary>
	GameStatePhase NowPhase;
		
	/// <summary>
	/// �������_�̔z��
	/// </summary>
	TArray<APlayerBase*> PlayerBaseArray;

	/// <summary>
	/// BattleGameState�̃C���^�[�t�F�[�X
	/// </summary>
	IBattleGameStateEventInterface* BattleGameStateInterface;

};
