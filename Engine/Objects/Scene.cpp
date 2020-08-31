#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "ObjectFactory.h"

namespace nc {
    void nc::Scene::Create(void* data)
    {
        m_engine = static_cast<Engine*>(data);
    }

    void nc::Scene::Destroy()
    {
        // call the member function to remove all game objects
        RemoveAllGameObjects();
    }

    void nc::Scene::Read(const rapidjson::Value& value)
    {
        if (value.HasMember("Prototypes")) {
            const rapidjson::Value& objectsValue = value["Prototypes"];
            if (objectsValue.IsArray())
            {
                ReadPrototypes(objectsValue);
            }
        }

        if (value.HasMember("GameObjects")) {
            const rapidjson::Value& objectsValue = value["GameObjects"];
            if (objectsValue.IsArray())
            {
                ReadGameObjects(objectsValue);
            }
        }
    }

    void Scene::ReadGameObjects(const rapidjson::Value& value)
    {
        for (rapidjson::SizeType i = 0; i < value.Size(); i++)
        {
            const rapidjson::Value& objectValue = value[i];
            if (objectValue.IsObject())
            {
                std::string typeName;
                // read game object “type” name from json (Get)
                json::Get(objectValue, "type", typeName);
                GameObject* gameObject = ObjectFactory::Instance().Create<GameObject>(typeName);// create game object from object factory
                    if (gameObject)
                    {
                        // call game object create, pass in m_engine
                        gameObject->Create(this);
                        // call game object read
                        gameObject->Read(objectValue);
                        // add game object to scene
                        AddGameObject(gameObject);
                    }
            }
        }
    }

    void Scene::ReadPrototypes(const rapidjson::Value& value)
    {
        for (rapidjson::SizeType i = 0; i < value.Size(); i++)
        {
            const rapidjson::Value& objectValue = value[i];
            if (objectValue.IsObject())
            {
                std::string typeName;
                // read game object “type” name from json (Get)
                json::Get(objectValue, "type", typeName);
                GameObject* gameObject = ObjectFactory::Instance().Create<GameObject>(typeName);// create game object from object factory
                if (gameObject)
                {
                    // call game object create, pass in m_engine
                    gameObject->Create(this);
                    // call game object read
                    gameObject->Read(objectValue);

                    ObjectFactory::Instance().Register(gameObject->m_name, new Prototype<Object>(gameObject));
                }
            }
        }
    }

    void nc::Scene::Update()
    {
        // iterate through the actors and call Update on each actor
        for (auto gameObject : m_gameObjects) {
            // update
            gameObject->Update();
        }

        //remove/destroy game objects
        auto iter = m_gameObjects.begin();
        while (iter != m_gameObjects.end()) {
            if ((*iter)->m_flags[GameObject::eFlags::DESTROY]) {
                (*iter)->Destroy();
                delete (*iter);
                iter = m_gameObjects.erase(iter);
            }
            else {
                iter++;
            }
        }
    }

    void nc::Scene::Draw()
    {
        // iterate through the actors and call Draw on each actor
        for (auto gameObject : m_gameObjects) {
            // draw
            gameObject->Draw();
        }

    }

    GameObject* nc::Scene::Find(const std::string& name)
    {
        for (auto gameObject : m_gameObjects)
        {
            // compare game object name to name parameter (==)
            if(gameObject->m_name == name)
            {
                return gameObject;
            }
        }

        return nullptr;

    }

    std::vector<GameObject*> Scene::FindGameObjectsWithTag(const std::string& tag)
    {
        std::vector<GameObject*> gameObjects;
        for (auto gameObject : m_gameObjects)
        {
            // compare game object name to name parameter (==)
            if (gameObject->m_tag == tag)
            {
               gameObjects.push_back(gameObject);
            }
        }
        return gameObjects;
    }

    void nc::Scene::AddGameObject(GameObject* gameObject)
    {
        // push back gameObject
        m_gameObjects.push_back(gameObject);
    }

    void nc::Scene::RemoveGameObject(GameObject* gameObject)
    {
        auto iter = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
        if (iter != m_gameObjects.end())
        {
            // destroy (*iter)->
            (*iter)->Destroy();
            // delete 
            delete (*iter);
        }
        // erase iter from m_gameObjects
        m_gameObjects.erase(iter);
    }

    void nc::Scene::RemoveAllGameObjects()
    {
        for (GameObject* gameObject : m_gameObjects)
        {
            // destroy
            gameObject->Destroy();
            // delete
            delete gameObject;
        }
        // clear game objects
        m_gameObjects.clear();
    }
}
