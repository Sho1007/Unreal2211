// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResponseWidget.generated.h"

DECLARE_DELEGATE_OneParam(FDele_ResponseWidget_Single_OneParam, FText);

/**
 * 
 */
UCLASS()
class JUMPSCARE_API UResponseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UResponseWidget(const FObjectInitializer& ObjectInitializer);

	void SetText(FText Value) { Text = Value; }
	
	FDele_ResponseWidget_Single_OneParam ResponseClicked;

private:
	UFUNCTION()
	void OnResponseClicked();

private:
	UPROPERTY(meta = (AllowPrivateAccess, ExposeOnSpawn), BlueprintReadOnly)
	class UButton* Btn_Response;
	UPROPERTY(meta = (AllowPrivateAccess, ExposeOnSpawn),BlueprintReadOnly)
	FText Text;
};
