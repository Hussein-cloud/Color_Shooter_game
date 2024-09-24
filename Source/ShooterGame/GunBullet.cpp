// Fill out your copyright notice in the Description page of Project Settings.

#include "GunBullet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "EnemyCharacter.h"
#include "HealthComponent.h"

// This sets the default values for the bullet
AGunBullet::AGunBullet()
{
    PrimaryActorTick.bCanEverTick = true; // Allows the bullet to be updated every frame

    // Create the collision component (the part of the bullet that detects hits)
    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComp->InitSphereRadius(5.0f); // Set the size of the collision sphere
    CollisionComp->BodyInstance.SetCollisionProfileName("Projectile"); // Set collision profile

    // Make sure the bullet can't be stepped on or walked over
    CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
    CollisionComp->CanCharacterStepUpOn = ECB_No;
    RootComponent = CollisionComp; // Set the collision component as the root

    // Create the projectile movement component (makes the bullet move)
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
    ProjectileMovement->UpdatedComponent = CollisionComp;
    ProjectileMovement->InitialSpeed = 3000.f; // Set how fast the bullet starts moving
    ProjectileMovement->MaxSpeed = 3000.f; // Set the maximum speed of the bullet
    ProjectileMovement->bRotationFollowsVelocity = true; // Make the bullet face the direction it's moving
    ProjectileMovement->bShouldBounce = true; // Allow the bullet to bounce off surfaces

    InitialLifeSpan = 3.0f; // Set the bullet to disappear after 3 seconds
}

// This runs when the game starts
void AGunBullet::BeginPlay()
{
    Super::BeginPlay();

    // Set up what happens when the bullet hits something
    CollisionComp->OnComponentHit.AddDynamic(this, &AGunBullet::OnHit);
}

// This updates the bullet every frame
void AGunBullet::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// This is what happens when the bullet hits something
void AGunBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // Make sure the bullet didn't hit itself or something it shouldn't
    if (OtherActor && OtherActor != this)
    {
        // Check if the bullet hit an enemy character
        AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(OtherActor);
        if (EnemyCharacter)
        {
            // Get the health component of the enemy
            UHealthComponent* EnemyHealth = EnemyCharacter->GetHealthComponent();
            if (EnemyHealth)
            {
                // Only damage the enemy if it matches the bullet's target type (red/blue)
                if (EnemyCharacter->bIsRed == bCanAttackRed)
                {
                    EnemyHealth->TakeDamage(30.0f); // Deal 30 damage to the enemy
                }

                Destroy(); // Destroy the bullet after hitting
            }
        }
    }
}
