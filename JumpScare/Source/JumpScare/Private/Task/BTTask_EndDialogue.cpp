// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTask_EndDialogue.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Public/Widget/DialogueWidget.h"
#include "../../Public/NPC/DialogueAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UBTTask_EndDialogue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UDialogueWidget* DW =  Cast<UDialogueWidget>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BB_DialogueWidget.SelectedKeyName));

	if (!ensureMsgf(DW != nullptr, TEXT("DialogueWidget is nullptr"))) return EBTNodeResult::Failed;

	DW->SetVisibility(ESlateVisibility::Hidden);

	ADialogueAIController* DAC = Cast<ADialogueAIController>(OwnerComp.GetAIOwner());

	if (!(ensureMsgf(DAC != nullptr, TEXT("AI Controller is nullptr")))) return EBTNodeResult::Failed;

	DAC->EndDialogue();

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	PC->SetShowMouseCursor(false);
	
	UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->EnableInput(PC);

	return EBTNodeResult::Succeeded;
}
