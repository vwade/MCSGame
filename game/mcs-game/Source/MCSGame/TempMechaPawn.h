#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TempMechaPawn.generated.h"
#include "Utilities/MCSUnits.h"

UCLASS()
class MCSGAME_API ATempMechaPawn : public APawn
{
    GENERATED_BODY()

public:
    ATempMechaPawn();

    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent *MechaMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USpringArmComponent *SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCameraComponent *ThirdPersonCamera;

    // Movement Vars (Temp basics; expand to 6-axis later)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    MCSSpeed ThrustSpeed = 4;  // Relativistic thrust scalar (MCS units in meters/s)

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    MCSSpeed RotationSpeed = 6;  // Yaw/Pitch for immersive control

    // Camera Vars (For third-person testing)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    MCSLength ArmLength = 16;  // Distance from mecha (tweak for 20m scale views)

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    bool bUseCameraLag = true;  // Smooth follows for high-speed maneuvers

protected:
    // Input Handlers
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);
};