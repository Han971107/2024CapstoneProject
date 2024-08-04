#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ServerPacketHandler.h"

void GameSession::OnConnected()
{
	GSessionManager.Add(static_pointer_cast<GameSession>(shared_from_this()));

	// 지금은 클라가 접속하면 바로 로그인 정보를 준다.
 	Send(ServerPacketHandler::Make_S_EnterGame());

	// 게임 입장
	// GRoom->
}

void GameSession::OnDisconnected()
{
	GSessionManager.Remove(static_pointer_cast<GameSession>(shared_from_this()));
}

void GameSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketHeader header = *((PacketHeader*)buffer);
	cout << "Packet ID : " << header.id << "Size : " << header.size << endl;
}

void GameSession::OnSend(int32 len)
{
	//cout << "OnSend Len = " << len << endl;
}