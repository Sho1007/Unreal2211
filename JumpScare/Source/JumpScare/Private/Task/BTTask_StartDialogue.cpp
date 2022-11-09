// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTask_StartDialogue.h"
#include "../../Public/NPC/DialogueAIController.h"
#include "Kismet/Gameplaystatics.h"

UBTTask_StartDialogue::UBTTask_StartDialogue()
{
	NodeName = TEXT("StartDialogue");
}

EBTNodeResult::Type UBTTask_StartDialogue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// GetAIOwner() 가 AIController* 반환하기 때문에 AIController 헤더를 추가해줘야함
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ensureMsgf(ControllingPawn != nullptr, TEXT(""))) return EBTNodeResult::Failed;

	UGameplayStatics::GetGameMode(GetWorld());

	return EBTNodeResult::Type();
}
