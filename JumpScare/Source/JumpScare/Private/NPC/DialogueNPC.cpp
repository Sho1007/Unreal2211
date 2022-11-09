// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/DialogueNPC.h"
#include "../../Public/NPC/DialogueAIController.h"

// Sets default values
ADialogueNPC::ADialogueNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ADialogueAIController::StaticClass();
}

// Called when the game starts or when spawned
void ADialogueNPC::BeginPlay()
{
	Super::BeginPlay();
	
	ADialogueAIController* DAC = Cast<ADialogueAIController>(GetController());
	if (ensure(DAC != nullptr))
	{
		DAC->SetBTAsset(BTAsset);
		DAC->SetBBAsset(BBAsset);
	}
}

void ADialogueNPC::Interact()
{
	ADialogueAIController* DAC = Cast<ADialogueAIController>(GetController());
	if (DAC)
		DAC->StartDialouge();
}

// Called every frame
void ADialogueNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADialogueNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}