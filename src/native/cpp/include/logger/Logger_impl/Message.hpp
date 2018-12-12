#ifndef TPFINALAYDAI_MESSAGE_HPP
#define TPFINALAYDAI_MESSAGE_HPP

#include <string>
#include <optional>
#include <algor/List.hpp>
#include <algor/GeometricObject.hpp>
#include <logger/Logger_impl/LogTypes.hpp>

namespace logger {
    class Logger;
}

namespace logger::__detail_Logger {
    class Message {
        const std::string * message = nullptr;
        std::optional<algor::List<algor::GeometricObject *>> attached_objects;
        FlagType flags;

    protected:
        Message() = default;

        explicit Message(FlagType flags, const std::string * message)
                : flags(flags), message(message)
        {}

        Message(FlagType flags, const std::string * message, algor::GeometricObject * object)
                : flags(flags), message(message), attached_objects({object})
        {}

        Message(FlagType flags, const std::string * message, algor::List<algor::GeometricObject *> objects)
                : flags(flags), message(message), attached_objects(std::move(objects))
        {}

        friend class logger::Logger;

        void setFlags(FlagType flags) {
            this->flags = flags;
        }

        void setMessage(const std::string * message) {
            this->message = message;
        }

        void setAttachedObjects(algor::List<algor::GeometricObject *> attachedObjects) {
            this->attached_objects = std::move(attachedObjects);
        }

        void free_memory() {
            delete this->message;
            this->message = nullptr;

            if(this->attached_objects.has_value()) {
                while(!this->attached_objects->isEmpty()) {
                    delete this->attached_objects->remove(
                            this->attached_objects->begin()
                    );
                }
                this->attached_objects = std::nullopt;
            }
        }

    public:
        virtual ~Message() = default;

        bool hasAttachments() const {
            return this->attached_objects.has_value();
        }

        const auto & getAttachments() const {
            return *(this->attached_objects);
        }

        const auto & getMessage() const {
            return *(this->message);
        }

        FlagType getFlags() const {
            return this->flags;
        }
    };

    class OwnerMessage : public Message {
        explicit OwnerMessage(Message const& message) {
            this->setMessage(new std::string(message.getMessage()));
            this->setFlags(message.getFlags());

            if(message.hasAttachments()) {
                algor::List<algor::GeometricObject *> objects;

                auto it = message.getAttachments().begin();
                auto end = message.getAttachments().end();
                for(; it!=end; ++it) {
                    objects.add((*it)->clone());
                }

                this->setAttachedObjects(std::move(objects));
            }
        }

        friend class logger::Logger;

    public:
        ~OwnerMessage() override {
            this->free_memory();
        }
    };
}

#endif //TPFINALAYDAI_MESSAGE_HPP
