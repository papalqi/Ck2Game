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
#include"Province.generated.h"




class ACk2Map;
struct FMapColorData;

UCLASS()
class UProvince : public UObject
{
	GENERATED_BODY()
public:
	int32 ProvinceID;
	//所有的Map里的
	TArray<int32> AllCoordinate;
	TArray<int32> OutLineCoordinate;
	FColor ProvinceColor;
	FName ProvinceName;
	TArray<FVector2D> All2DCoordinate;
	TArray<FVector2D> OutLine2DCoordinate;

	FVector2D OrigineVector;
	FVector WorldVector;
	void InitProvince(int32 Width, int32 Height);

	void SpawnText();
	void GetOutLine(int32 Width, int32 Height, TArray<FColor>& MapProvinceColorData);
	UPROPERTY()
	ATextRenderActor* RenderActor;
};



UCLASS()
class UProvinceManager : public UObject
{
	GENERATED_BODY()
public:
	void Init(ACk2Map* InMapActor,FMapColorData& MapColorData, TArray<FDataTableMapData*> &MapData);

	void SpawnText();


	UPROPERTY()
	TMap<FColor, UProvince*> ColorToProcince;

	ACk2Map* MapActor;

};