// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GunBase.h"
#include "LoseScreenWidget.h"
#include "ShooterGameCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class USpringArmComponent;
class UStaticMeshComponent;

UCLASS(config=Game)
class AShooterGameCharacter : public ACharacter
{
	GENERATED_BODY()

	
	UPROPERTY(VisibleDefaultsOnly, Category=Camera)
	USpringArmComponent* SpringArmComponent;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* RedFireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* BlueFireAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	
public:
	AShooterGameCharacter();

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
		UStaticMeshComponent* PlayerMesh;

	AGunBase* RedGunReference;
	AGunBase* BlueGunReference;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
		TSubclassOf<ULoseScreenWidget> LoseScreen;

	UPROPERTY()
		ULoseScreenWidget* LoseScreenInstance;


protected:
	virtual void BeginPlay();

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

	class UHealthComponent* HealthComponent;

	UFUNCTION()
		void Die();

	int GetRedGunAmmo();
	int GetBlueGunAmmo();

	class UHealthComponent* GetHealthComponent();
	

protected:
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void ShootRedGun(const FInputActionValue& Value);

	void ShootBlueGun(const FInputActionValue& Value);

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

};

