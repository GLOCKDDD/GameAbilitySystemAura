// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	/**
	 * 当PlayerState复制时被触发
	 */
	virtual void OnRep_PlayerState() override;
private:
	/**
	 *将player state中相应的值赋值给character的ASC和AS指针
	 *设置owner actor和avatar actor
	 */
	void InitAbilityActorInfo();
};
