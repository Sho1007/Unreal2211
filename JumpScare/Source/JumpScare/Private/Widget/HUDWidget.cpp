// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/HUDWidget.h"
#include "../../Public/Widget/InteractMessageWidget.h"


void UHUDWidget::DisplayMessage(bool bShowMessage)
{
	if (bShowMessage)
	{
		if (WBP_InteractMessage != nullptr)
		{
			WBP_InteractMessage->SetMessageText(FText::FromName("Press E"));
			WBP_InteractMessage->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		if (WBP_InteractMessage != nullptr)
		{
			WBP_InteractMessage->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}