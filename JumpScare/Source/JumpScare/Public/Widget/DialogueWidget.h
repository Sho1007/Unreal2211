// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class JUMPSCARE_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (AllowPrivateAccess = true), BlueprintReadWrite)
	FText DialogueText;
	UPROPERTY(meta = (AllowPrivateAccess = true), BlueprintReadWrite)
	FText SpeakerName;
};
