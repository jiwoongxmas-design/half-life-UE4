#include "AI/AICharacter.h"
#include "Character/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PerceptionComponent.h"

AAICharacter::AAICharacter()
{
    PrimaryActorTick.TickInterval = 0.1f;
    
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;
    
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->MaxWalkSpeed = PatrolSpeed;
}

void AAICharacter::BeginPlay()
{
    Super::BeginPlay();
    CurrentHealth = MaxHealth;
    
    // Find player character
    for (TActorIterator<APlayerCharacter> It(GetWorld()); It; ++It)
    {
        PlayerTarget = *It;
        break;
    }
}

void AAICharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateAI();
}

void AAICharacter::UpdateAI()
{
    if (!PlayerTarget)
        return;
    
    float DistanceToPlayer = FVector::Dist(GetActorLocation(), PlayerTarget->GetActorLocation());
    
    // Update state based on distance
    if (DistanceToPlayer < AttackRange)
    {
        SetAIState(EAIState::ATTACK);
        UpdateAttack();
    }
    else if (DistanceToPlayer < DetectionRange && CanSeeTarget())
    {
        SetAIState(EAIState::CHASE);
        UpdateChase();
    }
    else
    {
        SetAIState(EAIState::PATROL);
        UpdatePatrol();
    }
}

void AAICharacter::UpdatePatrol()
{
    // Simple patrol logic
    GetCharacterMovement()->MaxWalkSpeed = PatrolSpeed;
}

void AAICharacter::UpdateChase()
{
    if (!PlayerTarget)
        return;
    
    GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
    
    FVector DirectionToPlayer = (PlayerTarget->GetActorLocation() - GetActorLocation()).GetSafeNormal();
    AddMovementInput(DirectionToPlayer, 1.0f);
}

void AAICharacter::UpdateAttack()
{
    if (!PlayerTarget)
        return;
    
    // Face the player
    FVector DirectionToPlayer = (PlayerTarget->GetActorLocation() - GetActorLocation()).GetSafeNormal();
    FRotator NewRotation = DirectionToPlayer.Rotation();
    SetActorRotation(NewRotation);
    
    // Attack
    float CurrentTime = GetWorld()->GetTimeSeconds();
    if (CurrentTime - LastAttackTime > 1.0f) // Attack every 1 second
    {
        LastAttackTime = CurrentTime;
        PlayerTarget->TakeDamage(Damage);
        UE_LOG(LogTemp, Warning, TEXT("AI attacked player!"));
    }
}

bool AAICharacter::CanSeeTarget()
{
    if (!PlayerTarget)
        return false;
    
    FHitResult HitResult;
    FVector StartLocation = GetActorLocation();
    FVector EndLocation = PlayerTarget->GetActorLocation();
    
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);
    QueryParams.AddIgnoredActor(PlayerTarget);
    
    if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams))
    {
        return HitResult.GetActor() == PlayerTarget;
    }
    
    return true;
}

void AAICharacter::TakeDamage(float DamageAmount)
{
    CurrentHealth -= DamageAmount;
    if (CurrentHealth <= 0.0f)
    {
        CurrentHealth = 0.0f;
        Destroy();
    }
}

void AAICharacter::SetAIState(EAIState NewState)
{
    CurrentState = NewState;
}