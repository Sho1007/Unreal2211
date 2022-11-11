// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interface/InteractInterface.h"

#include "DialogueNPC.generated.h"

UCLASS()
class JUMPSCARE_API ADialogueNPC : public ACharacter, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADialogueNPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Interact() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FText GetNPCName() { return Name; }

private:
	UPROPERTY(meta = (AllowPrivateAccess = true), EditAnywhere, BlueprintReadWrite)
	class UBehaviorTree* BTAsset = nullptr;
	UPROPERTY(meta = (AllowPrivateAccess = true), EditAnywhere, BlueprintReadWrite)
	class UBlackboardData* BBAsset = nullptr;

	UPROPERTY(meta = (AllowPrivateAccess = true), EditAnywhere, BlueprintReadWrite)
	FText Name = FText::FromName(FName("DefaultNPCName"));
};
