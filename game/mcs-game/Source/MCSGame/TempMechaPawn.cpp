#include "TempMechaPawn.h"
#include "Utilities/MCSUnits.h"

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
        FVector Forward = GetActorForwardVector() * Value * ThrustSpeed; // (me, user) see I don't like this, I tend to think of the "actor's" forward vector as the combined direction of local horizontal coords (XZ/Y-Up plane) rather than some precomputed value I have no control over (end rant) | unless there's some way to look inside and control it
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

//  (me, user) it says its built-in so we comment this attempt out for now
// void ATempMechaPawn::Turn(float Value) {
//  if (Value != 0.0f) {
//      FVector TurnValue = 
//  }
// }