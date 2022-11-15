// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../../Public/Widget/HUDWidget.h"
#include "../../Public/Interface/InteractInterface.h"
#include "../../Public/Object/PickUp.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	if (ensureMsgf(SpringArmComponent != nullptr, TEXT("PlayerCharacter : SpringArmComponent is not created!")))
	{
		SpringArmComponent->SetupAttachment(RootComponent);

		CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
		if (ensureMsgf(CameraComponent != nullptr, TEXT("PlayerCharacter : CameraComponent is not created!")))
		{
			CameraComponent->SetupAttachment(SpringArmComponent);
		}
	}

	HoldingComponent = CreateDefaultSubobject<USceneComponent>("HoldingComponent");
	if (ensureMsgf(HoldingComponent != nullptr, TEXT("HoldingComponent is nullptr")))
	{
		HoldingComponent->SetupAttachment(RootComponent);
		HoldingComponent->SetRelativeLocation(FVector(100, 0, 100));
	}

	CurrentPickUpItem = nullptr;
	bCanMove = true;
	bCanCameraMove = true;
	bInspecting = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	PitchMax = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMax;
	PitchMin = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMin;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInspecting)
	{
		if (bHoldingItem)
		{
			CameraComponent->SetFieldOfView(FMath::Lerp(CameraComponent->FieldOfView, 90.0f, 0.1f));
			HoldingComponent->SetRelativeLocation(FVector(0.0f, 50.0f, 50.0f));
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMax = 179.90f;
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMin = -179.90f;
			CurrentPickUpItem->RotateActor();
		}
		else
		{
			CameraComponent->SetFieldOfView(FMath::Lerp(CameraComponent->FieldOfView, 45.0f, 0.1f));

		}
	}
	else
	{
		CameraComponent->SetFieldOfView(FMath::Lerp(CameraComponent->FieldOfView, 90.0f, 0.1f));

		if (bHoldingItem)
		{
			HoldingComponent->SetRelativeLocation(FVector(50.0f, 0.0f, 0.0f));
		}
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);

	PlayerInputComponent->BindAction("Inspect", IE_Pressed, this, &APlayerCharacter::OnInspect);
	PlayerInputComponent->BindAction("Inspect", IE_Released, this, &APlayerCharacter::OnInspectRelease);

	// Bind Axis
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &APlayerCharacter::LookRight);
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	if (!Controller || !AxisValue || !bCanMove) return;

	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, AxisValue);

	InteractCheck(InteractActor);
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	if (!Controller || !AxisValue || !bCanMove) return;

	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, AxisValue);

	InteractCheck(InteractActor);
}

void APlayerCharacter::LookUp(float AxisValue)
{
	if (!Controller || !AxisValue || !bCanCameraMove) return;

	AddControllerPitchInput(AxisValue);

	InteractCheck(InteractActor);
}

void APlayerCharacter::LookRight(float AxisValue)
{
	if (!Controller || !AxisValue || !bCanCameraMove) return;

	AddControllerYawInput(AxisValue);

	InteractCheck(InteractActor);
}

void APlayerCharacter::InteractCheck(AActor*& InteractAcotr)
{
	FVector Start = CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector() * 300.0f;
	FVector End = CameraComponent->GetComponentLocation()  + CameraComponent->GetForwardVector() * 500.0f;
	FHitResult HitResult;

	if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End, 10.0f, UEngineTypes::ConvertToTraceType(ECC_Camera), false, {}, EDrawDebugTrace::ForOneFrame, HitResult, true))
	{
		if (HitResult.GetActor()->GetClass()->IsChildOf(APickUp::StaticClass()))
		{
			CurrentPickUpItem = Cast<APickUp>(HitResult.GetActor());
		}
		else
		{
			CurrentPickUpItem = nullptr;
		}
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

	if (CurrentPickUpItem && !bInspecting)
	{
		ToggleItemPickUp();
	}


	// 원래 Interact Function 이지만 Inspecting 추가를 위해 잠시 Comment로 바꿈
	// Inspect Function 추가 완료되면 Inspect 또한 Interact의 하위 기능으로 Convert 필요
	/*
	if (InteractActor && InteractActor->IsValidLowLevelFast())
	{
		IInteractInterface* Interface = Cast<IInteractInterface>(InteractActor);
		if (Interface)
		{
			Interface->Interact();
		}
	}
	*/
}

void APlayerCharacter::OnInspect()
{
	if (bHoldingItem)
	{
		LastRotation = GetControlRotation();
		ToggleMovement();
	}
	else
	{
		bInspecting = true;
	}
}

void APlayerCharacter::OnInspectRelease()
{
	if (bInspecting && bHoldingItem)
	{
		Controller->SetControlRotation(LastRotation);
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMax = PitchMax;
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMin = PitchMin;
		ToggleMovement();
	}
	else
	{
		bInspecting = false;
	}
}

void APlayerCharacter::ToggleItemPickUp()
{
	if (CurrentPickUpItem)
	{
		bHoldingItem = true;
		CurrentPickUpItem->PickUp();

		if (!bHoldingItem)
		{
			CurrentPickUpItem = nullptr;
		}
	}
}

void APlayerCharacter::ToggleMovement()
{
	bCanMove = !bCanMove;
	bInspecting = !bInspecting;
	CameraComponent->bUsePawnControlRotation = !CameraComponent->bUsePawnControlRotation;
	bUseControllerRotationYaw = !bUseControllerRotationYaw;
}
