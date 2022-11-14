// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTask_AskQuestion.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Public/Widget/DialogueWidget.h"
#include "../../Public/Widget/ResponseListWidget.h"

#include "Kismet/GameplayStatics.h"

void UBTTask_AskQuestion::ResponseReceive(FText Response)
{
    BTComp->GetBlackboardComponent()->SetValueAsString(BB_Response.SelectedKeyName, Response.ToString());
    FInputModeGameOnly InputMode;
    UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(InputMode);
    RLW->RemoveFromParent();

    FinishLatentTask(*BTComp, EBTNodeResult::Succeeded);
}

EBTNodeResult::Type UBTTask_AskQuestion::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    BTComp = &OwnerComp;
    DW = Cast<UDialogueWidget>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BB_DialogueWidget.SelectedKeyName));

    if (!ensureMsgf(DW != nullptr, TEXT("DialogueWidget is nullptr"))) EBTNodeResult::Failed;

    DW->SetDialogueText(Question);

    PrepareResponse();

    FInputModeUIOnly InputMode;
    InputMode.SetWidgetToFocus(RLW->TakeWidget());
    return EBTNodeResult::InProgress;
}

bool UBTTask_AskQuestion::PrepareResponse()
{

    RLW = CreateWidget<UResponseListWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), ResponseListWidgetClass);

    if (!ensureMsgf(RLW != nullptr, TEXT("ResponseWidget is nullptr"))) return false;

    DW->GetResponseListPanel()->AddChildToOverlay(RLW);

    for (FText Response : Responses)
    {
        UResponseWidget* RW = CreateWidget<UResponseWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), ResponseWidgetClass);
        RW->SetText(Response);
        RLW->AddToChild(RW);
        RW->ResponseClicked.BindUFunction(this, "ResponseReceive");
    }

    return true;
}
