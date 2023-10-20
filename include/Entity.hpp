#pragma once

namespace gl{
class Entity;
class EntityLink;
class EntityList;
}

#include "Game.hpp"

#include "deps.h"

namespace gl {
    class Entity {
        EntityLink* link_;

        public:

        virtual void update(const GameData& gameData) {}
        virtual void render(const glm::mat4& windowModel) {}

        virtual void loadRenderer(Game* game) {}
        virtual void loadTextures(const GameData& data) {}

        // Callback methods
        virtual void GameSize_callback(uint16_t width, uint16_t height) {}


        // virtual glm::vec2 hitBox()=0;
        // virtual glm::vec2 position() {return pos_;}
        // virtual float rotation() {return rotation_;}
        // virtual glm::vec2 scale() {return scale_;}

    };

    class EntityLink {
        EntityLink* next_;
        EntityLink* last_;
        Entity* entity_;

        public:
        EntityLink(Entity* entity);
        ~EntityLink();

        Entity* entity() {return entity_;}
        
        EntityLink* next() {return next_;}
        EntityLink* setNext(EntityLink* link);
        EntityLink* last() {return last_;}
        EntityLink* setLast(EntityLink* link);

        void breakFromList();

        bool pushFront(EntityList* list);
        bool pushBack(EntityList* list);
        bool moveForward(size_t n=1);
        bool moveBackward(size_t n=1);
    };

    class EntityList {
        EntityLink* front_;
        EntityLink* last_;
        
        public:

        EntityList();
        ~EntityList();

        void appendFront(EntityLink* entity);
        void appendFront(Entity* entity) {
            appendFront(new EntityLink(entity));
        }

        void appendBack(EntityLink* entity);
        void appendBack(Entity* entity) {
            appendBack(new EntityLink(entity));
        }

        void render(const glm::mat4 &windowModel);
        void update(const GameData &gameData);

       template <typename... params>
        void call(void (Entity::*method)(params...), params... args) {
            for (EntityLink* link = front_->next(); link->next();
                    link = link->next()) {
                (link->entity()->*method)(args...);
            }
        }
    };

}