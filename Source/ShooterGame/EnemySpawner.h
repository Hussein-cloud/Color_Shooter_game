#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "EnemySpawner.generated.h"

UCLASS()
class SHOOTERGAME_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	AEnemySpawner();

protected:
	virtual void BeginPlay() override;

	FTimerHandle SpawnTimerHandle;

	void SpawnEnemy();

	void UpdateSpawnDelay();

	FVector GetRandomPointInVolume();

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		UBoxComponent* SpawnArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		TSubclassOf<class AEnemyCharacter> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		float MinSpawnDelayRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		float MaxSpawnDelayRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		float DifficultyScalar;

};
