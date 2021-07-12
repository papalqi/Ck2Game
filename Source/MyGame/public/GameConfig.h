// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture.h"
#include "Engine/DataTable.h"


#include "GameConfig.generated.h"

/**
 * 
 */

USTRUCT(Blueprintable, BlueprintType)
struct FGameMapConfig 
{
	GENERATED_USTRUCT_BODY()
		virtual ~FGameMapConfig() { }
	FGameMapConfig() { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* ProvinceTex;

};

