#include "Character/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "Weapon/Weapon.h"

APlayerCharacter::APlayerCharacter()
{
    PrimaryActorTick.TickInterval = 0.0f;
    
    // Don't rotate character with camera
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    GetCharacterMovement()->MaxWalkSpeedCrouched = 400.0f;
}

void APlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    CurrentHealth = MaxHealth;
    
    // Spawn starting weapon if specified
    if (StartingWeaponClass)
    {
        EquipWeapon(GetWorld()->SpawnActor<AWeapon>(StartingWeaponClass));
    }
}

void APlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    if (PlayerInputComponent)
    {
        // Movement
        PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
        PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
        
        // Looking
        PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
        PlayerInputComponent->BindAxis("TurnRight", this, &APlayerCharacter::TurnRight);
        
        // Actions
        PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
        PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::Sprint);
        PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::StopSprinting);
        PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::Fire);
    }
}

void APlayerCharacter::MoveForward(float Value)
{
    if (Controller && Value != 0.0f)
    {
        AddMovementInput(GetActorForwardVector(), Value);
    }
}

void APlayerCharacter::MoveRight(float Value)
{
    if (Controller && Value != 0.0f)
    {
        AddMovementInput(GetActorRightVector(), Value);
    }
}

void APlayerCharacter::LookUp(float Value)
{
    if (Controller)
    {
        AddControllerPitchInput(Value);
    }
}

void APlayerCharacter::TurnRight(float Value)
{
    if (Controller)
    {
        AddControllerYawInput(Value);
    }
}

void APlayerCharacter::Sprint()
{
    GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void APlayerCharacter::StopSprinting()
{
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void APlayerCharacter::TakeDamage(float DamageAmount)
{
    CurrentHealth -= DamageAmount;
    if (CurrentHealth <= 0.0f)
    {
        CurrentHealth = 0.0f;
        // TODO: Death logic
    }
}

void APlayerCharacter::Heal(float HealAmount)
{
    CurrentHealth = FMath::Min(CurrentHealth + HealAmount, MaxHealth);
}

void APlayerCharacter::EquipWeapon(AWeapon* NewWeapon)
{
    CurrentWeapon = NewWeapon;
    if (CurrentWeapon)
    {
        CurrentWeapon->SetOwner(this);
    }
}

void APlayerCharacter::Fire()
{
    if (CurrentWeapon)
    {
        CurrentWeapon->Fire();
    }
}