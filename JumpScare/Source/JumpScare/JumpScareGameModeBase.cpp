// Copyright Epic Games, Inc. All Rights Reserved.


#include "JumpScareGameModeBase.h"
#include "Public/Widget/HUDWidget.h"
#include "Kismet/GamePlayStatics.h"
#include "Public/Player/PlayerCharacter.h"

UDialogueWidget* AJumpScareGameModeBase::GetDialogueWidget()
{
	return HUDWidget->GetDialogueWidget();
}

void AJumpScareGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (ensureMsgf(PC != nullptr, TEXT("AJumpScareGameModeBase : PlayerController is nullptr")))
		HUDWidget = CreateWidget<UHUDWidget>(PC, HUDWidgetClass);

	if (ensureMsgf(HUDWidget, TEXT("AJumpScareGameModeBase : HUDWidget is nullptr")))
	{
		HUDWidget->AddToViewport();
	}

	APlayerCharacter* Character = Cast<APlayerCharacter>(PC->GetCharacter());
	if (ensureMsgf(Character != nullptr, TEXT("GameModeBase : Character is nullptr")))
	{
		Character->SetHUDWidget(HUDWidget);
	}
}
