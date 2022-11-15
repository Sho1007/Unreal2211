// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

UCLASS()
class JUMPSCARE_API APickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void RotateActor();
	UFUNCTION()
	void PickUp();

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere)
	USceneComponent* HoldingComponent;

	bool bHolding;
	bool bGravity;

	FRotator ControlRotation;
	ACharacter* PlayerCharacter;
	class UCameraComponent* PlayerCamera;
	FVector ForwardVector;
};
