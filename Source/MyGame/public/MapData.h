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
#include "Engine/DataTable.h"
#include "MapData.generated.h"

USTRUCT(BlueprintType)
struct FDataTableMapData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FDataTableMapData() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable Test")
		int32 province;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable Test")
		int32 red;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable Test")
		int32 green;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable Test")
		int32 blue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable Test")
		FString name;
};


struct FMapColorData
{
	FMapColorData(){};
	FMapColorData(int32 InHeight,int32 InWidth);
	void Init(const FColor* ColorArray);
	FColor GetColor(int32 Index);
public:
	int32 Width;
	int32 Height;
	TArray<FColor>ColorData;
};
