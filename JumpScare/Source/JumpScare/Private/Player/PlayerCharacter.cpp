// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../../Public/Widget/HUDWidget.h"
#include "../../Public/Interface/InteractInterface.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	ensureMsgf(SpringArmComponent != nullptr, TEXT("PlayerCharacter : SpringArmComponent is not created!"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	ensureMsgf(CameraComponent != nullptr, TEXT("PlayerCharacter : CameraComponent is not created!"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
}

void APlayerCharacter::InteractCheck(AActor*& InteractAcotr)
{
	FVector Start = CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector() * 300.0f;
	FVector End = CameraComponent->GetComponentLocation()  + CameraComponent->GetForwardVector() * 500.0f;
	FHitResult HitResult;

	if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End, 10.0f, UEngineTypes::ConvertToTraceType(ECC_Camera), false, {}, EDrawDebugTrace::ForOneFrame, HitResult, true))
	{
		IInteractInterface* Interface = Cast<IInteractInterface>(HitResult.GetActor());
		if (Interface)
		{
			InteractAcotr = HitResult.GetActor();
			if (ensureMsgf(HUDWidget != nullptr, TEXT("PlayerCharacter : HUDWidget is nullptr")))
				HUDWidget->DisplayMessage(true);
		}
		return;
	}
	InteractActor = nullptr;
	if (ensureMsgf(HUDWidget != nullptr, TEXT("PlayerCharacter : HUDWidget is nullptr")))
		HUDWidget->DisplayMessage(false);
}

void APlayerCharacter::Interact()
{
	InteractCheck(InteractActor);
	if (InteractActor && InteractActor->IsValidLowLevelFast())
	{
		IInteractInterface* Interface = Cast<IInteractInterface>(InteractActor);
		if (Interface)
		{
			Interface->Interact();
		}
	}
}
