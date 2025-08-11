#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TempControllerComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MCSGAME_API UTempControllerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UTempControllerComponent();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
    virtual void BeginPlay() override;

    // Subcomponents (Created dynamically for modularity)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USpringArmComponent *SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCameraComponent *ThirdPersonCamera;

    // Movement Vars (Temp; expand to 6DoF with energy costs)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float ThrustSpeed = 1000.0f;  // Scalar for relativistic bursts

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float RotationSpeed = 100.0f;  // For yaw/pitch in orbital maneuvers

    // Camera Vars (Third-person immersion)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    float ArmLength = 500.0f;  // Boom distance (tweak for 1000m craft views)

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    bool bUseCameraLag = true;  // Smooth tracking for kinetic conversions

protected:
    // Input Bindings (Called from owning Pawn/Actor)
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);

    AActor *OwnerActor;  // Cache for movement application
};