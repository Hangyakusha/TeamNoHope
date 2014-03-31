#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <android/asset_manager.h>

namespace gg
{
	class AssetManager
	{
	public:
		static AAssetManager* manager;
	};	
}

#endif