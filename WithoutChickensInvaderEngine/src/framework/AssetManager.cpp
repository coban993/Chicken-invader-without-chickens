#include "framework\AssetManager.h"

namespace wci
{
	unique<AssetManager> AssetManager::assetManager{ nullptr };

	AssetManager& AssetManager::Get()
	{
		if (!assetManager)
			assetManager = std::move(unique<AssetManager>{new AssetManager});

		return *assetManager;
	}

	shared<sf::Texture> AssetManager::LoadTexture(const std::string& path)
	{
		//ako je vec ucitana onda se ne vraca kopija nego ta ucitana
		auto found = mLoadedTextureMap.find(path);
		if (found != mLoadedTextureMap.end())
			return found->second;

		//ako nije ucitana onda je trazi i ubaci u mapu
		shared<sf::Texture> newTexture{ new sf::Texture };
		if(newTexture->loadFromFile(mRootDirectory + path))
		{
			mLoadedTextureMap.insert({path, newTexture});
			return newTexture;
		}

		return shared<sf::Texture> {nullptr};
	}

	void AssetManager::CleanCycle()
	{
		for (auto iter = mLoadedTextureMap.begin(); iter != mLoadedTextureMap.end();)
		{
			if (iter->second.unique())
			{
				LOG("cleaning texture: %s", iter->first.c_str());
				iter = mLoadedTextureMap.erase(iter);
			}
			else
				++iter;
		}
	}

	void AssetManager::SetAssetRootDirectory(const std::string& directory)
	{
		mRootDirectory = directory;
	}

	AssetManager::AssetManager() : mRootDirectory{}
	{
	}
}
