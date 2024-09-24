// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterGameGameMode.h"
#include "ShooterGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShooterGameGameMode::AShooterGameGameMode()
	: Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
