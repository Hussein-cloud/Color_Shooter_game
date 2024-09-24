// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "ShooterGameCharacter.h"
#include "EnemyCharacter.h"

// This sets the default values for the health component
UHealthComponent::UHealthComponent()
{
    MaxHealth = 100.0f;  // Set the maximum health to 100
    CurrentHealth = MaxHealth;  // Start with full health
}

// This runs when the game starts
void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();
}

// This is called when the character takes damage
void UHealthComponent::TakeDamage(float DamageAmount)
{
    // Decrease the current health by the damage amount, but don't let it go below 0
    CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);

    // If health drops to 0 or below, the character should die
    if (CurrentHealth <= 0.0f)
    {
        AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(GetOwner());
        if (Enemy)
        {
            Enemy->Die();  // If the owner is an enemy, make it die
        }
        else
        {
            AShooterGameCharacter* Player = Cast<AShooterGameCharacter>(GetOwner());
            Player->Die();  // If the owner is the player, make them die
        }
    }
}

// This is called when the character heals
void UHealthComponent::Heal(float HealAmount)
{
    // Increase the current health by the heal amount, but don't let it go over the max health
    CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
}

// This returns the current health
float UHealthComponent::GetCurrentHealth() const
{
    return CurrentHealth;
}

// This returns the maximum health
float UHealthComponent::GetMaxHealth() const
{
    return MaxHealth;
}

// This sets the current health to a new value, making sure it stays within bounds
void UHealthComponent::SetCurrentHealth(float NewHealth)
{
    CurrentHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
}

// This sets the maximum health to a new value and adjusts current health if needed
void UHealthComponent::SetMaxHealth(float NewMaxHealth)
{
    MaxHealth = NewMaxHealth;  // Set the max health to the new value
    CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);  // Adjust current health if it's over the new max
}
