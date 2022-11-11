// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_DisplayLine.generated.h"

/**
 * 
 */
UCLASS()
class JUMPSCARE_API UBTTask_DisplayLine : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_DisplayLine(const FObjectInitializer& objectInitializer);
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
public:
	UPROPERTY(EditAnywhere)
	FText Text;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BB_DialogueWidget;

	bool isEPressed = false;
};
