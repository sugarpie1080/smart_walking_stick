import signal
import fastdds
import sys

DESCRIPTION = """DDS Subscriber for Fast DDS Python bindings"""
USAGE = ('python3 GenericSubscriber.py')

# To capture ctrl+C
def signal_handler(sig, frame):
    print('Interrupted!')

class ReaderListener(fastdds.DataReaderListener):

    def __init__(self):
        super().__init__()

    def on_subscription_matched(self, datareader, info):
        if (0 < info.current_count_change):
            print(f"Subscriber matched publisher {info.last_publication_handle}")
        else:
            print(f"Subscriber unmatched publisher {info.last_publication_handle}")

    def on_data_available(self, reader):
        info = fastdds.SampleInfo()
        data = reader.take_next_sample(info)
        print(f"Received Data: {data}, Info: {info}")

class Reader:

    def __init__(self, topic_name: str, topic_type: fastdds.TypeSupport):
        factory = fastdds.DomainParticipantFactory.get_instance()
        self.participant_qos = fastdds.DomainParticipantQos()
        factory.get_default_participant_qos(self.participant_qos)
        self.participant = factory.create_participant(0, self.participant_qos)

        self.topic_data_type = topic_type
        self.topic_data_type.set_name(topic_name)
        self.type_support = fastdds.TypeSupport(self.topic_data_type)
        self.participant.register_type(self.type_support)

        self.topic_qos = fastdds.TopicQos()
        self.participant.get_default_topic_qos(self.topic_qos)
        self.topic = self.participant.create_topic(topic_name, self.topic_data_type.get_name(), self.topic_qos)

        self.subscriber_qos = fastdds.SubscriberQos()
        self.participant.get_default_subscriber_qos(self.subscriber_qos)
        self.subscriber = self.participant.create_subscriber(self.subscriber_qos)

        self.listener = ReaderListener()
        self.reader_qos = fastdds.DataReaderQos()
        self.subscriber.get_default_datareader_qos(self.reader_qos)
        self.reader = self.subscriber.create_datareader(self.topic, self.reader_qos, self.listener)

    def delete(self):
        factory = fastdds.DomainParticipantFactory.get_instance()
        self.participant.delete_contained_entities()
        factory.delete_participant(self.participant)

    def run(self):
        signal.signal(signal.SIGINT, signal_handler)
        print('Press Ctrl+C to stop')
        signal.pause()
        self.delete()

if __name__ == '__main__':
    print('Creating subscriber.')
    import ToFData
    topic_name = "ToFData"
    topic_type = ToFData.ToFDataPubSubType()

    reader = Reader(topic_name, topic_type)
    reader.run()
    exit()
