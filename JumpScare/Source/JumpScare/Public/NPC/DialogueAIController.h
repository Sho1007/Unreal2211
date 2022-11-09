// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DialogueAIController.generated.h"

/**
 * 
 */
UCLASS()
class JUMPSCARE_API ADialogueAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void StartDialouge();
	UFUNCTION(BlueprintCallable)
	void EndDialogue();

	void SetBTAsset(class UBehaviorTree* Value) { BTAsset = Value; }
	void SetBBAsset(class UBlackboardData* Value) { BBAsset = Value; }
	
private:
	UPROPERTY(meta = (AllowPrivateAccess = true), BlueprintReadWrite)
	UBehaviorTree* BTAsset;
	UPROPERTY(meta = (AllowPrivateAccess = true), BlueprintReadWrite)
	UBlackboardData* BBAsset;

	static const FName BB_Key_Response;
	static const FName BB_Key_DialogueWidget;
};
