#include "pch.h"
#include <iostream>
#include <thread>
#include <vector>
using namespace std;
#include <atomic>
#include <mutex>
#include "ThreadManager.h"
#include "SocketUtils.h"
#include "Listener.h"
#include "Service.h"
#include "Session.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ServerPacketHandler.h"


// 서버
// 1) 새로운 소켓 생성 (socket)				문지기 역할
// 2) 소켓에 주소/포트 번호 설정 (bind)			상호/주소 (직원교육)
// 3) 소켓 일 시키기 (listen)					근무 시작
// 4) 손님 접속 (accept)						영업 개시
// 5) 클라와 통신


// Overlapped IO (비동기 + 논블로킹)


int main()
{
	SocketUtils::Init();

	ServerServiceRef service = make_shared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		make_shared<IocpCore>(),
		[]() { return make_shared<GameSession>(); }, // TODO : SessionManager 등
		100);

	assert(service->Start());

	for (int32 i = 0; i < 1; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch(); 
				}
			});
	}

	//char sendData[1000] = "Hello World";
	 
	// Contents
	while (true)
	{
		vector<BuffData> buffs{ BuffData {100, 1.5f}, BuffData{200, 2.3f}, BuffData {300, 0.7f } };
		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_TEST(1001, 100, 10, buffs);
		GSessionManager.Broadcast(sendBuffer);

		this_thread::sleep_for(250ms);
	}


	GThreadManager->Join();

	// 윈속 종료
	SocketUtils::Clear();
}