// Fill out your copyright notice in the Description page of Project Settings.


#include "LMADefaultCharacter.h"
//#include "D:\Games2024\Task\Ta_3\LeaveMeAlone\Source\LeaveMeAlone\Public\LMADefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
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
}

// Called when the game starts or when spawned
void ALMADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (CursorMaterial)
	{
		CurrentCursor = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), CursorMaterial, CursorSize, FVector(0));
	}
	
}

// Called every frame
void ALMADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

// Called to bind functionality to input
void ALMADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ALMADefaultCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALMADefaultCharacter::MoveRight);
	//PlayerInputComponent->BindAction(TEXT("Mouse0"), IE_Pressed, LMADefaultCharacter, &ALMADefaultCharacter::Mouse0);
	PlayerInputComponent->BindAxis("Mouse0", this, &ALMADefaultCharacter::Mouse0);
}
void ALMADefaultCharacter::MoveForward(float Value) {
	AddMovementInput(GetActorForwardVector(), Value);
}

void ALMADefaultCharacter::MoveRight(float Value) {
	AddMovementInput(GetActorRightVector(), Value);
}

FVector ALMADefaultCharacter::changeSP(float val) { ALMADefaultCharacter::SpringArmComponent->TargetArmLength += val; return { 1.0f, 1.0f, 1.0f }; }
void ALMADefaultCharacter::Mouse(float Value) {}
void ALMADefaultCharacter::Mouse0(float Value) {
	SpringArmComponent->TargetArmLength = SpringArmComponent->TargetArmLength * 50*Value;
	//ALMADefaultCharacter::ArmLength = ALMADefaultCharacter::ArmLength + Value*50;	
	//AddMovementInput(ALMADefaultCharacter::changeSP, Value); //void ����� ���������� � ������?
}
