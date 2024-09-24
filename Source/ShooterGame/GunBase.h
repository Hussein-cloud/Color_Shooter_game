#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h" // Include SkeletalMeshComponent
#include "Components/BoxComponent.h"
#include "GunBase.generated.h"

class AGunBullet;

UCLASS()
class SHOOTERGAME_API AGunBase : public AActor
{
	GENERATED_BODY()

public:
	AGunBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun")
		TSubclassOf<AGunBullet> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun")
		int32 BulletCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun")
		FName PickupSocketName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USkeletalMeshComponent* GunMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UBoxComponent* PickupBox;

	UPROPERTY(EditDefaultsOnly, Category = "Gun")
		bool bIsRedGun = false;
		

public:
	UFUNCTION(BlueprintCallable, Category = "Gun")
		virtual void Shoot();

	UFUNCTION(BlueprintCallable, Category = "Gun")
		int32 GetCurrentBulletCount() const;

	UFUNCTION(BlueprintCallable, Category = "Gun")
		void PickupBy(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
