from threading import Condition
import time
import fastdds
import ToFData

class WriterListener(fastdds.DataWriterListener):
    def __init__(self, writer):
        self._writer = writer
        super().__init__()

    def on_publication_matched(self, datawriter, info):
        if info.current_count_change > 0:
            print(f"Publisher matched subscriber {info.last_subscription_handle}")
            self._writer._cvDiscovery.acquire()
            self._writer._matched_reader += 1
            self._writer._cvDiscovery.notify()
            self._writer._cvDiscovery.release()
        else:
            print(f"Publisher unmatched subscriber {info.last_subscription_handle}")
            self._writer._cvDiscovery.acquire()
            self._writer._matched_reader -= 1
            self._writer._cvDiscovery.notify()
            self._writer._cvDiscovery.release()


class Writer:
    def __init__(self):
        self._matched_reader = 0
        self._cvDiscovery = Condition()
        self.index = 0

        factory = fastdds.DomainParticipantFactory.get_instance()
        participant_qos = fastdds.DomainParticipantQos()
        factory.get_default_participant_qos(participant_qos)
        self.participant = factory.create_participant(0, participant_qos)

        self.topic_data_type = ToFData.ToFDataPubSubType()
        self.topic_data_type.set_name("ToFData")
        self.type_support = fastdds.TypeSupport(self.topic_data_type)
        self.participant.register_type(self.type_support)

        self.topic_qos = fastdds.TopicQos()
        self.participant.get_default_topic_qos(self.topic_qos)
        self.topic = self.participant.create_topic("ToFDataTopic", self.topic_data_type.get_name(), self.topic_qos)

        self.publisher_qos = fastdds.PublisherQos()
        self.participant.get_default_publisher_qos(self.publisher_qos)
        self.publisher = self.participant.create_publisher(self.publisher_qos)

        self.listener = WriterListener(self)
        self.writer_qos = fastdds.DataWriterQos()
        self.publisher.get_default_datawriter_qos(self.writer_qos)
        self.writer = self.publisher.create_datawriter(self.topic, self.writer_qos, self.listener)

    def write(self):
        data = ToFData.ToFData()
        data.distance(float(150.0))  # Example distance value
        data.sec(self.index)
        
        # Simulating battery percentage
        battery_level = int(max(0, 100 - (self.index % 100)))  # Gradual battery drain, resets at 0
        data.battery(battery_level)

        self.writer.write(data)
        print(f"Sending data: Seconds={data.sec()}, Distance={data.distance()}, Battery={data.battery()}%")
        self.index += 1

    def wait_discovery(self):
        self._cvDiscovery.acquire()
        print("Writer is waiting for discovery...")
        self._cvDiscovery.wait_for(lambda: self._matched_reader != 0)
        self._cvDiscovery.release()
        print("Writer discovery finished...")

    def run(self):
        self.wait_discovery()
        for _ in range(1000):  # Send 1000 samples for demonstration
            time.sleep(1)
            self.write()
        self.delete()

    def delete(self):
        factory = fastdds.DomainParticipantFactory.get_instance()
        self.participant.delete_contained_entities()
        factory.delete_participant(self.participant)


if __name__ == '__main__':
    print("Starting publisher...")
    writer = Writer()
    writer.run()
