// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthZeroDelegate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTERGAME_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UHealthComponent();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
        float CurrentHealth;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
        float MaxHealth;

public:

    UFUNCTION(BlueprintCallable, Category = "Health")
        void TakeDamage(float DamageAmount);

    UFUNCTION(BlueprintCallable, Category = "Health")
        void Heal(float HealAmount);

    UFUNCTION(BlueprintCallable, Category = "Health")
        float GetCurrentHealth() const;

    UFUNCTION(BlueprintCallable, Category = "Health")
        float GetMaxHealth() const;

    UFUNCTION(BlueprintCallable, Category = "Health")
        void SetCurrentHealth(float NewHealth);

    UFUNCTION(BlueprintCallable, Category = "Health")
        void SetMaxHealth(float NewMaxHealth);
};
