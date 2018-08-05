#include <stdafx.h>
#include <engine\gameloop.h>

#include <engine\objectmodel\universe.h>

namespace OK
{
    void GameLoop::Init()
    {
        Universe::CreateSingleton();
        m_Universe = Universe::Get();
        m_Universe->Init();
    }

    void GameLoop::Shutdown()
    {
        m_Universe->Shutdown();
        Universe::DeleteSingleton();
        m_Universe = nullptr;
    }

    void GameLoop::Tick(const GameWindowEventData& eventData, OK::f32 dt)
    {
        m_Universe->Update(0.0f);
    }
}