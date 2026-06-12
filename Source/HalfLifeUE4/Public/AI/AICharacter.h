#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

class APlayerCharacter;

UENUM(BlueprintType)
enum class EAIState : uint8
{
    IDLE = 0 UMETA(DisplayName = "Idle"),
    PATROL = 1 UMETA(DisplayName = "Patrol"),
    ALERT = 2 UMETA(DisplayName = "Alert"),
    CHASE = 3 UMETA(DisplayName = "Chase"),
    ATTACK = 4 UMETA(DisplayName = "Attack")
};

UCLASS()
class HALFLIFEUE4_API AAICharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AAICharacter();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // AI Stats
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float MaxHealth = 50.0f;
    
    UPROPERTY(BlueprintReadWrite, Category = "AI")
    float CurrentHealth;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float DetectionRange = 1000.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float AttackRange = 500.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float PatrolSpeed = 400.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float ChaseSpeed = 800.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float Damage = 15.0f;

    // Current state
    UPROPERTY(BlueprintReadWrite, Category = "AI")
    EAIState CurrentState = EAIState::IDLE;

public:
    UFUNCTION(BlueprintCallable, Category = "AI")
    void TakeDamage(float DamageAmount);
    
    UFUNCTION(BlueprintCallable, Category = "AI")
    void SetAIState(EAIState NewState);

private:
    APlayerCharacter* PlayerTarget;
    float LastAttackTime = 0.0f;
    
    void UpdateAI();
    void UpdatePatrol();
    void UpdateChase();
    void UpdateAttack();
    bool CanSeeTarget();
};