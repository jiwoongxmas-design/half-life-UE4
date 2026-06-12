#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HalfLifeUE4GameMode.generated.h"

UCLASS()
class HALFLIFEUE4_API AHalfLifeUE4GameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AHalfLifeUE4GameMode();
    
    virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
    TSubclassOf<class APlayerCharacter> PlayerCharacterClass;
};