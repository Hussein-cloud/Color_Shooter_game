#include "EnemySpawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnemyCharacter.h"
#include "TimerManager.h"

// This sets the default values for the enemy spawner
AEnemySpawner::AEnemySpawner()
{
    // Create the spawn area where enemies will appear
    SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
    RootComponent = SpawnArea;

    // Set the initial range for spawn delays
    MinSpawnDelayRange = 1.0f;
    MaxSpawnDelayRange = 3.0f;

    // Set how much harder it gets to spawn enemies over time
    DifficultyScalar = 1.1f;
}

// This runs when the game starts
void AEnemySpawner::BeginPlay()
{
    Super::BeginPlay();

    // Start the timer to spawn enemies every second
    GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawner::SpawnEnemy, 1.0f, true);
}

// This runs every frame (over and over as the game plays)
void AEnemySpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// This is where we spawn an enemy
void AEnemySpawner::SpawnEnemy()
{
    // Check if we have an enemy class to spawn
    if (EnemyClass)
    {
        // Make it harder by updating the spawn delay
        UpdateSpawnDelay();

        // Get a random spot in the spawn area
        FVector SpawnLocation = GetRandomPointInVolume();

        // Spawn the enemy at that spot with no rotation
        GetWorld()->SpawnActor<AEnemyCharacter>(EnemyClass, SpawnLocation, FRotator::ZeroRotator);
    }
}

// This makes the game harder by spawning enemies faster
void AEnemySpawner::UpdateSpawnDelay()
{
    // Make the minimum and maximum delay shorter
    MinSpawnDelayRange /= DifficultyScalar;
    MaxSpawnDelayRange /= DifficultyScalar;

    // Get a new random delay between the new min and max
    float SpawnDelay = FMath::FRandRange(MinSpawnDelayRange, MaxSpawnDelayRange);

    // Restart the timer with the new delay
    GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
    GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawner::SpawnEnemy, SpawnDelay, false);
}

// This picks a random spot in the box where enemies can spawn
FVector AEnemySpawner::GetRandomPointInVolume()
{
    if (SpawnArea)
    {
        // Find the middle of the spawn area
        FVector SpawnOrigin = SpawnArea->Bounds.Origin;

        // Find how big the spawn area is
        FVector SpawnExtent = SpawnArea->Bounds.BoxExtent;

        // Pick a random spot inside the box
        return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
    }

    // If there's no spawn area, return zero vector (no location)
    return FVector::ZeroVector;
}
