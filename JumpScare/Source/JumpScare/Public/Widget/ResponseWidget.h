// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
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
	void SetText(FText Value) { Text = Value; }
	
	FDele_ResponseWidget_Single_OneParam ResponseClicked;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnResponseClicked();
	UFUNCTION()
	void OnResponseHovered();
	UFUNCTION()
	void OnResponseUnHovered();

private:
	UPROPERTY(meta = (AllowPrivateAccess, BindWidget), BlueprintReadOnly)
	UButton* Btn_Response;
	UPROPERTY(meta = (AllowPrivateAccess, ExposeOnSpawn),BlueprintReadOnly)
	FText Text;
};
