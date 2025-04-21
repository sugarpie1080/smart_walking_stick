"""
@file ReaderListenerBattery.py
@Author: Kyle Watt, Felicity Lipscomb
@Date: 2025-04-16
"""
import signal
import flask
from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import fastdds
import Battery

"""@package docstring
Documentation for ReaderListenerBattery.py.

This script defines the ReaderListenerBattery class, which listens for Battery (Time-of-Flight) data updates via FastDDS and emits the received data to WebSocket clients using Socket.IO.
"""

class ReaderListenerBattery(fastdds.DataReaderListener):
    """
    Creates a new class called ReaderListenerBattery that inherits from fastdds.DataReaderListener.

    The class is responsible for:
    - Handling FastDDS subscription events.
    - Receiving and processing Battery data.
    - Transmitting the received data to a connected Socket.IO server.

    Attributes:
        socketio (SocketIO): The Socket.IO instance used to emit data updates to connected clients.
    """
    def __init__(self, socketio):
        """
        Initializes the ReaderListenerBattery class.
        """
        super().__init__()
        self.socketio = socketio

    def on_subscription_matched(self, datareader, info):
        """
        Callback function triggered when a subscription matches or unmatches.

        Logs whether the subscriber has matched or unmatched with a publisher.
        """
        if info.current_count_change > 0:
            print(f"Subscriber matched publisher {info.last_publication_handle}")
        else:
            print(f"Subscriber unmatched publisher {info.last_publication_handle}")

    def on_data_available(self, reader):
        """
        Callback function triggered when new data is available from the reader.

        This method performs the following steps:
        1. Reads the next sample from the DataReader.
        2. Extracts the `time left` and `sec` values from the Battery object.
        3. Emits the received data (distance, time, and a placeholder battery level) to Socket.IO clients.

        Emits:
            - 'update_data': Sends the received data as a dictionary containing:
                - 'sec' (int): The timestamp in seconds.
                - 'battery' (float): Placeholder value for battery status (currently set to 0.0).
                - 'battery_percentage' (float): The measured battery_percentage.
        """
        info = fastdds.SampleInfo()
        data = Battery.Battery()

        # Attempt to take the next sample from the reader
        reader.take_next_sample(data, info)
        battery_percentage = data.battery_percentage()
        sec = data.sec()

        # Debugging: Print received values
        print("values:")
        print(battery_percentage, sec)

        if reader.take_next_sample(data, info):
            # Debug output
            print(f"Received data: Seconds={data.sec()}, Battery= {data.battery_percentage()}")

            # Emit the data to connected WebSocket clients
            self.socketio.emit('update_data_battery', {
                'sec': data.sec(),
                'time_left': data.battery_percentage()
            })
        else:
            # Log an error if no valid data is received
            print("No data received or data invalid.")
