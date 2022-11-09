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
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(meta = (AllowPrivateAccess = true), BlueprintReadWrite)
	class UHUDWidget* HUDWidget;
	
	UPROPERTY(meta = (AllowPrivateAccess = true), EditAnywhere, BlueprintReadWrite)
	class TSubclassOf<UHUDWidget> HUDWidgetClass;
};
