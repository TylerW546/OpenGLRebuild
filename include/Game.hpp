#pragma once

namespace gl {
class Game;
class GameData;
}

#include "Window.hpp"
#include "Entity.hpp"
#include "ResourceManager.hpp"

#include "deps.h"

#include <map>
#include <typeinfo>
#include <typeindex> 

namespace gl {

    struct GameData {
        uint16_t width, height;
        uint32_t tps;
        float dTime;
        bool Keys[1024];
        ResourceManager resourceManager;
    };

    class Game {
        // using Callback = std::function<void()>;
        // using Key = std::tuple<int,int,int>;

        // template<KEY, NEXT=void>
        // class CallbackMap {
        //     std::map<KEY, NEXT> map_;
        //     std::vector<Callback> callbacks_;
        //     void bindCallBack(CallBack callback) {
        //         callBacks_.pushBack(callBack);
        //     }
        // }

        private:

        EntityList* entities_;
        Window* window_;
        GameData gameData_;

        // Garantees pointer is to object of same type as index
        std::map<std::type_index, void*> renderMap_;

        // CallbackMap<int,CallbackMap<int,CallbackMap<int>> keyCallbackMap_;
        
        public:
        
        Game(uint32_t fps, uint16_t fieldWidth, uint16_t fieldHeight,
            const char* windowTitle = "", 
            WindowType windowType = WindowType::static_window);
        ~Game();

        // void bindKey(int scancode, Callback callback);
        // void bindKey(int scancode, int action, Callback callback);
        // void bindKey(int scancode, int action, int mod, Callback callback);

        uint16_t fieldWidth() {return gameData_.width;}
        uint16_t fieldHeight() {return gameData_.height;}
        bool setGameSize(uint16_t width, uint16_t height);
        void pressKey(int key);
        void releaseKey(int key); 

        GameData& data() {return gameData_;}

        void loadEntity(Entity* entity);
        void execute();


        template<typename T>
        bool loadRenderer(T* renderer) {
            std::type_index index = typeid(T);
            if (renderMap_[index]) return false;
            renderMap_[index] = renderer;
            return true;
        }

        template<typename T>
        T* renderer() {
            return (T*)renderMap_[typeid(T)];
        }

        // Remove renderer of type T from internal map
        // Returns pointer if removed
        // Returns nullptr if renderer of type T doesn't exist
        template<typename T>
        T* removeRenderer() {
            if (!renderMap_[typeid(T)]) return nullptr;
            T* tmpReturn = renderMap_[typeid(T)];
            renderMap_.erase(typeid(T));
            return tmpReturn;
        }

        // Remove renderer from internal map
        // Returns pointer if removed
        // Returns nullptr if renderer of type T doesn't exist
        // or pointer doesn't match provided renderer
        template<typename T>
        T* removeRenderer(T* renderer) {
            if (!renderer || renderMap_[typeid(T)] != renderer)
                return nullptr;
            T* tmpReturn = renderMap_[typeid(T)];
            renderMap_.erase(typeid(T));
            return tmpReturn;
        }

        // Removes and deletes renderer of given type
        // from internal map
        // Returns true if renderer of type T was delete
        // false if not found in map
        template<typename T>
        bool deleteRenderer() {
            T* tmpRenderer = renderMap_[typeid(T)];
            if (!tmpRenderer) return false;
            delete tmpRenderer;
            renderMap_.erase(typeid(T));
            return true;
        }

        // Removes and deletes renderer of given type
        // from internal map
        // Returns true if renderer of type T was delete\
        // false if not found in map
        template<typename T>
        bool deleteRenderer(T* renderer) {
            T* tmpRenderer = renderMap_[typeid(T)];
            if (!tmpRenderer) return false;
            delete tmpRenderer;
            renderMap_.erase(typeid(T));
            return true;
        }
    };


}