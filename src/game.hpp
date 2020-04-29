#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <utility>
#include <tuple>
#include <cmath>
#include <random>
#include <mutex>
#include <cstddef>

#include "sgct/mutexes.h"
#include "sgct/shareddata.h"
#include "sgct/log.h"
#include "glad/glad.h"
#include "glm/packing.hpp"
#include "sgct/shadermanager.h"
#include <sgct/engine.h>
#include "sgct/shaderprogram.h"
#include "glm/matrix.hpp"

#include "player.hpp"
#include "collectiblepool.hpp"
#include "utility.hpp"

// abock;  consider implementing all of this as an "implicit" singleton.  Instead of
// making the functions static, you create a single instance of Game in the main.cpp and
// then pass this around.  Personally, I enjoy that method of handling singletons better
// see also https://github.com/OpenSpace/OpenSpace/blob/master/include/openspace/engine/globals.h
// and https://github.com/OpenSpace/OpenSpace/blob/master/src/engine/globals.cpp for a
// way to implement that functionality

//Implemented as explicit singleton, handles pretty much everything
class Game
{
public:
	//Init instance and print useful shader and model info
	static void init();

	//Get instance
	static Game& instance();
	static bool exists() { return mInstance != nullptr; }

	//Destroy instance
	static void destroy();

	//Copying forbidden
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;

	//Print loaded assets (shaders, models)
	void printLoadedAssets() const;    

	//Render objects
	void render() const;

	//Set MVP matrix
	void setMVP(const glm::mat4& mvp) { mMvp = mvp;};

	//Mostly used for debugging
	void addPlayer();

	void addPlayer(const glm::vec3& pos);

	//Add player from playerdata for instant sync
	void addPlayer(const PlayerData& p);

	//Add player from server request
	void addPlayer(std::tuple<unsigned int, std::string>&& inputTuple);

	//enable/disable player 
	void enablePlayer(unsigned id);
	void disablePlayer(unsigned id);

	//Update all gameobjects
	void update();

	//Get and encode object data for syncing
	std::vector<std::byte> getEncodedData();

	//Set object data from inputted data
	void setDecodedPlayerData(const std::vector<PlayerData>& newState);
	void setDecodedCollectibleData(const std::vector<CollectibleData>& newState);

	//Deserialize data
	void deserializeData(const std::vector<std::byte>& data,
		unsigned int pos,
		std::vector<PlayerData>& playerBuffer,
		std::vector<CollectibleData>& collectBuffer);

	//Set the turn speed of player player with id id
	void updateTurnSpeed(std::tuple<unsigned int, float>&& input);    
   
	//DEBUGGING TOOL: apply orientation to all GameObjects
	void rotateAllPlayers(float deltaOrientation);

	std::vector<PlayerData> getPlayerData();
	std::vector<CollectibleData> getCollectibleData();

private:
//Members
	//Singleton instance of game
	static Game* mInstance;

	//All players stored sequentually
	std::vector<Player> mPlayers;

	//Pool of collectibles for fast "generation" of objects
	CollectiblePool mCollectPool;

	//GameObjects unique id generator for player tagging
	static unsigned int mUniqueId;	

	//Track all loaded shaders' names
	std::vector<std::string> mShaderNames;

	//MVP matrix used for rendering
	glm::mat4 mMvp;

	//Slot after which players only present on master node exist
	size_t mLastSyncedPlayer;

	//The time of the last update (in seconds)
	float mLastFrameTime;

	static constexpr double collisionDistance = 0.2f; //TODO make this object specific
	static constexpr size_t mMAXPLAYERS = 110;
	static constexpr size_t mMAXCOLLECTIBLES = 300;

//Functions
	//Constructor
	Game();

	//Collision detection in mInteractObjects, bubble style
	void detectCollisions();

	//Get encoded player & collectible data
	

	//Read shader into ShaderManager
	void loadShader(const std::string& shaderName);

	//Display current list of shaders, called by printLoadedAssets()
	void printShaderPrograms() const;

	const glm::mat4& getMVP() { return mMvp; };
};
