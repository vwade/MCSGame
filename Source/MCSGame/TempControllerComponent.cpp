#include "TempControllerComponent.h"
#include "GameFramework/Pawn.h"  // For input setup if attached to Pawn

UTempControllerComponent::UTempControllerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTempControllerComponent::BeginPlay()
{
    Super::BeginPlay();
    OwnerActor = GetOwner();

    // Create SpringArm if not set
    if (!SpringArm) {
        SpringArm = NewObject<USpringArmComponent>(OwnerActor, TEXT("SpringArm"));
        SpringArm->RegisterComponent();
        SpringArm->AttachToComponent(OwnerActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
        SpringArm->TargetArmLength = ArmLength;
        SpringArm->bUsePawnControlRotation = true;
        SpringArm->bEnableCameraLag = bUseCameraLag;
    }

    // Create Camera
    if (!ThirdPersonCamera) {
        ThirdPersonCamera = NewObject<UCameraComponent>(OwnerActor, TEXT("ThirdPersonCamera"));
        ThirdPersonCamera->RegisterComponent();
        ThirdPersonCamera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
    }
}

void UTempControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    // Future: Accumulate heat from movement for dampener expulsion
}

// Input Functions (Bind these in Pawn's SetupPlayerInputComponent)
void UTempControllerComponent::MoveForward(float Value)
{
    if (OwnerActor && Value != 0.0f) {
        FVector Forward = OwnerActor->GetActorForwardVector() * Value * ThrustSpeed;
        OwnerActor->AddActorLocalOffset(Forward, true);  // Sweep for future kinetic-to-heat
    }
}

void UTempControllerComponent::MoveRight(float Value)
{
    if (OwnerActor && Value != 0.0f) {
        FVector Right = OwnerActor->GetActorRightVector() * Value * ThrustSpeed;
        OwnerActor->AddActorLocalOffset(Right, true);
    }
}

void UTempControllerComponent::Turn(float Value)
{
    if (OwnerActor) {
        OwnerActor->AddControllerYawInput(Value * RotationSpeed * GetWorld()->GetDeltaSeconds());
    }
}

void UTempControllerComponent::LookUp(float Value)
{
    if (OwnerActor) {
        OwnerActor->AddControllerPitchInput(Value * RotationSpeed * GetWorld()->GetDeltaSeconds());
    }
}