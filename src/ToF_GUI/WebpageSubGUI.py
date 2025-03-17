import signal
import flask
from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import fastdds
import ToFData

app = Flask(__name__)
socketio = SocketIO(app)

# Route to serve the webpage
@app.route('/')
def index():
    return render_template('index.html')

# Custom ReaderListener to receive DDS data and emit via WebSocket
class ReaderListener(fastdds.DataReaderListener):
    def on_subscription_matched(self, datareader, info):
        if info.current_count_change > 0:
            print(f"Subscriber matched publisher {info.last_publication_handle}")
        else:
            print(f"Subscriber unmatched publisher {info.last_publication_handle}")

    def on_data_available(self, reader):
        info = fastdds.SampleInfo()
        data = ToFData.ToFData()
        reader.take_next_sample(data, info)
        distance = data.distance()
        nanosec=data.nanosec()
        sec=data.sec()

        print("values:")
        print(distance,nanosec,sec)

        if reader.take_next_sample(data, info):
            print(f"Received data: Seconds={data.sec()}, Nanoseconds={data.nanosec()}, Distance={data.distance()}")  # Debug output
            # Emit data to connected WebSocket clients
            socketio.emit('update_data', {'sec': data.sec(), 'nanosec': data.nanosec(), 'distance': data.distance()})
        else:
            print("No data received or data invalid.")


class Reader:
    def __init__(self):
        factory = fastdds.DomainParticipantFactory.get_instance()
        participant_qos = fastdds.DomainParticipantQos()
        factory.get_default_participant_qos(participant_qos)
        self.participant = factory.create_participant(0, participant_qos)

        topic_data_type = ToFData.ToFDataPubSubType()
        topic_data_type.set_name("ToFData")
        type_support = fastdds.TypeSupport(topic_data_type)
        self.participant.register_type(type_support)

        topic_qos = fastdds.TopicQos()
        self.participant.get_default_topic_qos(topic_qos)
        self.topic = self.participant.create_topic("ToFDataTopic", topic_data_type.get_name(), topic_qos)

        subscriber_qos = fastdds.SubscriberQos()
        self.participant.get_default_subscriber_qos(subscriber_qos)
        self.subscriber = self.participant.create_subscriber(subscriber_qos)

        self.listener = ReaderListener()
        reader_qos = fastdds.DataReaderQos()
        self.subscriber.get_default_datareader_qos(reader_qos)
        self.reader = self.subscriber.create_datareader(self.topic, reader_qos, self.listener)

    def delete(self):
        factory = fastdds.DomainParticipantFactory.get_instance()
        self.participant.delete_contained_entities()
        factory.delete_participant(self.participant)

if __name__ == '__main__':
    # Create the DDS reader
    reader = Reader()

    # Capture Ctrl+C signal to clean up
    signal.signal(signal.SIGINT, lambda sig, frame: reader.delete() or exit(0))

    # Start the Flask web server
    socketio.run(app, host='0.0.0.0', port=5000)
