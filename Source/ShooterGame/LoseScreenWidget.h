#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "LoseScreenWidget.generated.h"

UCLASS()
class SHOOTERGAME_API ULoseScreenWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

    UFUNCTION()
        void OnRestartClicked();

public:
    ULoseScreenWidget(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
        UButton* RestartButton;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
        UTextBlock* LoseText;
};
