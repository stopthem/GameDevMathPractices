// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MatrixTransformationTests.generated.h"

UCLASS()
class PENNYDEBYLMATHCOURSE_API AMatrixTransformationTests : public AActor
{
	GENERATED_BODY()

public:
	AMatrixTransformationTests();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, Category="Translation")
	FVector TranslateVector = FVector::ForwardVector;

private:
	void Translate();

public:
	UPROPERTY(EditAnywhere, Category="Rotate")
	FVector AngleVector = FVector(0.0f, 45.0f, 0.0f);

	UPROPERTY(EditAnywhere, Category="Rotate")
	bool bRotateAroundCenter = true;

private:
	void RotateAroundCenter();

	void Rotate();

public:
	UPROPERTY(EditAnywhere, Category="Shear")
	FVector ShearVector = FVector(0, 1, 0);

private:
	void Shear();

public:
	UPROPERTY(EditAnywhere, Category="Reflection")
	FVector ReflectionVector = FVector(0);

private:
	void Reflection();

public:
	UPROPERTY(EditAnywhere, Category="Transformation Tests")
	TObjectPtr<AActor> CenterActor;

	UPROPERTY(EditAnywhere, Category="Transformation Tests")
	TArray<TObjectPtr<AActor>> Spheres;

public:
	UPROPERTY(EditAnywhere, Category="Scaling")
	FVector ScaleVector = FVector::OneVector * 2;

private:
	void Scale();

public:
	UPROPERTY(EditAnywhere, Category="Quaternion")
	FVector RotateAxis = FVector::UpVector;

	UPROPERTY(EditAnywhere, Category="Quaternion")
	float RotateAngle = 45.0f;

private:
	void QuaternionRotate();
};
