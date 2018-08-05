#pragma once

namespace OK
{
    template <typename SingletonType>
    class Singleton
    {
    public:
        template <typename ... ConstructorArguments>
        static void CreateSingleton(ConstructorArguments... arguments)
        {
            okAssert(ms_Instance == nullptr, "Singleton has already been created.");
            ms_Instance = new SingletonType{ arguments... };
        }

        static void DeleteSingleton()
        {
            okAssert(ms_Instance != nullptr, "Singleton does not exist or has already been destroyed.");
            okSafeDelete(ms_Instance);
        }

        static SingletonType* Get()
        {
            okAssert(ms_Instance != nullptr, "Singleton does not exist or has already been destroyed.");
            return ms_Instance;
        }

    private:
        static SingletonType* ms_Instance;
    };

    template <typename SingletonType>
    SingletonType* Singleton<SingletonType>::ms_Instance = nullptr;
}