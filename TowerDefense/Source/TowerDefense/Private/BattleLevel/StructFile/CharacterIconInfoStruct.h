// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class CharacterIconInfoStruct
{
public:
	CharacterIconInfoStruct();
	~CharacterIconInfoStruct();

	struct IconInfo {

		//�L�����̃^�C�vID
		int TypeId;

		//�o���ɕK�v�ȃR�X�g
		float NeedCost;

		/// <summary>
		/// �A�C�R���ɐݒ肷��e�N�X�`���\�̃p�X
		/// </summary>
		FString IconTexture;

		//�L������HP
		int Hp;

		//�L�����̍U����
		int Attack;

		//�L�����̖h���
		int Defense;

		//�L������X�̍��G�͈�
		int XRange;

		//�L������Y�̍��G�͈�
		int YRange;

		//�L�����̍U���X�s�[�h
		float AttackSpan;

		//�L�����̍��G�J�n�͈�
		int StartSerchRangeNum;

		//�L�������~�߂��鐔
		int StopEnemyNum;
	};
};
