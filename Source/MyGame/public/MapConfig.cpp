#include "MapConfig.h"
#include "MapData.h"



FMapColorData FMapConfigHelper::GetColorData(UTexture2D* Texture)
{
	TextureCompressionSettings OldCompressionSettings = Texture->CompressionSettings;
	TextureMipGenSettings OldMipGenSettings = Texture->MipGenSettings;
	bool OldSRGB = Texture->SRGB;
	Texture->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
	Texture->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
	Texture->SRGB = false;
	Texture->UpdateResource();
	int32 MapWidth = Texture->GetSizeX();
	int32 MapHeight = Texture->GetSizeY();
	const FColor* FormatedImageData = static_cast<const FColor*>(Texture->PlatformData->Mips[0].BulkData.LockReadOnly());


	 FMapColorData MapColorData(MapHeight, MapWidth);

	MapColorData.Init(FormatedImageData);


	Texture->PlatformData->Mips[0].BulkData.Unlock();

	Texture->CompressionSettings = OldCompressionSettings;
	Texture->MipGenSettings = OldMipGenSettings;
	Texture->SRGB = OldSRGB;
	Texture->UpdateResource();
	return MapColorData;
}
