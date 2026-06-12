#include "Weapon/Weapon.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

AWeapon::AWeapon()
{
    PrimaryActorTick.bCanEverTick = true;
    
    MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
    RootComponent = MeshComponent;
    
    MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
    MuzzleLocation->SetupAttachment(MeshComponent);
    
    CurrentAmmo = MaxAmmo;
}

void AWeapon::BeginPlay()
{
    Super::BeginPlay();
    CurrentAmmo = MaxAmmo;
}

void AWeapon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AWeapon::Fire()
{
    if (!HasAmmo())
    {
        UE_LOG(LogTemp, Warning, TEXT("No ammo!"));
        return;
    }
    
    // Check fire rate
    float CurrentTime = GetWorld()->GetTimeSeconds();
    if (CurrentTime - LastFireTime < FireRate)
    {
        return;
    }
    
    LastFireTime = CurrentTime;
    OnFire();
}

void AWeapon::OnFire()
{
    if (!HasAmmo())
        return;
    
    CurrentAmmo--;
    
    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
    APlayerController* PlayerController = Cast<APlayerController>(OwnerCharacter->GetController());
    
    if (PlayerController && MuzzleLocation)
    {
        FVector CameraLocation;
        FRotator CameraRotation;
        PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);
        
        FVector FireDirection = CameraRotation.Vector();
        FVector StartLocation = MuzzleLocation->GetComponentLocation();
        FVector EndLocation = StartLocation + FireDirection * 10000.0f;
        
        // Raycast for hit detection
        FHitResult HitResult;
        FCollisionQueryParams QueryParams;
        QueryParams.AddIgnoredActor(GetOwner());
        
        if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Pawn, QueryParams))
        {
            // Hit something!
            if (AActor* HitActor = HitResult.GetActor())
            {
                UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitActor->GetName());
                // Apply damage
                HitActor->TakeDamage(Damage, FDamageEvent(), PlayerController, this);
            }
        }
        
        // Draw debug line
        DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 1.0f);
    }
}

void AWeapon::Reload()
{
    CurrentAmmo = MaxAmmo;
    UE_LOG(LogTemp, Log, TEXT("%s reloaded!"), *WeaponName);
}