// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTask_StartDialogue.h"
// GetPawn
#include "../../Public/NPC/DialogueAIController.h"
// GetGamemode, GetPlayerController
#include "Kismet/Gameplaystatics.h"
// GetDialogue
#include "../../JumpScareGameModeBase.h"
// SetSpeakerName
#include "../../Public/Widget/DialogueWidget.h"
// GetName
#include "../../Public/NPC/DialogueNPC.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_StartDialogue::UBTTask_StartDialogue()
{
	NodeName = TEXT("StartDialogue");
}

EBTNodeResult::Type UBTTask_StartDialogue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// GetAIOwner() 가 AIController* 반환하기 때문에 AIController 헤더를 추가해줘야함
	ADialogueNPC* NPC = Cast<ADialogueNPC>(OwnerComp.GetAIOwner()->GetPawn());
	if (!ensureMsgf(NPC != nullptr, TEXT("NPC is nullptr"))) return EBTNodeResult::Failed;

	AJumpScareGameModeBase* GM = Cast<AJumpScareGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (ensureMsgf(GM != nullptr, TEXT("GameMode is nullptr")))
	{
		UDialogueWidget* DW = GM->GetDialogueWidget();
		DW->SetSpeakerName(NPC->GetNPCName());
		DW->SetDialogueText(FText::FromName(" "));
		DW->SetVisibility(ESlateVisibility::Visible);
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(BB_DialogueWidget.SelectedKeyName, DW);
	}
	else EBTNodeResult::Failed;

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (ensureMsgf(PC != nullptr, TEXT("PC is nullptr")))
	{
		PC->SetShowMouseCursor(true);
		PC->GetCharacter()->DisableInput(PC);
	}
	else EBTNodeResult::Failed;
	return EBTNodeResult::Succeeded;
}
