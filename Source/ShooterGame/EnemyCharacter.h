#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HealthComponent.h" 
#include "GameFramework/PlayerController.h"
#include "LoseScreenWidget.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class SHOOTERGAME_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UBoxComponent* DamageArea;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UPawnSensingComponent* PawnSensingComponent;




	UFUNCTION()
		void OnSeePawn(APawn* SeenPawn);

	UFUNCTION()
		void OnDamageAreaOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UHealthComponent* GetHealthComponent() const { return HealthComponent; }

	UPROPERTY(EditAnywhere, Category = "EnemyType")
		bool bIsRed = false;

	void Die();
};
