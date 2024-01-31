// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "InteractableInterface.h"
#include "KeiTruckController.generated.h"

/**
 * 
 */
UCLASS()
class KEITRUCKSIMULATOR_API AKeiTruckController : public AWheeledVehiclePawn, public IInteractableInterface
{
	GENERATED_BODY()

	AKeiTruckController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Interact(ABasePlayer* _player) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SetInteractability(bool _interactability, FVector playerPos = FVector(0, 0, 0)) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void InterpsToOriginalRotation(float _deltaTime);



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UTextRenderComponent* TextRenderer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UStaticMeshComponent* Rotator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	class UStaticMeshComponent* CabBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UStaticMeshComponent* EnterVehiclePosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UStaticMeshComponent* ExitVehiclePosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Camera")
	class UCameraComponent* ThirdPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Camera")
	class UCameraComponent* FirstPersonCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* KeiMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* ActionBrake;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* ActionExitVehicle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* ActionHandbrake;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* ActionLookAround;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* ActionReset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* ActionSteering;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* ActionThrottle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* ActionToggleCamera;


	UFUNCTION(BlueprintCallable)
	void Brake(const FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
	void ExitVehicle(const FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
	void HandbrakeStart(const FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
	void HandbrakeEnd(const FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
	void LookAround(const FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
	void Reset(const FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
	void Steering(const FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
	void Throttle(const FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
	void ToggleCamera(const FInputActionValue& value);

	bool ActiveCamera = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ABasePlayer* player;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UChaosWheeledVehicleMovementComponent* ChaosWheeledVehicleMovementComponent;	
};
