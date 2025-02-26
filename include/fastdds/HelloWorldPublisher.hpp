#ifndef HELLO_WORLD_PUBLISHER_HPP
#define HELLO_WORLD_PUBLISHER_HPP
#include "BasePublisher.hpp"
#include "HelloWorldMsgPubSubTypes.h"

class HelloWorldPublisher : public BasePublisher<HelloWorldMsg, HelloWorldMsgPubSubType> {
public:
    HelloWorldPublisher() : BasePublisher("HelloWorldTopic"){}
    
};

#endif
