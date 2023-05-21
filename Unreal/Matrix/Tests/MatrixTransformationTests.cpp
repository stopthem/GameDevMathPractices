// Fill out your copyright notice in the Description page of Project Settings.


#include "MatrixTransformationTests.h"

#include "PennyDeBylMathCourse/BlueprintFunctionLibraries/MatrixExBlueprintFunctionLibrary.h"
#include "PennyDeBylMathCourse/Matrix/CustomMatrix.h"

AMatrixTransformationTests::AMatrixTransformationTests()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMatrixTransformationTests::BeginPlay()
{
	Super::BeginPlay();

	Translate();

	Scale();

	RotateAroundCenter();

	Rotate();

	Shear();

	Reflection();

	QuaternionRotate();
}

void AMatrixTransformationTests::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// This code draws lines between the spheres to form a house.
	// Build a house PagBounce
	DrawDebugLine(GetWorld(), Spheres[0]->GetActorLocation(), Spheres[1]->GetActorLocation(), FColor::Green, true);
	DrawDebugLine(GetWorld(), Spheres[0]->GetActorLocation(), Spheres[2]->GetActorLocation(), FColor::Green, true);
	DrawDebugLine(GetWorld(), Spheres[0]->GetActorLocation(), Spheres[4]->GetActorLocation(), FColor::Green, true);

	DrawDebugLine(GetWorld(), Spheres[1]->GetActorLocation(), Spheres[3]->GetActorLocation(), FColor::Green, true);
	DrawDebugLine(GetWorld(), Spheres[1]->GetActorLocation(), Spheres[5]->GetActorLocation(), FColor::Green, true);

	DrawDebugLine(GetWorld(), Spheres[2]->GetActorLocation(), Spheres[3]->GetActorLocation(), FColor::Green, true);
	DrawDebugLine(GetWorld(), Spheres[2]->GetActorLocation(), Spheres[6]->GetActorLocation(), FColor::Green, true);

	DrawDebugLine(GetWorld(), Spheres[3]->GetActorLocation(), Spheres[7]->GetActorLocation(), FColor::Green, true);

	DrawDebugLine(GetWorld(), Spheres[4]->GetActorLocation(), Spheres[8]->GetActorLocation(), FColor::Green, true);
	DrawDebugLine(GetWorld(), Spheres[4]->GetActorLocation(), Spheres[6]->GetActorLocation(), FColor::Green, true);
	DrawDebugLine(GetWorld(), Spheres[4]->GetActorLocation(), Spheres[5]->GetActorLocation(), FColor::Green, true);

	DrawDebugLine(GetWorld(), Spheres[5]->GetActorLocation(), Spheres[8]->GetActorLocation(), FColor::Green, true);
	DrawDebugLine(GetWorld(), Spheres[5]->GetActorLocation(), Spheres[7]->GetActorLocation(), FColor::Green, true);
	DrawDebugLine(GetWorld(), Spheres[5]->GetActorLocation(), Spheres[4]->GetActorLocation(), FColor::Green, true);

	DrawDebugLine(GetWorld(), Spheres[6]->GetActorLocation(), Spheres[9]->GetActorLocation(), FColor::Green, true);
	DrawDebugLine(GetWorld(), Spheres[6]->GetActorLocation(), Spheres[7]->GetActorLocation(), FColor::Green, true);

	DrawDebugLine(GetWorld(), Spheres[7]->GetActorLocation(), Spheres[9]->GetActorLocation(), FColor::Green, true);
	DrawDebugLine(GetWorld(), Spheres[7]->GetActorLocation(), Spheres[6]->GetActorLocation(), FColor::Green, true);

	DrawDebugLine(GetWorld(), Spheres[9]->GetActorLocation(), Spheres[8]->GetActorLocation(), FColor::Green, true);
}

void AMatrixTransformationTests::Translate()
{
	if (TranslateVector == FVector(0))
	{
		return;
	}
	for (AActor* Sphere : Spheres)
	{
		Sphere->SetActorLocation(UMatrixExBlueprintFunctionLibrary::Translate(Sphere->GetActorLocation(), TranslateVector));
	}
}

