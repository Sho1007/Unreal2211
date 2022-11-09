// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractMessageWidget.generated.h"

/**
 * 
 */
UCLASS()
class JUMPSCARE_API UInteractMessageWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetMessageText(FText Value) { MessageText = Value; }
private:
	UPROPERTY(meta = (AllowPrivateAccess = true), BlueprintReadWrite)
	FText MessageText;
};
