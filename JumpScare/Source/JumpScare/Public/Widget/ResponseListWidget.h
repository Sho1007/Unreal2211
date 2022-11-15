// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/VerticalBox.h"
#include "ResponseWidget.h"

#include "ResponseListWidget.generated.h"

/**
 * 
 */
UCLASS()
class JUMPSCARE_API UResponseListWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void AddToChild(UResponseWidget* Widget);

protected:
	virtual void NativeConstruct() override;
private:
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget), BlueprintReadOnly)
	UVerticalBox* VB_ResponseList;
};
