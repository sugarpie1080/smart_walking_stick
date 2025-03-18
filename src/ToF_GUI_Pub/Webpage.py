import signal
from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import fastdds
import ToFData

app = Flask(__name__)
socketio = SocketIO(app)

@app.route('/')
def index():
    return render_template('index.html')

# Fast DDS Writer for User Inputs
class Writer:
    def __init__(self):
        factory = fastdds.DomainParticipantFactory.get_instance()
        participant_qos = fastdds.DomainParticipantQos()
        factory.get_default_participant_qos(participant_qos)
        self.participant = factory.create_participant(0, participant_qos)

        # Register the type for user input data
        topic_data_type = ToFData.ToFDataPubSubType()
        topic_data_type.set_name("ToFData")
        type_support = fastdds.TypeSupport(topic_data_type)
        self.participant.register_type(type_support)

        # Create topic for user inputs
        topic_qos = fastdds.TopicQos()
        self.participant.get_default_topic_qos(topic_qos)
        self.topic = self.participant.create_topic("UserInputTopic", topic_data_type.get_name(), topic_qos)

        # Create a publisher
        publisher_qos = fastdds.PublisherQos()
        self.participant.get_default_publisher_qos(publisher_qos)
        self.publisher = self.participant.create_publisher(publisher_qos)

        # Initialize the data writer
        self.writer_qos = fastdds.DataWriterQos()
        self.publisher.get_default_datawriter_qos(self.writer_qos)

        # QoS Settings (optional, adjust as needed)
        self.writer_qos.reliability().kind = fastdds.RELIABLE_RELIABILITY_QOS
        self.writer_qos.durability().kind = fastdds.VOLATILE_DURABILITY_QOS

        # Create the writer
        self.writer = self.publisher.create_datawriter(self.topic, self.writer_qos)

        if self.writer is None:
            raise RuntimeError("Failed to create DataWriter for UserInputTopic")

    def publish_user_inputs(self, threshold, intensity, enable):
        # Create and populate the data
        data = ToFData.ToFData()
        data.threshold(threshold)
        data.intensity(intensity)
        data.enable(enable)

        # Write data using the DataWriter
        self.writer.write(data)
        print(f"Published user inputs: Threshold={threshold}, Intensity={intensity}, Enable={enable}")


# Initialize Fast DDS Writer
dds_writer = Writer()

# DDS Reader to Receive and Broadcast Data
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
        battery=data.battery()
        sec=data.sec()


        if reader.take_next_sample(data, info):
            #print(f"Received data: Seconds={data.sec()}, Battery={data.battery()}, Distance={data.distance()}")  # Debug output
            # Emit data to connected WebSocket clients
            socketio.emit('update_data', {'sec': data.sec(), 'battery': data.battery(), 'distance': data.distance()})
        else:
            print("No data received or data invalid.")


class Reader:
    def __init__(self):
        factory = fastdds.DomainParticipantFactory.get_instance()
        participant_qos = fastdds.DomainParticipantQos()
        factory.get_default_participant_qos(participant_qos)
        self.participant = factory.create_participant(0, participant_qos)

        # Register and create topic
        topic_data_type = ToFData.ToFDataPubSubType()
        topic_data_type.set_name("ToFData")
        type_support = fastdds.TypeSupport(topic_data_type)
        self.participant.register_type(type_support)

        topic_qos = fastdds.TopicQos()
        self.participant.get_default_topic_qos(topic_qos)
        self.topic = self.participant.create_topic("ToFDataTopic", topic_data_type.get_name(), topic_qos)

        # Create subscriber
        subscriber_qos = fastdds.SubscriberQos()
        self.participant.get_default_subscriber_qos(subscriber_qos)
        self.subscriber = self.participant.create_subscriber(subscriber_qos)

        # Attach listener to the data reader
        self.listener = ReaderListener()
        reader_qos = fastdds.DataReaderQos()
        self.subscriber.get_default_datareader_qos(reader_qos)
        self.reader = self.subscriber.create_datareader(self.topic, reader_qos, self.listener)

    def delete(self):
        factory = fastdds.DomainParticipantFactory.get_instance()
        self.participant.delete_contained_entities()
        factory.delete_participant(self.participant)

# Handle WebSocket Events
@socketio.on('update_controls')
def handle_controls_update(data):
    #print("DEBUG: WebSocket event triggered")  # Add debug log here
    #print("DEBUG: Received WebSocket data:", data)  # Log the incoming data

    try:
        threshold = int(data['threshold'])
        intensity = int(data['intensity'])
        enable = data['enable']
        #print(f"Parsed user controls: Threshold={threshold}, Intensity={intensity}, Enable={enable}")
    except Exception as e:
        print(f"ERROR: Failed to parse user controls: {e}")

    dds_writer.publish_user_inputs(threshold, intensity, enable)

if __name__ == '__main__':
    # Create DDS Reader
    reader = Reader()

    # Handle exit signal
    signal.signal(signal.SIGINT, lambda sig, frame: reader.delete() or exit(0))

    # Run Flask Web Server with WebSocket Support
    socketio.run(app, host='0.0.0.0', port=5000)
