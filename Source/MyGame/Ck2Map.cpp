// Fill out your copyright notice in the Description page of Project Settings.


#include "Ck2Map.h"
#include "Logging/LogMacros.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/TextRenderComponent.h"

// Sets default values
ACk2Map::ACk2Map()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	static ConstructorHelpers::FObjectFinder<UStaticMesh> TemStaticMesh(TEXT("StaticMesh'/Game/Mesh/Plane.Plane'"));

	USceneComponent* RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	if (TemStaticMesh.Succeeded())

	{
		MapMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
		if (MapMeshComponent)
		{
			// "Components/SkeletalMeshComponent.h"
			MapMeshComponent->SetStaticMesh(TemStaticMesh.Object);
			MapMeshComponent->SetupAttachment(RootComponent);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Fail--------------"));
		}

	}
}

// Called when the game starts or when spawned
void ACk2Map::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACk2Map::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACk2Map::InitMapData()
{
	if (!ProvinceTex || !MapMeshComponent)
	{
		UKismetSystemLibrary::PrintString(this, TEXT("not Ready"));
		return;
	}	

	CopyTextureToArray(ProvinceTex);

	SetMapScale();

	InitMapTextureData();

	SpawnText();
}

void ACk2Map::CopyTextureToArray(UTexture2D* Texture)
{

	TextureCompressionSettings OldCompressionSettings = Texture->CompressionSettings;
	TextureMipGenSettings OldMipGenSettings = Texture->MipGenSettings;
	bool OldSRGB = Texture->SRGB;
	MapProvinceColorData.Empty();
	Texture->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
	Texture->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
	Texture->SRGB = false;
	Texture->UpdateResource();
	MapWidth = Texture->GetSizeX();
	MapHeight = Texture->GetSizeY();
	const FColor* FormatedImageData = static_cast<const FColor*>(Texture->PlatformData->Mips[0].BulkData.LockReadOnly());
	MapProvinceColorData.Reserve(MapHeight* MapWidth);

	for (int32 X = 0; X < MapHeight; X++)
	{
		for (int32 Y = 0; Y < MapWidth; Y++)
		{
			FColor PixelColor = FormatedImageData[X * MapWidth + Y];
			//做若干操作
			MapProvinceColorData.Add(PixelColor);
		}
	}

	Texture->PlatformData->Mips[0].BulkData.Unlock();

	Texture->CompressionSettings = OldCompressionSettings;
	Texture->MipGenSettings = OldMipGenSettings;
	Texture->SRGB = OldSRGB;
	Texture->UpdateResource();
	
}

void ACk2Map::SetMapScale()
{
	if (CellSizeScale == 0)
	{
		CellSizeScale = 1;
	}

	FVector WorldScale = FVector(MapHeight * CellSizeScale,MapWidth*CellSizeScale,1);
	//MapMeshComponent->SetWorldScale3D(WorldScale);
	
	MapMeshComponent->GetLocalBounds(LocalMinPosition, LocalMaxPosition);
	MapMeshComponent->SetRelativeScale3D(WorldScale);

	CellSize.X= WorldScale.X*(LocalMaxPosition - LocalMinPosition).X/MapHeight;
	CellSize.Y = WorldScale.Y*(LocalMaxPosition - LocalMinPosition).Y / MapWidth;
	CellSize.Z = 0;
	WorldMinPosition=MapMeshComponent->GetComponentLocation()- FVector(MapHeight/2, MapWidth/2,0)*CellSize;

}

