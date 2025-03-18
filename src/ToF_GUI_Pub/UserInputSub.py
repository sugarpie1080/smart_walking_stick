import signal
from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import fastdds
import ToFData

DESCRIPTION = """ToF Subscriber for Fast DDS python bindings"""
USAGE = ('python3 ToFSubscriber.py')

# Flask app setup
app = Flask(__name__)
socketio = SocketIO(app)

# To capture ctrl+C
def signal_handler(sig, frame):
    print('Interrupted!')

class ReaderListener(fastdds.DataReaderListener):
    def __init__(self, socketio):
        super().__init__()
        self.socketio = socketio

    def on_subscription_matched(self, datareader, info):
        if info.current_count_change > 0:
            print(f"Subscriber matched publisher {info.last_publication_handle}")
        else:
            print(f"Subscriber unmatched publisher {info.last_publication_handle}")

    def on_data_available(self, reader):
        info = fastdds.SampleInfo()
        data = ToFData.ToFData()
        reader.take_next_sample(data, info)
        if reader.take_next_sample(data, info) and info.valid_data:
            try:
                threshold = data.threshold()
                intensity = data.intensity()
                enable = data.enable()
                print(f"Received data: Threshold={threshold}, Intensity={intensity}, Enable={enable}")
                # Emit data to connected WebSocket clients
                self.socketio.emit('update_data', {'threshold': threshold, 'intensity': intensity, 'enable': enable})
            except Exception as e:
                print(f"Error processing data: {e}")
        else:
            print("No valid data received.")

class Reader:
    def __init__(self, socketio):
        factory = fastdds.DomainParticipantFactory.get_instance()
        self.participant_qos = fastdds.DomainParticipantQos()
        factory.get_default_participant_qos(self.participant_qos)
        self.participant = factory.create_participant(0, self.participant_qos)

        self.topic_data_type = ToFData.ToFDataPubSubType()
        self.topic_data_type.set_name("ToFData")
        self.type_support = fastdds.TypeSupport(self.topic_data_type)
        self.participant.register_type(self.type_support)

        self.topic_qos = fastdds.TopicQos()
        self.participant.get_default_topic_qos(self.topic_qos)
        self.topic = self.participant.create_topic("UserInputTopic", self.topic_data_type.get_name(), self.topic_qos)

        self.subscriber_qos = fastdds.SubscriberQos()
        self.participant.get_default_subscriber_qos(self.subscriber_qos)
        self.subscriber = self.participant.create_subscriber(self.subscriber_qos)

        # Initialize reader_qos here
        self.reader_qos = fastdds.DataReaderQos()
        self.subscriber.get_default_datareader_qos(self.reader_qos)

        # Customize QoS settings (optional)
        self.reader_qos.reliability().kind = fastdds.RELIABLE_RELIABILITY_QOS
        self.reader_qos.durability().kind = fastdds.VOLATILE_DURABILITY_QOS

        self.listener = ReaderListener(socketio)
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
    reader = Reader(socketio)
    reader.run()
    exit()
