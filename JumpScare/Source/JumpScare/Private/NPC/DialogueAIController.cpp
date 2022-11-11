// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/DialogueAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ADialogueAIController::BB_Key_Response(TEXT("Response"));
const FName ADialogueAIController::BB_Key_DialogueWidget(TEXT("DialogueWidget"));

void ADialogueAIController::StartDialouge()
{
	UBlackboardComponent* BC = Blackboard;
	if (ensureMsgf(UseBlackboard(BBAsset, BC), TEXT("BBAsset is not valid!")))
	{
		if (ensureMsgf(RunBehaviorTree(BTAsset), TEXT("BTAsset is not valid!")))
		{
			RunBehaviorTree(BTAsset);
		}
	}
}

void ADialogueAIController::EndDialogue()
{
	UBehaviorTreeComponent* BTC = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTC)
		BTC->StopLogic(FString());
		//BTC->StopTree();
}