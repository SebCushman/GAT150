#pragma once
#include "Resources/ResourceManager.h"
#include "Graphics/Renderer.h"
#include "Input/InputSystem.h"
#include "Core/Timer.h"
#include <vector>

namespace nc {
	class System;

	class Engine {
	public:
		bool Startup();
		void Shutdown();

		void Update();

		template<typename T>
		T* GetSystem();

	protected:
		std::vector<System*> m_systems;
	};

	template<typename T>
	T* Engine::GetSystem() {
		T* result{ nullptr };

		for (auto system : m_systems) {
			result = dynamic_cast<T*>(system);
			if (result) break;
		}

			return result;
	}
}