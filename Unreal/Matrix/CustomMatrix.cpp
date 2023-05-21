// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomMatrix.h"

const FCustomMatrix FCustomMatrix::IDENTITY_MATRIX = FCustomMatrix(4, 4, TArray<float>
                                                                   {
	                                                                   1, 0, 0, 0,
	                                                                   0, 1, 0, 0,
	                                                                   0, 0, 1, 0,
	                                                                   0, 0, 0, 1
                                                                   });

FCustomMatrix::FCustomMatrix()
	: Values(TArray<float>{0, 0, 0}), Rows(4), Columns(1)
{
}

FCustomMatrix::FCustomMatrix(const int Rows, const int Columns, const TArray<float>& Values)
{
	this->Values = TArray(Values);
	this->Rows = Rows;
	this->Columns = Columns;
}

FVector4 FCustomMatrix::AsPoint()
{
	if (!IsPointOrVector())
	{
		return FVector(0);
	}

	return FVector4(Values[0], Values[1], Values[2], 1);
}

FVector4 FCustomMatrix::AsVector4()
{
	if (!IsPointOrVector())
	{
		return FVector(0);
	}

	return FVector4(Values[0], Values[1], Values[2], 0);
}

FVector FCustomMatrix::AsVector()
{
	if (!IsPointOrVector())
	{
		return FVector(0);
	}

	return FVector(Values[0], Values[1], Values[2]);
}

bool FCustomMatrix::IsPointOrVector(const bool ShouldLogIfNot)
{
	const bool IsPointOrVector = Rows == 4 && Columns == 1;
	if (!IsPointOrVector && ShouldLogIfNot)
	{
		UE_LOG(LogTemp, Warning, TEXT("can't return matrix %s as point or vector because it is not a point or vector!(has to be 4 rows 1 column)"), *ToString());
	}

	return IsPointOrVector;
}

FCustomMatrix FCustomMatrix::AsTranslation()
{
	if (!IsPointOrVector(false))
	{
		UE_LOG(LogTemp, Warning, TEXT("can't return %s as translation matrix because it is not a point or vector!(has to be 4 rows 1 column)"), *ToString());
		return *this;
	}

	const TArray<float> TranslationValues
	{
		1, 0, 0, Values[0],
		0, 1, 0, Values[1],
		0, 0, 1, Values[2],
		0, 0, 0, 1
	};

	return FCustomMatrix(4, 4, TranslationValues);
}

FCustomMatrix FCustomMatrix::AsScale()
{
	if (!IsPointOrVector(false))
	{
		UE_LOG(LogTemp, Warning, TEXT("can't return %s as scale matrix because it is not a point or vector!(has to be 4 rows 1 column)"), *ToString());
		return *this;
	}

	const TArray<float> ScaleValues
	{
		Values[0], 0, 0, 0,
		0, Values[1], 0, 0,
		0, 0, Values[2], 0,
		0, 0, 0, 1
	};

	return FCustomMatrix(4, 4, ScaleValues);
}

FCustomMatrix FCustomMatrix::GetXRollMatrixFromAngle(const float Angle)
{
	const float AngleAsRadian = FMath::DegreesToRadians(Angle);

	return FCustomMatrix(4, 4, TArray<float>
	                     {
		                     1, 0, 0, 0,
		                     0, FMath::Cos(AngleAsRadian), -FMath::Sin(AngleAsRadian), 0,
		                     0, FMath::Sin(AngleAsRadian), FMath::Cos(AngleAsRadian), 0,
		                     0, 0, 0, 1
	                     });
}

FCustomMatrix FCustomMatrix::GetYRollMatrixFromAngle(const float Angle)
{
	const float AngleAsRadian = FMath::DegreesToRadians(Angle);

	return FCustomMatrix(4, 4, TArray<float>
	                     {
		                     FMath::Cos(AngleAsRadian), 0, FMath::Sin(AngleAsRadian), 0,
		                     0, 1, 0, 0,
		                     -FMath::Sin(AngleAsRadian), 0, FMath::Cos(AngleAsRadian), 0,
		                     0, 0, 0, 1
	                     });
}

FCustomMatrix FCustomMatrix::GetZRollMatrixFromAngle(const float Angle)
{
	const float AngleAsRadian = FMath::DegreesToRadians(Angle);

	return FCustomMatrix(4, 4, TArray<float>
	                     {
		                     FMath::Cos(AngleAsRadian), -FMath::Sin(AngleAsRadian), 0, 0,
		                     FMath::Sin(AngleAsRadian), FMath::Cos(AngleAsRadian), 0, 0,
		                     0, 0, 1, 0,
		                     0, 0, 0, 1
	                     });
}

