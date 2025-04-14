import signal
import flask
from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import fastdds
import ToFData
# Custom ReaderListener to receive DDS data and emit via WebSocket
class ReaderListenerToF(fastdds.DataReaderListener):
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
        distance = data.distance()
        # battery=data.battery()
        sec=data.sec()

        print("values:")
        print(distance,sec)

        if reader.take_next_sample(data, info):
            print(f"Received data: Seconds={data.sec()}, Battery={0.0}, Distance={data.distance()}")  # Debug output
            # Emit data to connected WebSocket clients
            self.socketio.emit('update_data', {'sec': data.sec(), 'battery': 0.0, 'distance': data.distance()})
        else:
            print("No data received or data invalid.")