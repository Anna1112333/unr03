 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "LMAGameMode.h"    //+++ сама поняла
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//#include "Camera/CameraComponent.h"
//#include "Components/DecalComponent.h"              //---
//#include "Components/InputComponent.h"
//#include "GameFramework/SpringArmComponent.h"
//#include "Kismet/GameplayStatics.h"
//#include "Kismet/KismetMathLibrary.h"
#include "LMADefaultCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class LEAVEMEALONE_API ALMADefaultCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ALMADefaultCharacter();

private:
	float YRotation = -75.0f; // отвечает за поворот камеры по оси Y.
	float ArmLength = 1400.0f; // отвечает за длину штатива.
	float FOV = 55.0f; // отвечает за поле зрения камеры.
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Mouse0(float Value);
	void Mouse(float Value);

protected:
	UPROPERTY()
	UDecalComponent* CurrentCursor = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorMaterial = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FVector changeSP(float val);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

