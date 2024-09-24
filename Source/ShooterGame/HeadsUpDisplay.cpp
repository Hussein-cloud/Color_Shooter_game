#include "HeadsUpDisplay.h"
#include "ShooterGameCharacter.h"
#include "Components/ProgressBar.h"
#include "HealthComponent.h"
#include "Components/TextBlock.h"

// This is called when the HUD is first created
void UHeadsUpDisplay::NativeConstruct()
{
    Super::NativeConstruct();

    // Get the player character so we can track their health and ammo
    PlayerCharacter = Cast<AShooterGameCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    // Update the health bar when the HUD is created
    UpdateHealthBar();
}

// This is called every frame to update the HUD
void UHeadsUpDisplay::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    // Keep the health bar and ammo count updated
    UpdateHealthBar();
}

// This updates the health bar and ammo text on the HUD
void UHeadsUpDisplay::UpdateHealthBar()
{
    // Update the health bar if we have a valid player and health bar component
    if (PlayerCharacter && HealthProgressBar)
    {
        // Calculate the player's current health as a percentage
        float HealthPercent = PlayerCharacter->GetHealthComponent()->GetCurrentHealth() / PlayerCharacter->GetHealthComponent()->GetMaxHealth();

        // Set the health bar's fill amount based on the player's health
        HealthProgressBar->SetPercent(HealthPercent);
    }

    // Update the blue gun's ammo count if we have a valid player and text component
    if (BlueGunAmmoText && PlayerCharacter)
    {
        int32 BlueGunAmmo = PlayerCharacter->GetBlueGunAmmo(); // Get the blue gun's ammo count
        BlueGunAmmoText->SetText(FText::AsNumber(BlueGunAmmo)); // Display the ammo count on the HUD
    }

    // Update the red gun's ammo count if we have a valid player and text component
    if (RedGunAmmoText && PlayerCharacter)
    {
        int32 RedGunAmmo = PlayerCharacter->GetRedGunAmmo(); // Get the red gun's ammo count
        RedGunAmmoText->SetText(FText::AsNumber(RedGunAmmo)); // Display the ammo count on the HUD
    }
}
