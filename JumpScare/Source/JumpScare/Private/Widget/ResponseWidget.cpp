// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ResponseWidget.h"


void UResponseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Response->OnClicked.AddDynamic(this, &UResponseWidget::OnResponseClicked);
	Btn_Response->OnHovered.AddDynamic(this, &UResponseWidget::OnResponseHovered);
	Btn_Response->OnUnhovered.AddDynamic(this, &UResponseWidget::OnResponseUnHovered);
}

void UResponseWidget::OnResponseClicked()
{
	ResponseClicked.Execute(Text);
}

void UResponseWidget::OnResponseHovered()
{
	Btn_Response->SetBackgroundColor(FLinearColor(0, 0, 0, 1));
}

void UResponseWidget::OnResponseUnHovered()
{
	Btn_Response->SetBackgroundColor(FLinearColor(0, 0, 0, 0.3));
}
