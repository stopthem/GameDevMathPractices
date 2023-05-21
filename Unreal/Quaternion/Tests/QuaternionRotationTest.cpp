// Fill out your copyright notice in the Description page of Project Settings.


#include "QuaternionRotationTest.h"

#include "PennyDeBylMathCourse/BlueprintFunctionLibraries/MatrixExBlueprintFunctionLibrary.h"
#include "PennyDeBylMathCourse/Matrix/CustomMatrix.h"

AQuaternionRotationTest::AQuaternionRotationTest()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AQuaternionRotationTest::BeginPlay()
{
	Super::BeginPlay();

	const FCustomMatrix RotationMatrix = UMatrixExBlueprintFunctionLibrary::GetRotationMatrixFromAngles(RotationAngleVector);

	RotationAngle = UMatrixExBlueprintFunctionLibrary::GetRotationAxisAngle(RotationMatrix);

	RotationAxis = UMatrixExBlueprintFunctionLibrary::GetRotationAxisMatrix(RotationMatrix, RotationAngle).AsVector();
}

void AQuaternionRotationTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldRotation(UMatrixExBlueprintFunctionLibrary::GetQuaternionFromAngleAndAxis(RotationAxis, RotationAngle));
}
