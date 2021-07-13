#include "Province.h"
#include "MapData.h"
#include "Engine/TextRenderActor.h"
#include "Ck2Map.h"
#include "Components/TextRenderComponent.h"
static TArray<FVector2D> OutlineBias
{
	FVector2D(1,0), FVector2D(0,1),
	FVector2D(-1,0),  FVector2D(0,-1),
	FVector2D(-1,1),  FVector2D(1,-1),
	FVector2D(-1,-1),  FVector2D(1,1)
};


void UProvince::GetOutLine(int32 Width, int32 Height, TArray<FColor>& MapProvinceColorData)
{
	TArray<FVector2D> TempOutLine2DCoordinate;
	TArray<int32> TempOutLineCoordinateIndex;
	for (auto& Coord : All2DCoordinate)
	{
		//如果在map的边缘,就说明是边缘
		if (Coord.X == 0 || Coord.Y == 0 || Coord.X == Height - 1 || Coord.Y == Width - 1)
		{
			TempOutLine2DCoordinate.Add(Coord);
			TempOutLineCoordinateIndex.Add(Coord.X * Width + Coord.Y);
			continue;
		}

		for (auto &bias : OutlineBias)
		{

			FVector2D b = Coord + bias;
			FColor OtherColor = MapProvinceColorData[b.X * Width + b.Y];
			if (OtherColor != ProvinceColor)
			{
				TempOutLine2DCoordinate.Add(Coord);
				TempOutLineCoordinateIndex.Add(Coord.X * Width + Coord.Y);
				break;
			}
		}
	}
	//找有顺序的边界
	//OutLine2DCoordinate.Empty();
	//for (int i=0;i!= TempOutLine2DCoordinate.Num();i++)
	//{
	//	if (TempOutLine2DCoordinate.Num()==0)
	//	{
	//		OutLine2DCoordinate.Add(TempOutLine2DCoordinate[0]);
	//	}
	//	else
	//	{
	//		FVector2D PreOutLine=OutLine2DCoordinate.Last();
	//		for (int j = 0; j != TempOutLine2DCoordinate.Num(); j++)
	//		{
	//			if (PreOutLine!= TempOutLine2DCoordinate[j]&&)
	//			{
	//			}
	//		}


	//	}
	//}
	All2DCoordinate= TempOutLine2DCoordinate;
	OutLineCoordinateIndex= TempOutLineCoordinateIndex;

	FVector2D Temp;
	for (auto& a : All2DCoordinate)
	{
		Temp = Temp + a;
	}


	//由于是从上向下，从左到右，所以我们需要
	OrigineVector = Temp / All2DCoordinate.Num();
}

void UProvince::InitProvince(int32 Width, int32 Height)
{
	if (IsValid(RenderActor))
	{
		RenderActor->Destroy(true);
		RenderActor = nullptr;
	}

	if (AllCoordinateIndex.Num() == 0)
	{
		return;
	}
	for (auto& a : AllCoordinateIndex)
	{
		All2DCoordinate.Add(FVector2D(a / Width, a % Width));
	}
}

void UProvince::SpawnText()
{
	if (GetWorld())
	{
		RenderActor = GetWorld()->SpawnActor<ATextRenderActor>();
		RenderActor->GetTextRender()->SetText(FText::FromName(ProvinceName));
		RenderActor->SetActorLocation(WorldVector);
		RenderActor->SetActorRotation(FRotator(90, 0, 0));
		RenderActor->SetActorScale3D(FVector(0.5, 0.5, 0.5));
	}

}

void UProvinceManager::Init(ACk2Map* InMapActor,FMapColorData& MapColorData, TArray<FDataTableMapData*> &MapData)
{
	MapActor= InMapActor;
	ColorToProcince.Empty();
	int32 MapHeight= MapColorData.Height;
	int32 MapWidth = MapColorData.Width;

	for (int32 X = 0; X < MapHeight; X++)
	{
		for (int32 Y = 0; Y < MapWidth; Y++)
		{
			FColor PixelColor = MapColorData.GetColor(X * MapWidth + Y);
			UProvince** ProvinceUnit = ColorToProcince.Find(PixelColor);
			//如果我们找到的话
			if (ProvinceUnit)
			{
				(*ProvinceUnit)->AllCoordinateIndex.Add(X * MapWidth + Y);
			}
			else
			{
				FDataTableMapData* TempMap = nullptr;
				for (auto &a : MapData)
				{
					FColor MapColor(a->red, a->green, a->blue);
					if (MapColor == PixelColor)
					{
						TempMap = a;
					}
				}
				//如果没有值，我们新建
				UProvince* temp=NewObject<UProvince>(MapActor->GetWorld());
				temp->ProvinceColor = PixelColor;
				if (TempMap != nullptr)
				{
					temp->ProvinceName = *TempMap->name;
					temp->ProvinceID = TempMap->province;
				}
				else
				{
					temp->ProvinceName = FName(*FString::FromInt(X * MapWidth + Y));
					temp->ProvinceID = MapData.Num();
				}

				temp->AllCoordinateIndex.Add(X * MapWidth + Y);

				ColorToProcince.Add(PixelColor, temp);
			}
		}
	}



	for (TMap<FColor, UProvince*>::TConstIterator It = ColorToProcince.CreateConstIterator(); It; ++It)
	{
		It->Value->InitProvince(MapWidth, MapHeight);
		It->Value->GetOutLine(MapWidth, MapHeight, MapColorData.ColorData);
	}

	for (TMap<FColor, UProvince*>::TConstIterator  It = ColorToProcince.CreateConstIterator(); It; ++It)
	{
		FVector Location = MapActor->GetWorldMinPosition() + MapActor->GetCellSize() * FVector(It->Value->OrigineVector.X, MapWidth - It->Value->OrigineVector.Y - 1, 0) + FVector(0, 0, 5);
		It->Value->WorldVector  = Location;
		
	}
	SpawnText();

}

void UProvinceManager::SpawnText()
{
	for (auto It = ColorToProcince.CreateConstIterator(); It; ++It)
	{
		It->Value->SpawnText();
	}
}

void UProvinceManager::ClearText()
{

}
