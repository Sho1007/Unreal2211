// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class JUMPSCARE_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void DisplayMessage(bool bShowMessage);
	
private:
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite)
	class UDialogueWidget* WBP_Dialogue;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite)
	class UCanvasPanel* CP_HUD;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadWrite)
	class UInteractMessageWidget* WBP_InteractMessage;
};
