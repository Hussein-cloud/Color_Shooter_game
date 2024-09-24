#include "LoseScreenWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

ULoseScreenWidget::ULoseScreenWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

void ULoseScreenWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (RestartButton)
    {
        RestartButton->OnClicked.AddDynamic(this, &ULoseScreenWidget::OnRestartClicked);
    }
}

void ULoseScreenWidget::OnRestartClicked()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName(*UGameplayStatics::GetCurrentLevelName(GetWorld())));
}
