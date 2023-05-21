// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PennyDeBylMathCourse/Matrix/CustomMatrix.h"
#include "QuaternionRotationTest.generated.h"

UCLASS()
class PENNYDEBYLMATHCOURSE_API AQuaternionRotationTest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AQuaternionRotationTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category="Rotation")
	FVector RotationAngleVector = FVector::LeftVector;

private:
	float RotationAngle = 0.0f;

	FVector RotationAxis = FVector(0);
};
