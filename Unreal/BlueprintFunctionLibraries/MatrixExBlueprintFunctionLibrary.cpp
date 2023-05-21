// Fill out your copyright notice in the Description page of Project Settings.


#include "MatrixExBlueprintFunctionLibrary.h"

#include "ArrayBlueprintFunctionLibrary.h"
#include "PennyDeBylMathCourse/Matrix/CustomMatrix.h"
#include "PennyDeBylMathCourse/Matrix/CustomQuaternionMatrix.h"

FVector UMatrixExBlueprintFunctionLibrary::Translate(const FVector& Location, const FVector& Direction)
{
	FCustomMatrix FromMatrix = FCustomMatrix::PointAsMatrix(Location);

	FCustomMatrix DirectionMatrix = FCustomMatrix::VectorAsMatrix(Direction);

	FCustomMatrix TranslatedMatrix = DirectionMatrix.AsTranslation() * FromMatrix;

	return TranslatedMatrix.AsPoint();
}

FVector UMatrixExBlueprintFunctionLibrary::Scale(const FVector& Location, const FVector& Scale)
{
	FCustomMatrix LocationMatrix = FCustomMatrix::PointAsMatrix(Location);

	FCustomMatrix ScaleMatrix = FCustomMatrix::VectorAsMatrix(Scale).AsScale();

	return (ScaleMatrix * LocationMatrix).AsVector();
}

FVector UMatrixExBlueprintFunctionLibrary::ScaleAroundCenter(const FVector& Location, const FVector& Scale, const FVector& Center)
{
	FVector FinalPoint = Translate(Location, Center * -1);

	FinalPoint = UMatrixExBlueprintFunctionLibrary::Scale(FinalPoint, Scale);

	return Translate(FinalPoint, Center);
}

FVector UMatrixExBlueprintFunctionLibrary::Rotate(const FVector& Location, const FVector& AnglesVector)
{
	FCustomMatrix LocationMatrix = FCustomMatrix::PointAsMatrix(Location);

	FCustomMatrix XRollMatrix = FCustomMatrix::GetXRollMatrixFromAngle(AnglesVector.X);
	FCustomMatrix YRollMatrix = FCustomMatrix::GetYRollMatrixFromAngle(AnglesVector.Y);
	FCustomMatrix ZRollMatrix = FCustomMatrix::GetZRollMatrixFromAngle(AnglesVector.Z);

	return (ZRollMatrix * YRollMatrix * XRollMatrix * LocationMatrix).AsPoint();
}

FVector UMatrixExBlueprintFunctionLibrary::RotateAroundCenter(const FVector& Location, const FVector& AnglesVector, const FVector& Center)
{
	FVector FinalPoint = Translate(Location, Center * -1);

	FinalPoint = Rotate(FinalPoint, AnglesVector);

	return Translate(FinalPoint, Center);
}

FVector UMatrixExBlueprintFunctionLibrary::QuaternionAngleAxis(const FVector& Location, const FVector& Axis, const float Angle)
{
	const float w = FMath::Cos(FMath::DegreesToRadians(Angle) / 2.0f);
	const float s = FMath::Sin(FMath::DegreesToRadians(Angle) / 2.0f);

	const FVector4 QuaternionVector(Axis.GetSafeNormal() * s, w);

	TArray<double> QuaternionConstructValues{
		1 - 2 * FMath::Square(QuaternionVector.Y) - 2 * FMath::Square(QuaternionVector.Z), QuaternionVector.X * QuaternionVector.Y * 2 - QuaternionVector.Z * QuaternionVector.W * 2,
		QuaternionVector.X * QuaternionVector.Z * 2 + QuaternionVector.Y * QuaternionVector.W * 2, 0,
		QuaternionVector.X * QuaternionVector.Y * 2 + QuaternionVector.Z * QuaternionVector.W, 1 - 2 * FMath::Square(QuaternionVector.X) - 2 * FMath::Square(QuaternionVector.Z),
		QuaternionVector.Y * QuaternionVector.Z * 2 - QuaternionVector.X * QuaternionVector.W * 2, 0,
		QuaternionVector.X * QuaternionVector.Z * 2 - QuaternionVector.Y * QuaternionVector.W * 2, QuaternionVector.Y * QuaternionVector.Z * 2 + QuaternionVector.X * QuaternionVector.W * 2,
		1 - 2 * FMath::Square(QuaternionVector.X) - 2 * FMath::Square(QuaternionVector.Y), 0,
		0, 0, 0, 1
	};

	FCustomQuaternionMatrix QuaternionConstructMatrix(4, 4, UArrayBlueprintFunctionLibrary::ConvertDoubleArrayToFloatArray(QuaternionConstructValues));

	FCustomMatrix LocationMatrix = FCustomMatrix::PointAsMatrix(Location);

	return (QuaternionConstructMatrix * LocationMatrix).AsVector();
}

