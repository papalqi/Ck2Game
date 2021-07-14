/*********************************************************
*@author papalqi
*@date 2021/07/12
*@brief H
*@see@ 
*
*@note
**********************************************************/
#pragma once
#include "CoreMinimal.h"
#include "Engine/TextRenderActor.h"
#include "MapData.h"
#include "Components/SplineComponent.h"
#include"Province.generated.h"




class ACk2Map;
struct FMapColorData;

UCLASS()
class AProvince : public AActor
{
	GENERATED_BODY()
public:

	AProvince();

	int32 ProvinceID;
	//所有的Map里的
	TArray<int32> AllCoordinateIndex;
	TArray<int32> OutLineCoordinateIndex;
	FColor ProvinceColor;
	FName ProvinceName;
	TArray<FVector2D> All2DCoordinate;
	TArray<FVector2D> OutLine2DCoordinate;

	FVector2D OrigineVector;
	FVector WorldVector;

	FVector WorldBias;
	FVector CellScale;

	TArray<FVector>GetOutLineWorldPositions();
	void InitProvince(int32 Width, int32 Height);

	void SpawnText();
	void CreateOutLine(int32 Width, int32 Height, TArray<FColor>& MapProvinceColorData);

	UPROPERTY()
	UTextRenderComponent* TextRenderComponent;

	UPROPERTY()
	USplineComponent* SplineComponent;
};



UCLASS()
class UProvinceManager : public UObject
{
	GENERATED_BODY()
public:
	void Init(ACk2Map* InMapActor,FMapColorData& MapColorData, TArray<FDataTableMapData*> &MapData);


protected:
	void SpawnText();
	void ClearText();

public:
	UPROPERTY()
	TMap<FColor, AProvince*> ColorToProcince;

	ACk2Map* MapActor;

};