void AMatrixTransformationTests::Scale()
{
	if (ScaleVector == FVector(0))
	{
		return;
	}
	for (AActor* Sphere : Spheres)
	{
		Sphere->SetActorLocation(UMatrixExBlueprintFunctionLibrary::ScaleAroundCenter(Sphere->GetActorLocation(), ScaleVector, CenterActor->GetActorLocation()));
	}
}


void AMatrixTransformationTests::RotateAroundCenter()
{
	if (AngleVector == FVector(0) || !bRotateAroundCenter)
	{
		return;
	}
	for (AActor* Sphere : Spheres)
	{
		Sphere->SetActorLocation(UMatrixExBlueprintFunctionLibrary::RotateAroundCenter(Sphere->GetActorLocation(), AngleVector, CenterActor->GetActorLocation()));

		FCustomMatrix RotationMatrix = UMatrixExBlueprintFunctionLibrary::GetRotationMatrixFromAngles(AngleVector);

		// const float RotationAngle = UMatrixExBlueprintFunctionLibrary::GetRotationAxisAngle(RotationMatrix);
		//
		// FCustomMatrix RotationAxisMatrix = UMatrixExBlueprintFunctionLibrary::GetRotationAxisMatrix(RotationMatrix, RotationAngle);
		//
		// UE_LOG(LogTemp, Warning, TEXT("rotation matrix : \n %s rotation angle : %f \n rotation axis matrix : \n %s")
		//        , *RotationMatrix.ToString(), RotationAngle, *RotationAxisMatrix.ToString());
		//
		// DrawDebugLine(GetWorld(), FVector(0), RotationAxisMatrix.AsVector() * 100.0f, FColor::Red, true);
	}
}

void AMatrixTransformationTests::Rotate()
{
	if (AngleVector == FVector(0) || bRotateAroundCenter)
	{
		return;
	}
	for (AActor* Sphere : Spheres)
	{
		Sphere->SetActorLocation(UMatrixExBlueprintFunctionLibrary::Rotate(Sphere->GetActorLocation(), AngleVector));

		FCustomMatrix RotationMatrix = UMatrixExBlueprintFunctionLibrary::GetRotationMatrixFromAngles(AngleVector);

		const float RotationAngle = UMatrixExBlueprintFunctionLibrary::GetRotationAxisAngle(RotationMatrix);

		FCustomMatrix RotationAxisMatrix = UMatrixExBlueprintFunctionLibrary::GetRotationAxisMatrix(RotationMatrix, RotationAngle);

		UE_LOG(LogTemp, Warning, TEXT("rotation angle : %f \n around \n rotation axis matrix : \n %s"), RotationAngle, *RotationAxisMatrix.ToString());

		DrawDebugLine(GetWorld(), FVector(0), RotationAxisMatrix.AsVector() * 50.0f, FColor::Red, true);
	}
}

void AMatrixTransformationTests::Shear()
{
	if (ShearVector == FVector(0))
	{
		return;
	}

	for (AActor* Sphere : Spheres)
	{
		Sphere->SetActorLocation(UMatrixExBlueprintFunctionLibrary::Shear(Sphere->GetActorLocation(), ShearVector));
	}
}

void AMatrixTransformationTests::Reflection()
{
	if (ReflectionVector == FVector(0))
	{
		return;
	}

	for (AActor* Sphere : Spheres)
	{
		Sphere->SetActorLocation(UMatrixExBlueprintFunctionLibrary::Reflection(Sphere->GetActorLocation(), ReflectionVector));
	}
}

void AMatrixTransformationTests::QuaternionRotate()
{
	if (RotateAngle == 0 && RotateAxis == FVector(0))
	{
		return;
	}

	for (AActor* Sphere : Spheres)
	{
		const FVector RotatedVector = UMatrixExBlueprintFunctionLibrary::QuaternionAngleAxis(Sphere->GetActorLocation(), RotateAxis, RotateAngle);
		Sphere->SetActorLocation(RotatedVector);
	}
}
