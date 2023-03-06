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

		//キャラのタイプID
		int TypeId;

		//出撃に必要なコスト
		float NeedCost;

		/// <summary>
		/// アイコンに設定するテクスチャ―のパス
		/// </summary>
		FString IconTexture;

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

		//キャラの索敵開始範囲
		int StartSerchRangeNum;

		//キャラを止められる数
		int StopEnemyNum;
	};
};
