#include "GunBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GunBullet.h" 
#include "ShooterGameCharacter.h"

// This sets the default values for the gun
AGunBase::AGunBase()
{
    // Start with 10 bullets in the gun
    BulletCount = 10;

    // Create the root component for the gun
    USceneComponent* GunRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(GunRoot);

    // Create the box that will detect when the player picks up the gun
    PickupBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupBox"));
    PickupBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // Only detect overlaps
    PickupBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    PickupBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap); // Only respond to overlaps
    PickupBox->SetupAttachment(GunRoot); // Attach the box to the root component

    // Create the gun mesh (how the gun looks)
    GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
    GunMesh->SetRelativeRotation(FQuat(0.0f, 0.0f, -90.0f, 0.0f)); // Rotate the gun mesh
    GunMesh->SetupAttachment(PickupBox); // Attach the mesh to the pickup box
}

// This runs when the game starts
void AGunBase::BeginPlay()
{
    Super::BeginPlay();

    // Set up what happens when the player picks up the gun
    PickupBox->OnComponentBeginOverlap.AddDynamic(this, &AGunBase::PickupBy);

    // Set the bullet count to 300 when the game starts
    BulletCount = 300;
}

// This is the method to shoot the gun
void AGunBase::Shoot()
{
    // Show a message on the screen when shooting
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Shooting"));

    // Check if we have bullets left and a projectile class set
    if (ProjectileClass && BulletCount > 0)
    {
        FActorSpawnParameters SpawnParams;

        // Get the transform of the "Muzzle" socket to spawn the bullet
        FTransform BulletSpawnTransform = GunMesh->GetSocketTransform("Muzzle");

        // Spawn the bullet in the world
        AGunBullet* Bullet = GetWorld()->SpawnActor<AGunBullet>(ProjectileClass, BulletSpawnTransform);

        // Set whether this bullet can attack red targets
        Bullet->bCanAttackRed = bIsRedGun;

        // Decrease the bullet count by one
        BulletCount--;
    }
}

// This returns the current bullet count
int32 AGunBase::GetCurrentBulletCount() const
{
    return BulletCount;
}

// This handles what happens when the player picks up the gun
void AGunBase::PickupBy(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Check if the actor picking up the gun is the player character
    AShooterGameCharacter* Character = Cast<AShooterGameCharacter>(OtherActor);

    if (!Character) return;

    // Disable the pickup box collision so it doesn't overlap anymore
    PickupBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // Get the player's mesh (the part of the player that holds the gun)
    UStaticMeshComponent* PlayerMesh = Character->PlayerMesh;

    if (PlayerMesh)
    {
        // Attach the gun to the player's mesh at the specified socket
        AttachToComponent(PlayerMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, PickupSocketName);

        // Set the player's reference to this gun, depending on the gun color
        if (bIsRedGun)
        {
            Character->RedGunReference = this;
        }
        else
        {
            Character->BlueGunReference = this;
        }
    }
}