void ACk2Map::InitMapTextureData()
{

	Provinces.Empty();

	TMap<FColor, FProvinceUnit> ProvinceData;
	//
	//const TCHAR* ContextString;
	FString ContextString;
	TArray<FDataTableMapData*> MapData;
	MapDefine->GetAllRows<FDataTableMapData>(ContextString, MapData);

	for (int32 X = 0; X < MapHeight; X++)
	{
		for (int32 Y = 0; Y < MapWidth; Y++)
		{
			FColor PixelColor = MapProvinceColorData[X * MapWidth + Y];
			FProvinceUnit* ProvinceUnit=ProvinceData.Find(PixelColor);
			//如果有值
			if (ProvinceUnit)
			{
				(ProvinceUnit)->AllCoordinate.Add(X * MapWidth + Y);
			}
			else
			{
				FDataTableMapData* tempMap=nullptr;
				for (auto &a: MapData)
				{
					FColor MapColor(a->red,a->green,a->blue);
					if (MapColor == PixelColor)
					{
						tempMap = a;
					}
				}
				//如果没有值，我们新建
				FProvinceUnit temp;
				temp.ProvinceColor = PixelColor;
				if (tempMap != nullptr)
				{
					temp.ProvinceName = *tempMap->name;
					temp.ProvinceID = tempMap->province;
				}
				else
				{
					temp.ProvinceName = FName(*FString::FromInt(X * MapWidth + Y));
					temp.ProvinceID = ProvinceData.Num();
				}
				
				temp.AllCoordinate.Add(X * MapWidth + Y);
			
				ProvinceData.Add(PixelColor, temp);
			}
		}
	}

	for (auto &a : ProvinceData)
	{
		Provinces.Add(a.Value);
	}

	for (auto& a : Provinces)
	{
		a.InitProvince(MapWidth,MapHeight);
		a.GetOutLine(MapWidth, MapHeight,MapProvinceColorData);
	}

	
}

void ACk2Map::SpawnText()
{

	if (ProvincesText.Num() != 0)
	{

		for (int i=0;i!= Provinces.Num();i++)
		{
			ProvincesText[i]->Destroy();
		}
		ProvincesText.Empty();
	}
	{
		for (auto& a : Provinces)
		{
		
			FVector location = WorldMinPosition + CellSize* FVector(a.OrigineVector.X, MapWidth-a.OrigineVector.Y-1, 0)+FVector(0,0,5);
			a.WorldVector= location;


			ATextRenderActor* temp=GetWorld()->SpawnActor<ATextRenderActor>();
			temp->GetTextRender()->SetText(FText::FromName(a.ProvinceName));
			temp->SetActorLocation(location);
			temp->SetActorRotation(FRotator(90,0,0));
			temp->SetActorScale3D(FVector(0.5, 0.5, 0.5));
			ProvincesText.Add(temp);


		}
	}



}


void FProvinceUnit::InitProvince(int32 Width, int32 Height)
{
	if (AllCoordinate.Num() == 0)
	{
		return;
	}
	for (auto& a : AllCoordinate)
	{
		All2DCoordinate.Add(FVector2D(a / Width, a % Width));
	}
}


static TArray<FVector2D> OutlineBias
{ 
FVector2D (1,0), FVector2D(0,1), 
FVector2D(-1,0),  FVector2D(0,-1),
FVector2D(-1,1),  FVector2D(1,-1),
FVector2D(-1,-1),  FVector2D(1,1)
};


void FProvinceUnit::GetOutLine(int32 Width, int32 Height, TArray<FColor>& MapProvinceColorData)
{
	for (auto& a : All2DCoordinate)
	{
		//如果在map的边缘
		if (a.X == 0 || a.Y == 0 || a.X == Height - 1 || a.Y == Width - 1)
		{
			OutLine2DCoordinate.Add(a);
			OutLineCoordinate.Add(a.X * Width + a.Y);
			continue;
		}
		for (auto &bias: OutlineBias)
		{
			
			FVector2D b= a+bias;
			FColor OtherColor = MapProvinceColorData[b.X * Width + b.Y];
			if (OtherColor != ProvinceColor)
			{
				OutLine2DCoordinate.Add(a);
				OutLineCoordinate.Add(a.X * Width + a.Y);
				break;
			}
		}


	}


	FVector2D Temp;
	for (auto& a : All2DCoordinate)
	{
		 Temp = Temp + a;
	}

	
	//由于是从上向下，从左到右，所以我们需要
	OrigineVector = Temp/ All2DCoordinate.Num();



}
