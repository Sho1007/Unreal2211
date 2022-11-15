// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JumpScareGameModeBase.generated.h"
/**
 * 
 */
UCLASS()
class JUMPSCARE_API AJumpScareGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	class UDialogueWidget* GetDialogueWidget();
protected:
	virtual void BeginPlay() override;
	class UHUDWidget* GetHUDWidget() { return HUDWidget; }
private:
	UPROPERTY(meta = (AllowPrivateAccess = true), BlueprintReadWrite)
	UHUDWidget* HUDWidget;
	
	UPROPERTY(meta = (AllowPrivateAccess = true), EditAnywhere, BlueprintReadWrite)
	class TSubclassOf<UHUDWidget> HUDWidgetClass;
};
