#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterGameCharacter.h"
#include "HeadsUpDisplay.generated.h"

UCLASS()
class SHOOTERGAME_API UHeadsUpDisplay : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
        UProgressBar* HealthProgressBar;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
        UTextBlock* BlueGunAmmoText;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
        UTextBlock* RedGunAmmoText;

    AShooterGameCharacter* PlayerCharacter;

    virtual void NativeConstruct() override;

    void UpdateHealthBar();

public:
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
