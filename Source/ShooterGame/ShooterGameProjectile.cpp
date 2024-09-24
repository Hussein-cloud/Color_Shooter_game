// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterGameProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// This sets the default values for the projectile
AShooterGameProjectile::AShooterGameProjectile()
{
    // Create the collision component (the part of the projectile that detects hits)
    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComp->InitSphereRadius(5.0f); // Set the size of the collision sphere
    CollisionComp->BodyInstance.SetCollisionProfileName("Projectile"); // Set the collision profile
    CollisionComp->OnComponentHit.AddDynamic(this, &AShooterGameProjectile::OnHit); // Notify when this component hits something

    // Make sure the projectile can't be walked on or stepped over
    CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
    CollisionComp->CanCharacterStepUpOn = ECB_No;

    // Set the collision component as the root component
    RootComponent = CollisionComp;

    // Create the projectile movement component (makes the projectile move)
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
    ProjectileMovement->UpdatedComponent = CollisionComp;
    ProjectileMovement->InitialSpeed = 3000.f; // Set how fast the projectile starts moving
    ProjectileMovement->MaxSpeed = 3000.f; // Set the maximum speed of the projectile
    ProjectileMovement->bRotationFollowsVelocity = true; // Make the projectile face the direction it's moving
    ProjectileMovement->bShouldBounce = true; // Allow the projectile to bounce off surfaces

    InitialLifeSpan = 3.0f; // Set the projectile to disappear after 3 seconds
}

// This is what happens when the projectile hits something
void AShooterGameProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // Check if the projectile hit something that can be affected by physics
    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
    {
        // Apply an impulse to the object that was hit
        OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

        // Destroy the projectile after it hits something
        Destroy();
    }
}
