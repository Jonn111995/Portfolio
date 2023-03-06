// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <string>
#include "BaseCharacter.h"

/**
 * 
 */
class CharacterStruct{

public:
	CharacterStruct();
	~CharacterStruct();

public:

  struct CharaStruct {

  public:
	//キャラクターが敵か味方かどうか
	ABaseCharacter::CharacterSide CharaSide;

	//キャラのHP
	int Hp;

	//キャラの攻撃力
	int Attack;

	//キャラの防御力
	int Defense;

	//キャラのXの索敵範囲
	int XRange;

	//キャラのYの索敵範囲
	int YRange;

	//キャラの攻撃スピード
	float AttackSpan;

	//キャラの歩くスピード
	float WalkSpeed;

	//キャラのタイプID
	int TypeId;

	//キャラの索敵開始範囲
	int StartSerchRangeNum;

	//キャラを止められる数
	int StopEnemyNum;

	//出撃に必要なコスト
	float NeedCost;

	//倒されたときに回復するコスト量
	float HealCostForDefeating;

	//味方キャラのアイコン画像のパス
	FString IconPath;

  };

};
