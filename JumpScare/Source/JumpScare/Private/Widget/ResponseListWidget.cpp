// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ResponseListWidget.h"

void UResponseListWidget::AddToChild(UResponseWidget* Widget)
{
	VB_ResponseList->AddChildToVerticalBox(Widget);
}

void UResponseListWidget::NativeConstruct()
{
	Super::NativeConstruct();
	bIsFocusable = true;
}
