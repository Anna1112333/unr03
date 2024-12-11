// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components\HealthComponent.h"
#include "D:\Games2024\Task\Ta_3\LeaveMeAlone\Source\LeaveMeAlone\Public\LMAGameMode.h"    //+++ сама поняла
//#include "D:\Games2024\Task\Ta_3\LeaveMeAlone\Intermediate\Build\Win64\UnrealEditor\Inc\LeaveMeAlone\UHT\LMADefaultCharacter.generated.h"
#include "LMADefaultCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHealthComponent;
class UAnimMontage;

UCLASS()
class LEAVEMEALONE_API ALMADefaultCharacter : public ACharacter
{

	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ALMADefaultCharacter();
	UFUNCTION()
	UHealthComponent* GetHealthComponent() const { return HealthComponent; }
private:
	float YRotation = -75.0f; // отвечает за поворот камеры по оси Y.
	float ArmLength = 1400.0f; // отвечает за длину штатива.
	float FOV = 55.0f; // отвечает за поле зрения камеры.
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Mouse0(float Value);
	void OnDeath();
	void OnHealthChanged(float NewHealth);
	void RotationPlayerOnCursor();
	//void Mouse(float Value);

protected:
	UPROPERTY()
	UDecalComponent* CurrentCursor = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorMaterial = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="SPR")
	float SP = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SPR")
	float minSP = 400.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SPR")
	float maxSP = 1400.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Health")
	UHealthComponent*  HealthComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathMontage;

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
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

