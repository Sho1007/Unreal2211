// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "PlayerCharacter.generated.h"

UCLASS()
class JUMPSCARE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintCallable)
	void InteractCheck(AActor*& InteractAcotr);

	void SetHUDWidget(class UHUDWidget* Value) { HUDWidget = Value; }

	// BindFunction
	void Interact();

private:
	UPROPERTY(meta = (AllowPrivateAccess = true), BlueprintReadOnly, EditDefaultsOnly)
	class UCameraComponent* CameraComponent = nullptr;
	UPROPERTY(meta = (AllowPrivateAccess = true), EditDefaultsOnly)
	class USpringArmComponent* SpringArmComponent = nullptr;
	UPROPERTY(meta = (AllowPrivateAccess = true), BlueprintReadWrite)
	AActor* InteractActor = nullptr;

	// HUD
	UPROPERTY(meta = (AllowPrivateAccess = true), BlueprintReadWrite)
	UHUDWidget* HUDWidget = nullptr;
};
