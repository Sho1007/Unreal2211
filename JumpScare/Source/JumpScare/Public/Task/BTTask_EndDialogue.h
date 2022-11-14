// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_EndDialogue.generated.h"

/**
 * 
 */
UCLASS()
class JUMPSCARE_API UBTTask_EndDialogue : public UBTTaskNode
{
	GENERATED_BODY()
	
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BB_DialogueWidget;
};