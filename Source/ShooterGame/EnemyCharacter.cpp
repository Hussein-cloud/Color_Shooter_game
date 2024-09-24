#include "EnemyCharacter.h"
#include "ShooterGameCharacter.h"
#include "HealthComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"

// This sets up the enemy character
AEnemyCharacter::AEnemyCharacter()
{
    // Create the health component so the enemy can have health
    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

    // Create the sensing component so the enemy can see other characters
    PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));

    // Create the damage area that will detect when players get close
    DamageArea = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageArea"));
    DamageArea->SetCollisionResponseToAllChannels(ECR_Overlap); // Make it detect overlaps
    DamageArea->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f)); // Set the size of the area
    DamageArea->SetupAttachment(RootComponent); // Attach it to the root component
}

// This happens when the game starts
void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Set up what happens when the enemy sees the player
    PawnSensingComponent->OnSeePawn.AddDynamic(this, &AEnemyCharacter::OnSeePawn);

    // Set up what happens when the player enters the damage area
    DamageArea->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnDamageAreaOverlap);
}

// This runs every frame (over and over as the game plays)
void AEnemyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// This lets the enemy respond to player inputs (like controlling a character)
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// This is what happens when the enemy sees the player
void AEnemyCharacter::OnSeePawn(APawn* SeenPawn)
{
    // Check if the enemy saw the player
    AShooterGameCharacter* PlayerCharacter = Cast<AShooterGameCharacter>(SeenPawn);
    if (PlayerCharacter)
    {
        // If the enemy saw the player, move towards the player
        AAIController* AIController = Cast<AAIController>(GetController());
        if (AIController)
        {
            AIController->MoveToActor(PlayerCharacter, 5.0f); // Move close to the player
        }
    }
}

// This is what happens when the player enters the damage area
void AEnemyCharacter::OnDamageAreaOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Check if the player entered the area
    AShooterGameCharacter* PlayerCharacter = Cast<AShooterGameCharacter>(OtherActor);
    if (PlayerCharacter)
    {
        // If the player is in the area, damage the player
        UHealthComponent* PlayerHealth = PlayerCharacter->GetHealthComponent();
        if (PlayerHealth)
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Attacked player"); // Show a message on the screen
            PlayerHealth->TakeDamage(10.0f); // Deal 10 damage to the player
        }
    }
}

// This is what happens when the enemy dies
void AEnemyCharacter::Die()
{
    Destroy(); // Remove the enemy from the game
}
