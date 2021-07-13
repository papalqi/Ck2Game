#pragma once
#include "CoreMinimal.h"
#include "MapConfig.generated.h"

class UTexture2D;
struct FMapColorData;
class UDataTable;



struct FMapConfigHelper
{
	static FMapColorData GetColorData(UTexture2D* ProvinceTex);
};




UCLASS()
class MYGAME_API UMapConfig : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ck2")
	UTexture2D* ProvinceTex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ck2")
	UStaticMesh* MapMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* MapDefine;
};


