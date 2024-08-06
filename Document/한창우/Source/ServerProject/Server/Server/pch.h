#pragma once

#include "CorePch.h"

#include "Protocol.pb.h"
#include "Enum.pb.h"
#include "Struct.pb.h"

using GameSessionRef	= std::shared_ptr<class GameSession>;
using GameRoomRef		= std::shared_ptr<class GameRoom>;

using GameObjectRef		= std::shared_ptr<class GameObject>;
using CreatureRef		= std::shared_ptr<class Creature>;
using PlayerRef			= std::shared_ptr<class Player>;
using MonsterRef		= std::shared_ptr<class Monster>;


#ifdef _DEBUG
#pragma comment(lib, "ServerCore\\Debug\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Debug\\libprotobufd.lib")
#else
#pragma comment(lib, "ServerCore\\Release\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Release\\libprotobuf.lib")
#endif

#include "ServerPacketHandler.h"