FCustomMatrix FCustomMatrix::GetShearMatrixFromVector(const FVector& Vector)
{
	return FCustomMatrix(4, 4, TArray<float>
	                     {
		                     1, (float)Vector.Y, (float)Vector.Z, 0,
		                     (float)Vector.X, 1, (float)Vector.Z, 0,
		                     (float)Vector.X, (float)Vector.Y, 1, 0,
		                     0, 0, 0, 1
	                     });
}

FCustomMatrix FCustomMatrix::GetReflectionMatrixWithVector(const FVector& Vector)
{
	auto DetermineAxisOutput = [](const double Val)
	{
		return float(Val != 0 ? -1 : 1);
	};

	return FCustomMatrix(4, 4, TArray<float>
	                     {
		                     DetermineAxisOutput(Vector.X), 0, 0, 0,
		                     0, DetermineAxisOutput(Vector.Y), 0, 0,
		                     0, 0, DetermineAxisOutput(Vector.Z), 0,
		                     0, 0, 0, 1
	                     });
}

FCustomMatrix FCustomMatrix::VectorAsMatrix(const FVector& Vector)
{
	return FCustomMatrix(4, 1, TArray<float>{float(Vector.X), float(Vector.Y), float(Vector.Z), 0});
}

FVector4 FCustomMatrix::GetColumn(int Column)
{
	if (!Is4X4Matrix())
	{
		return FVector4();
	}

	return FVector4(Values[Column], Values[7 - Column], Values[11 - Column], Values[15 - Column]);
}

FVector4 FCustomMatrix::GetRow(int Row)
{
	if (!Is4X4Matrix())
	{
		return FVector4();
	}

	const int RowStartIndex = Row * Columns;
	return FVector4(Values[RowStartIndex], Values[RowStartIndex + 1], Values[RowStartIndex + 2], Values[RowStartIndex + 3]);
}

float FCustomMatrix::ValueAt(int row, int column) const
{
	return Values[row * Columns + column];
}

bool FCustomMatrix::Is4X4Matrix()
{
	const bool Is4x4 = Rows == 4 && Columns == 4;
	if (!Is4x4)
	{
		UE_LOG(LogTemp, Warning, TEXT("matrix %s is not 4x4!"), *ToString());
	}
	return Is4x4;
}

FCustomMatrix FCustomMatrix::PointAsMatrix(const FVector& Vector)
{
	return FCustomMatrix(4, 1, TArray<float>{float(Vector.X), float(Vector.Y), float(Vector.Z), 1});
}

FCustomMatrix FCustomMatrix::operator+(FCustomMatrix& OtherMatrix)
{
	if (Rows != OtherMatrix.Rows || Columns != OtherMatrix.Columns)
	{
		UE_LOG(LogTemp, Warning, TEXT("can't add matrix %s to %s because either row or column count does not match!"), *ToString(), *OtherMatrix.ToString());
		return *this;
	}

	FCustomMatrix AggregateMatrix(Rows, Columns, Values);

	for (int i = 0; i < AggregateMatrix.Values.Num(); ++i)
	{
		AggregateMatrix.Values[i] += OtherMatrix.Values[i];
	}

	return AggregateMatrix;
}

FCustomMatrix FCustomMatrix::operator*(FCustomMatrix& OtherMatrix)
{
	if (Columns != OtherMatrix.Rows)
	{
		UE_LOG(LogTemp, Warning, TEXT("can't multiply matrix %s with %s because first matrix column count does not match second matrix row count!"), *ToString(), *OtherMatrix.ToString());
		return *this;
	}

	TArray<float> MultipliedValues;
	MultipliedValues.SetNum(Rows * OtherMatrix.Columns);

	FCustomMatrix MultipliedMatrix(Rows, OtherMatrix.Columns, MultipliedValues);

	for (int r = 0; r < Rows; ++r)
	{
		for (int oc = 0; oc < OtherMatrix.Columns; ++oc)
		{
			for (int c = 0; c < Columns; ++c)
			{
				MultipliedMatrix.Values[r * OtherMatrix.Columns + oc] += Values[r * Columns + c] * OtherMatrix.Values[c * OtherMatrix.Columns + oc];
			}
		}
	}

	return MultipliedMatrix;
}

FString FCustomMatrix::ToString()
{
	FString MatrixString = "";
	for (int r = 0; r < Rows; ++r)
	{
		for (int c = 0; c < Columns; ++c)
		{
			FString ValueStringToAdd = FString::SanitizeFloat(Values[r * Columns + c]);

			MatrixString += ValueStringToAdd + " ";
		}

		MatrixString += "\n";
	}

	return MatrixString;
}
