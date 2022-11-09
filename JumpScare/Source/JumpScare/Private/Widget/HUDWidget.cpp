// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/HUDWidget.h"
#include "../../Public/Widget/InteractMessageWidget.h"


void UHUDWidget::DisplayMessage(bool bShowMessage)
{
	UE_LOG(LogTemp, Warning, TEXT("Test 1"));
	if (bShowMessage)
	{
		UE_LOG(LogTemp, Warning, TEXT("Test 2"));
		if (WBP_InteractMessage != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Test 3"));
			WBP_InteractMessage->SetMessageText(FText::FromName("Press E"));
			WBP_InteractMessage->SetVisibility(ESlateVisibility::Visible);
		}
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Test 4"));
		if (WBP_InteractMessage != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Test 5"));
			WBP_InteractMessage->SetVisibility(ESlateVisibility::Hidden);
		}
		
	}
}
