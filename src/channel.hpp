#pragma once

#include "concurrentmap.hpp"
#include "emotemanager.hpp"
#include "logging/loggingchannel.hpp"
#include "messages/lazyloadedimage.hpp"
#include "messages/limitedqueue.hpp"

#include <QMap>
#include <QMutex>
#include <QString>
#include <QVector>
#include <boost/signals2.hpp>

#include <memory>
#include <set>

namespace chatterino {
namespace messages {
class Message;
}

class Channel
{
public:
    explicit Channel(const QString &_name);

    boost::signals2::signal<void(messages::SharedMessage &)> messageRemovedFromStart;
    boost::signals2::signal<void(messages::SharedMessage &)> messageAppended;

    virtual bool isEmpty() const;
    messages::LimitedQueueSnapshot<messages::SharedMessage> getMessageSnapshot();

    void addMessage(messages::SharedMessage message);
    void addRecentChatter(const QString &username);

    std::set<QString> getUsernamesForCompletions();

    QString name;
    QStringList modList;

    std::mutex recentChattersMutex;
    std::set<QString> recentChatters;

    virtual bool canSendMessage() const;
    virtual void sendMessage(const QString &message);

private:
    messages::LimitedQueue<messages::SharedMessage> messages;

    // std::shared_ptr<logging::Channel> loggingChannel;
};

}  // namespace chatterino