FCustomMatrix UMatrixExBlueprintFunctionLibrary::GetRotationMatrixFromAngles(const FVector& AnglesVector)
{
	FCustomMatrix XRollMatrix = FCustomMatrix::GetXRollMatrixFromAngle(AnglesVector.X);
	FCustomMatrix YRollMatrix = FCustomMatrix::GetYRollMatrixFromAngle(AnglesVector.Y);
	FCustomMatrix ZRollMatrix = FCustomMatrix::GetZRollMatrixFromAngle(AnglesVector.Z);

	return ZRollMatrix * YRollMatrix * XRollMatrix;
}

float UMatrixExBlueprintFunctionLibrary::GetRotationAxisAngle(const FCustomMatrix& RotationMatrix)
{
	const float AxesAggregate = 0.5f * (RotationMatrix.ValueAt(0, 0) + RotationMatrix.ValueAt(1, 1) + RotationMatrix.ValueAt(2, 2) + RotationMatrix.ValueAt(3, 3) - 2);

	return FMath::Cos(AxesAggregate);
}

FCustomMatrix UMatrixExBlueprintFunctionLibrary::GetRotationAxisMatrix(const FCustomMatrix& RotationMatrix, const float Angle)
{
	FVector RotationAxis;

	const float AngleAsRadians = FMath::DegreesToRadians(Angle);

	RotationAxis.X = (RotationMatrix.ValueAt(2, 1) - RotationMatrix.ValueAt(1, 2)) / (2 * FMath::Sin(AngleAsRadians));
	RotationAxis.Y = (RotationMatrix.ValueAt(0, 2) - RotationMatrix.ValueAt(2, 0)) / (2 * FMath::Sin(AngleAsRadians));
	RotationAxis.Z = (RotationMatrix.ValueAt(1, 0) - RotationMatrix.ValueAt(0, 1)) / (2 * FMath::Sin(AngleAsRadians));

	return FCustomMatrix::VectorAsMatrix(RotationAxis);
}

FQuat UMatrixExBlueprintFunctionLibrary::GetQuaternionFromAngleAndAxis(const FVector& AxisVector, const float Angle)
{
	const float AngleAsRadians = FMath::DegreesToRadians(Angle);

	const float w = FMath::Cos(AngleAsRadians / 2.0f);
	const float s = FMath::Sin(AngleAsRadians / 2.0f);

	const FVector4 QuaternionVector(AxisVector.GetSafeNormal() * s, w);

	return FQuat(QuaternionVector.X, QuaternionVector.Y, QuaternionVector.Z, QuaternionVector.W);
}

FVector UMatrixExBlueprintFunctionLibrary::Shear(const FVector& Location, const FVector& ShearVector)
{
	FCustomMatrix LocationMatrix = FCustomMatrix::PointAsMatrix(Location);

	return (FCustomMatrix::GetShearMatrixFromVector(ShearVector) * LocationMatrix).AsPoint();
}

FVector UMatrixExBlueprintFunctionLibrary::Reflection(const FVector& Location, const FVector& ReflectionVector)
{
	FCustomMatrix LocationMatrix = FCustomMatrix::PointAsMatrix(Location);

	return (FCustomMatrix::GetReflectionMatrixWithVector(ReflectionVector) * LocationMatrix).AsPoint();
}
