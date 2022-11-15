// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/PickUp.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	if (ensureMsgf(StaticMesh != nullptr, TEXT("StaticMesh is not created!")))
	{
		StaticMesh->SetSimulatePhysics(true);
		SetRootComponent(StaticMesh);
	}
	bHolding = false;
	bGravity = true;
}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (ensureMsgf(PlayerCharacter != nullptr, TEXT("PlayerCharacter is nullptr")))
	{
		PlayerCamera = PlayerCharacter->FindComponentByClass<UCameraComponent>();
		ensureMsgf(PlayerCamera != nullptr, TEXT("PlayerCamera is nullptr"));

		TArray<USceneComponent*> Components;

		PlayerCharacter->GetComponents(Components);
		if (Components.Num() > 0)
		{
			for (USceneComponent* Comp : Components)
			{
				if (Comp->GetName() == "HoldingComponent")
				{
					HoldingComponent = Comp;
					break;
				}
			}
		}

		ensureMsgf(HoldingComponent != nullptr, TEXT("HoldingComponent is nullptr"));

	}

}

// Called every frame
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bHolding && HoldingComponent)
	{
		SetActorLocationAndRotation(HoldingComponent->GetComponentLocation(), HoldingComponent->GetComponentRotation());
	}
}

void APickUp::RotateActor()
{
	ControlRotation = GetWorld()->GetFirstPlayerController()->GetControlRotation();
	SetActorRotation(FQuat(ControlRotation));
}

void APickUp::PickUp()
{
	bHolding = !bHolding;
	bGravity = !bGravity;
	StaticMesh->SetEnableGravity(bGravity);
	StaticMesh->SetSimulatePhysics(!bHolding);
	StaticMesh->SetCollisionEnabled(bHolding ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryAndPhysics);

	if (!bHolding)
	{
		ForwardVector = PlayerCamera->GetForwardVector();
		StaticMesh->AddForce(ForwardVector * 1000.0f * StaticMesh->GetMass());
	}
}

