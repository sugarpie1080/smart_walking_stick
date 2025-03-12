import sys
import signal
from PyQt5.QtWidgets import QApplication, QLabel, QVBoxLayout, QWidget

import fastdds
import ToFData

# PyQt5 GUI Class
class ToFDataDisplay(QWidget):
    def __init__(self):
        super().__init__()

        self.init_ui()

    def init_ui(self):
        self.setWindowTitle("ToF Data Display")

        # Create labels to display the data
        self.sec_label = QLabel("Seconds: 0")
        self.nanosec_label = QLabel("Nanoseconds: 0")
        self.distance_label = QLabel("Distance: 0.0 mm")

        # Arrange widgets vertically
        layout = QVBoxLayout()
        layout.addWidget(self.sec_label)
        layout.addWidget(self.nanosec_label)
        layout.addWidget(self.distance_label)

        self.setLayout(layout)

    def update_data(self, sec, nanosec, distance):
        # Update the labels with new data
        self.sec_label.setText(f"Seconds: {sec}")
        self.nanosec_label.setText(f"Nanoseconds: {nanosec}")
        self.distance_label.setText(f"Distance: {distance} mm")


# Custom ReaderListener to receive DDS data and update GUI
class ReaderListener(fastdds.DataReaderListener):
    def __init__(self, gui):
        super().__init__()
        self.gui = gui

    def on_subscription_matched(self, datareader, info):
        if 0 < info.current_count_change:
            print(f"Subscriber matched publisher {info.last_publication_handle}")
        else:
            print(f"Subscriber unmatched publisher {info.last_publication_handle}")

    def on_data_available(self, reader):
        info = fastdds.SampleInfo()
        data = ToFData.ToFData()

        if reader.take_next_sample(data, info):
            # Extract the data and update the GUI
            sec = data.sec()
            nanosec = data.nanosec()
            distance = data.distance()

            # Update the PyQt5 GUI
            self.gui.update_data(sec, nanosec, distance)


class Reader:
    def __init__(self, gui):
        self.gui = gui
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
        self.topic = self.participant.create_topic("ToFDataTopic", self.topic_data_type.get_name(), self.topic_qos)

        self.subscriber_qos = fastdds.SubscriberQos()
        self.participant.get_default_subscriber_qos(self.subscriber_qos)
        self.subscriber = self.participant.create_subscriber(self.subscriber_qos)

        self.listener = ReaderListener(self.gui)
        self.reader_qos = fastdds.DataReaderQos()
        self.subscriber.get_default_datareader_qos(self.reader_qos)
        self.reader = self.subscriber.create_datareader(self.topic, self.reader_qos, self.listener)

    def delete(self):
        factory = fastdds.DomainParticipantFactory.get_instance()
        self.participant.delete_contained_entities()
        factory.delete_participant(self.participant)


if __name__ == '__main__':
    # Create the PyQt5 application
    app = QApplication(sys.argv)
    tof_display = ToFDataDisplay()
    tof_display.show()

    # Start the DDS reader
    print("Creating subscriber.")
    reader = Reader(tof_display)

    # Capture Ctrl+C signal to clean up
    signal.signal(signal.SIGINT, lambda sig, frame: reader.delete() or app.quit())

    # Start the Qt event loop
    sys.exit(app.exec_())
