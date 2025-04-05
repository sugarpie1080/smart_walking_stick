import fastdds
class Reader:
    def __init__(self,set_name, topic_name, topic_data_type,listener):
        self.set_name = set_name
        self.topic_name = topic_name
        # self.topic_class = topic_class
        self.listener = listener()

        factory = fastdds.DomainParticipantFactory.get_instance()
        participant_qos = fastdds.DomainParticipantQos()
        factory.get_default_participant_qos(participant_qos)
        self.participant = factory.create_participant(0, participant_qos)

        self.topic_data_type = topic_data_type()
        self.topic_data_type.set_name(self.set_name)
        type_support = fastdds.TypeSupport(self.topic_data_type)
        self.participant.register_type(type_support)

        topic_qos = fastdds.TopicQos()
        self.participant.get_default_topic_qos(topic_qos)
        self.topic = self.participant.create_topic(self.topic_name, self.topic_data_type.get_name(), topic_qos)

        subscriber_qos = fastdds.SubscriberQos()
        self.participant.get_default_subscriber_qos(subscriber_qos)
        self.subscriber = self.participant.create_subscriber(subscriber_qos)

        reader_qos = fastdds.DataReaderQos()
        self.subscriber.get_default_datareader_qos(reader_qos)
        self.reader = self.subscriber.create_datareader(self.topic, reader_qos, self.listener)

    def delete(self):
        factory = fastdds.DomainParticipantFactory.get_instance()
        self.participant.delete_contained_entities()
        factory.delete_participant(self.participant)