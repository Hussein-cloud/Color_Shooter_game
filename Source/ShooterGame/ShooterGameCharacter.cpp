// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterGameCharacter.h"
#include "ShooterGameProjectile.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "HealthComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Blueprint/UserWidget.h"
#include "LoseScreenWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// This sets the default values for the player character
AShooterGameCharacter::AShooterGameCharacter()
{
    // The character doesn't start with a rifle
    bHasRifle = false;

    // Set the size for the player's collision capsule
    GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

    // Create the spring arm for camera movement and attach it to the root
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    SpringArmComponent->SetupAttachment(RootComponent);

    // Create the first-person camera and attach it to the spring arm
    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
    FirstPersonCameraComponent->SetupAttachment(SpringArmComponent);

    // Create the player's mesh (how the player looks) and attach it to the mesh component
    PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
    PlayerMesh->SetupAttachment(GetMesh());

    // Create the health component for the player
    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("PlayerHealthComponent"));
}

// This runs when the game starts
void AShooterGameCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Set up the input mapping context if the player controller is valid
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }

    // Set the input mode to game only and hide the mouse cursor
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        FInputModeGameOnly InputMode;
        PlayerController->SetInputMode(InputMode);
        PlayerController->bShowMouseCursor = false;
    }
}

// This sets up the player inputs like moving, looking, and shooting
void AShooterGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // Bind the jump action to the corresponding functions
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

        // Bind the movement action
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShooterGameCharacter::Move);

        // Bind the look action
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShooterGameCharacter::Look);

        // Bind the fire actions for both guns
        EnhancedInputComponent->BindAction(RedFireAction, ETriggerEvent::Triggered, this, &AShooterGameCharacter::ShootRedGun);
        EnhancedInputComponent->BindAction(BlueFireAction, ETriggerEvent::Triggered, this, &AShooterGameCharacter::ShootBlueGun);
    }
}

// This handles the player's movement based on input
void AShooterGameCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddMovementInput(GetActorForwardVector(), MovementVector.Y); // Move forward/backward
        AddMovementInput(GetActorRightVector(), MovementVector.X); // Move right/left
    }
}

// This handles the player's looking direction based on input
void AShooterGameCharacter::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAxisVector.X); // Look left/right
    }
}

// This sets whether the player has a rifle
void AShooterGameCharacter::SetHasRifle(bool bNewHasRifle)
{
    bHasRifle = bNewHasRifle;
}

// This returns whether the player has a rifle
bool AShooterGameCharacter::GetHasRifle()
{
    return bHasRifle;
}

// This is what happens when the player dies
void AShooterGameCharacter::Die()
{
    // Show the lose screen when the player dies
    if (LoseScreen)
    {
        LoseScreenInstance = CreateWidget<ULoseScreenWidget>(GetWorld(), LoseScreen);
        if (LoseScreenInstance)
        {
            LoseScreenInstance->AddToViewport();
        }
    }

    // Change the input mode to UI only and show the mouse cursor
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        FInputModeUIOnly InputMode;
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        PlayerController->SetInputMode(InputMode);
        PlayerController->bShowMouseCursor = true;
    }
}

// This returns the current ammo count for the red gun
int AShooterGameCharacter::GetRedGunAmmo()
{
    if (RedGunReference == nullptr) return 0;

    return RedGunReference->GetCurrentBulletCount();
}

// This returns the current ammo count for the blue gun
int AShooterGameCharacter::GetBlueGunAmmo()
{
    if (BlueGunReference == nullptr) return 0;

    return BlueGunReference->GetCurrentBulletCount();
}

// This returns the player's health component
UHealthComponent* AShooterGameCharacter::GetHealthComponent()
{
    return HealthComponent;
}

// This handles shooting the red gun
void AShooterGameCharacter::ShootRedGun(const FInputActionValue& Value)
{
    if (RedGunReference)
    {
        RedGunReference->Shoot();
    }
}

// This handles shooting the blue gun
void AShooterGameCharacter::ShootBlueGun(const FInputActionValue& Value)
{
    if (BlueGunReference)
    {
        BlueGunReference->Shoot();
    }
}
