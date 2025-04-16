import fastdds
from flask_socketio import SocketIO

"""@package docstring
Documentation for Reader class.

This class is responsible for creating a subscriber that connects to a FastDDS publisher. It handles the initialization of FastDDS entities, including participants, topics, subscribers, and data readers.
"""

class Reader:
    """
    Represents a FastDDS subscriber that reads data published by a FastDDS publisher.

    The class sets up necessary FastDDS components to subscribe to a specific topic and uses a listener to handle data availability events.

    Attributes:
        set_name (str): The name of the data type associated with the topic.
        topic_name (str): The name of the topic to subscribe to.
        topic_data_type: The FastDDS data type associated with the topic.
        listener: The listener class for processing received data.
        socketio (SocketIO): The Socket.IO instance used for transmitting updates to web clients.
        participant: The FastDDS participant entity for communication.
        topic: The FastDDS topic entity.
        subscriber: The FastDDS subscriber entity.
        reader: The FastDDS data reader entity.
    """
    def __init__(self, set_name, topic_name, topic_data_type, listener, socketio):
        """
        Initializes the Reader class.

        Creates and configures FastDDS entities required for subscribing to data topics and reading data samples.
        """
        self.set_name = set_name
        self.topic_name = topic_name
        self.listener = listener(socketio)

        # Initialize FastDDS participant
        factory = fastdds.DomainParticipantFactory.get_instance()
        participant_qos = fastdds.DomainParticipantQos()
        factory.get_default_participant_qos(participant_qos)
        self.participant = factory.create_participant(0, participant_qos)

        # Register topic data type
        self.topic_data_type = topic_data_type()
        self.topic_data_type.set_name(self.set_name)
        type_support = fastdds.TypeSupport(self.topic_data_type)
        self.participant.register_type(type_support)

        # Create FastDDS topic
        topic_qos = fastdds.TopicQos()
        self.participant.get_default_topic_qos(topic_qos)
        self.topic = self.participant.create_topic(self.topic_name, self.topic_data_type.get_name(), topic_qos)

        # Create FastDDS subscriber
        subscriber_qos = fastdds.SubscriberQos()
        self.participant.get_default_subscriber_qos(subscriber_qos)
        self.subscriber = self.participant.create_subscriber(subscriber_qos)

        # Create FastDDS data reader
        reader_qos = fastdds.DataReaderQos()
        self.subscriber.get_default_datareader_qos(reader_qos)
        self.reader = self.subscriber.create_datareader(self.topic, reader_qos, self.listener)

    def delete(self):
        """
        Cleans up FastDDS entities.

        Deletes all contained entities in the participant and releases resources.

        This method should be called to safely remove the DDS entities when they are no longer needed.

        @return: None
        """
        factory = fastdds.DomainParticipantFactory.get_instance()
        self.participant.delete_contained_entities()
        factory.delete_participant(self.participant)
