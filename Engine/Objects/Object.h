#pragma once
#include "Core/Json.h"

namespace nc {
	class Object {
	public:
		virtual void Create(void* data = nullptr) = 0;
		virtual void Destroy() = 0;

		virtual void Read(const rapidjson::Value& value) {}

		template<typename T>
		static T* Instantiate() {
			T* instance = new T;
			return instance;
		}
	};
}