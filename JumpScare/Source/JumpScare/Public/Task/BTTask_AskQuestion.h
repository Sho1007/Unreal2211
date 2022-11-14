// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_AskQuestion.generated.h"

/**
 * 
 */
UCLASS()
class JUMPSCARE_API UBTTask_AskQuestion : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ResponseReceive(FText Response);

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private:
	bool PrepareResponse();


public:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BB_DialogueWidget;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BB_Response;
	UPROPERTY(EditAnywhere)
	FText Question;
	UPROPERTY(EditAnywhere)
	TArray<FText> Responses;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UResponseListWidget> ResponseListWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UResponseWidget> ResponseWidgetClass;

	class UDialogueWidget* DW;
	UBehaviorTreeComponent* BTComp;
	UResponseListWidget* RLW;
};
