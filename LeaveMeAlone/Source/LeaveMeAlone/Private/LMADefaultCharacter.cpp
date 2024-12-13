// Fill out your copyright notice in the Description page of Project Settings.


#include "LMADefaultCharacter.h"
//#include "D:\Games2024\Task\Ta_3\LeaveMeAlone\Source\LeaveMeAlone\Public\LMADefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"

// Sets default values
ALMADefaultCharacter::ALMADefaultCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");//+++
	SpringArmComponent->SetupAttachment(GetRootComponent());//+++
	SpringArmComponent->TargetArmLength = ArmLength;
	SpringArmComponent->SetUsingAbsoluteRotation(true);	
	SpringArmComponent->SetRelativeRotation(FRotator(YRotation, 0.0f, 0.0f));
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bEnableCameraLag = true;	
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");//+++
	CameraComponent->SetupAttachment(SpringArmComponent);//+++
	CameraComponent->SetFieldOfView(FOV);
	CameraComponent->bUsePawnControlRotation = false;	

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}


void ALMADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
	OnSprint.Broadcast(Spr);
	if (CursorMaterial)
	{
		CurrentCursor = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), CursorMaterial, CursorSize, FVector(0));
	}
	HealthComponent->OnDeath.AddUObject(this, &ALMADefaultCharacter::OnDeath);
	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnHealthChanged.AddUObject(this, &ALMADefaultCharacter::OnHealthChanged);

}


void ALMADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!(HealthComponent->IsDead()))
	{
		RotationPlayerOnCursor();
	}
	if (Sprint_1 == false && Sprint_2 == false) Sprint = false; //неизвестно когда проверит тик переменную, а кргда BindAction , поэтому двойная проверка для выключения спринта
	if (Sprint_1 == true && Sprint_2 == true) Sprint_1 = false;
	if (Sprint_1 == false && Sprint_2 == true) Sprint_2 = false;
	if (Sprint == false && SprintEnergy < 100) SprintEnergy += 0.1f;
	if (Sprint == true && SprintEnergy > 0.2) SprintEnergy -= 0.1f;
	if (SprintEnergy >= 0.1)
		Spr = Sprint;
	else Spr = false;
}

// Called to bind functionality to input
void ALMADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ALMADefaultCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALMADefaultCharacter::MoveRight);	
	PlayerInputComponent->BindAxis("Mouse", this, &ALMADefaultCharacter::Mouse0);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ALMADefaultCharacter::Sprint0);
}
void ALMADefaultCharacter::MoveForward(float Value) {
	AddMovementInput(GetActorForwardVector(), Value);
}

void ALMADefaultCharacter::MoveRight(float Value) {
	AddMovementInput(GetActorRightVector(), Value);
}


void ALMADefaultCharacter::Mouse0(float Value) {
	SpringArmComponent->TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + Value * SP, minSP, maxSP);
	AddMovementInput(UKismetMathLibrary::GetForwardVector({ 0, 0, CameraComponent->GetComponentRotation().Yaw }), Value);
}

void ALMADefaultCharacter::OnDeath()
{
	
	CurrentCursor->DestroyRenderState_Concurrent();
	PlayAnimMontage(DeathMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.0f);
	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}

}

void ALMADefaultCharacter::OnHealthChanged(float NewHealth)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Health = %f"), NewHealth));
}

void ALMADefaultCharacter::RotationPlayerOnCursor()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		FHitResult ResultHit;
		PC->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, ResultHit);
		float FindRotatorResultYaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),
			ResultHit.Location).Yaw;
		SetActorRotation(FQuat(FRotator(0.0f, FindRotatorResultYaw, 0.0f)));
		if (CurrentCursor)
		{
			CurrentCursor->SetWorldLocation(ResultHit.Location);
		}
	}
}
void ALMADefaultCharacter::Sprint0() { Sprint_1 = true; Sprint_2 = true; Sprint = true; };