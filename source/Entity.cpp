#include <Entity.hpp>

namespace gl {
    EntityLink::EntityLink(Entity* entity) :
        next_(nullptr), last_(nullptr), entity_(entity)
    {}

    EntityLink::~EntityLink() {
        if(entity_)
            delete entity_;
    }
    EntityLink* EntityLink::setNext(EntityLink* link) {
        EntityLink* tmp = next_;
        next_ = link;
        return tmp;
    }
    EntityLink* EntityLink::setLast(EntityLink* link) {
        EntityLink* tmp = last_;
        last_ = link;
        return tmp;
    }

    void EntityLink::breakFromList() {
        if (next_)
            next_->setLast(last_);
        next_ = nullptr;
        if (last_)
            last_->setNext(next_);
        last_ = nullptr;
    }

    bool EntityLink::pushFront(EntityList* list) {
        if (!list) return false;
        breakFromList();
        list->appendFront(this);
    }
    bool EntityLink::pushBack(EntityList* list) {
        if (!list) return false;
        breakFromList();
        list->appendFront(this);
    }
    bool EntityLink::moveForward(size_t n) {
        if (!last_ || !n) return !(bool)n;
        EntityLink* link = last_;
        breakFromList();
        size_t i = 1;
        while (i < n) {
            if (!link->last()->last()) break;
            link = link->last(); 
            i++;
        }

        // Insert Link
        link->last()->setNext(this);
        last_ = link->last();
        link->setLast(this);
        next_ = link;
        return !(i < n);
    }

    bool EntityLink::moveBackward(size_t n) {
        if (!next_ || !n) return !(bool)n;
        EntityLink* link = next_;
        breakFromList();
        size_t i = 1;
        while (i < n) {
            if (!link->next()->next()) break;
            link = link->next(); 
            i++;
        }

        // Insert Link
        link->next()->setLast(this);
        next_ = link->next();
        link->setNext(this);
        last_ = link;
        return !(i < n);
    }

    EntityList::EntityList() :
        front_(new EntityLink(nullptr)),
        last_(new EntityLink(nullptr))
    {
        front_->setNext(last_);
        last_->setLast(front_);
    }
    EntityList::~EntityList() {
        EntityLink* link;
        for (link = front_; link; link = link->next()) {
            delete link;
        }
    }
    
    void EntityList::appendFront(EntityLink* entity) {
        front_->next()->setLast(entity);
        entity->setNext(front_->next());
        front_->setNext(entity);
        entity->setLast(front_);
    }

    void EntityList::appendBack(EntityLink* entity) {
        last_->last()->setNext(entity);
        entity->setLast(last_->last());
        last_->setLast(entity);
        entity->setNext(last_);
    }

    void EntityList::render(const glm::mat4 &projection) {
        for (EntityLink* link = front_->next(); link->next();
                link = link->next()) {
            link->entity()->render(projection);
        }
    }
    void EntityList::update(const GameData &gameData) {
        for (EntityLink* link = front_->next(); link->next();
                link = link->next()) {
            link->entity()->update(gameData);
        }
    }
    
}