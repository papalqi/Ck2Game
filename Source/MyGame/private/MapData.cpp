#include "MapData.h"



FMapColorData::FMapColorData(int32 InHeight, int32 InWidth)
:Height(InHeight),
Width(InWidth)
{
	ColorData.Reserve(Height*Width);
}

void FMapColorData::Init(const FColor* ColorArray)
{
	for (int32 X = 0; X < Height; X++)
	{
		for (int32 Y = 0; Y < Width; Y++)
		{
			FColor PixelColor = ColorArray[X * Width + Y];
			//×öÈô¸É²Ù×÷
			ColorData.Add(PixelColor);
		}
	}
}

FColor FMapColorData::GetColor(int32 Index)
{
	return ColorData[Index];
}
