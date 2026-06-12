#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

AWEAPON_API AWeapon : public AActor
{
    GENERATED_BODY()

public:
    AWeapon();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // Weapon stats
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float Damage = 25.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float FireRate = 0.1f; // Time between shots in seconds
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    int32 MaxAmmo = 120;
    
    UPROPERTY(BlueprintReadWrite, Category = "Weapon")
    int32 CurrentAmmo;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    FString WeaponName = "Pistol";

    // Mesh components
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
    class USkeletalMeshComponent* MeshComponent;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
    class USceneComponent* MuzzleLocation;

public:
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    virtual void Fire();
    
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void Reload();
    
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    bool HasAmmo() const { return CurrentAmmo > 0; }

private:
    float LastFireTime = 0.0f;
    
    void OnFire();
};