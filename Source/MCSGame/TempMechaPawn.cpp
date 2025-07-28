#include "TempMechaPawn.h"

ATempMechaPawn::ATempMechaPawn()
{
    // Root and Mesh
    MechaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MechaMesh"));
    RootComponent = MechaMesh;
    MechaMesh->SetSimulatePhysics(true);  // Enable Chaos Physics for temp gravity/collision tests

    // Spring Arm
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = ArmLength;
    SpringArm->bUsePawnControlRotation = true;
    SpringArm->bEnableCameraLag = bUseCameraLag;

    // Camera
    ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
    ThirdPersonCamera->SetupAttachment(SpringArm);
}

void ATempMechaPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // Future: Add inertial dampener logic (e.g., convert velocity to heat on impacts)
}

void ATempMechaPawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Bind Axes (User-defined; expand to 6-axis later)
    PlayerInputComponent->BindAxis("MoveForward", this, &ATempMechaPawn::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ATempMechaPawn::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);  // Built-in for yaw
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);  // Built-in for pitch
}

void ATempMechaPawn::MoveForward(float Value)
{
    if (Value != 0.0f) {
        FVector Forward = GetActorForwardVector() * Value * ThrustSpeed;
        AddActorLocalOffset(Forward, true);  // Sweep for collisions (future heat conversion)
    }
}

void ATempMechaPawn::MoveRight(float Value)
{
    if (Value != 0.0f) {
        FVector Right = GetActorRightVector() * Value * ThrustSpeed;
        AddActorLocalOffset(Right, true);
    }
}