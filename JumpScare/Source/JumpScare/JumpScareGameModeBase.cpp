// Copyright Epic Games, Inc. All Rights Reserved.


#include "JumpScareGameModeBase.h"
#include "Public/Widget/HUDWidget.h"
#include "Kismet/GamePlayStatics.h"

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
}
