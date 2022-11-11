// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTask_DisplayLine.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Public/Widget/DialogueWidget.h"
#include "Kismet/GameplayStatics.h"

UBTTask_DisplayLine::UBTTask_DisplayLine(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_DisplayLine::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UDialogueWidget* DW = Cast<UDialogueWidget>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BB_DialogueWidget.SelectedKeyName));
	if (!ensureMsgf(DW != nullptr, TEXT("DialogueWidget is nullptr"))) EBTNodeResult::Failed;
	DW->SetDialogueText(Text);
	return EBTNodeResult::InProgress;
}

void UBTTask_DisplayLine::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->WasInputKeyJustPressed(EKeys::E))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
