#include "HalfLifeUE4GameMode.h"
#include "Character/PlayerCharacter.h"

AHalfLifeUE4GameMode::AHalfLifeUE4GameMode()
{
    DefaultPawnClass = APlayerCharacter::StaticClass();
    PlayerControllerClass = APlayerController::StaticClass();
}

void AHalfLifeUE4GameMode::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Half-Life UE4 Game Started!"));
}