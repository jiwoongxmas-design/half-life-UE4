#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class AWeapon;

UCLASS()
class HALFLIFEUE4_API APlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    APlayerCharacter();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Health system
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float MaxHealth = 100.0f;
    
    UPROPERTY(BlueprintReadWrite, Category = "Health")
    float CurrentHealth;

    // Weapon system
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<AWeapon> StartingWeaponClass;
    
    UPROPERTY(BlueprintReadWrite, Category = "Weapon")
    AWeapon* CurrentWeapon;

    // Movement
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float WalkSpeed = 600.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float SprintSpeed = 1200.0f;

public:
    // Health functions
    UFUNCTION(BlueprintCallable, Category = "Health")
    void TakeDamage(float DamageAmount);
    
    UFUNCTION(BlueprintCallable, Category = "Health")
    void Heal(float HealAmount);

    // Weapon functions
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void EquipWeapon(AWeapon* NewWeapon);
    
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void Fire();

private:
    // Input callbacks
    void MoveForward(float Value);
    void MoveRight(float Value);
    void LookUp(float Value);
    void TurnRight(float Value);
    void Sprint();
    void StopSprinting();
};