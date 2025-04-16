"""
@file ReaderListenerMotor.py
@Author: Kyle Watt, Felicity Lipscomb
@Date: 2025-04-16
"""
import signal
import flask
from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import fastdds
import MotorCommands

"""@package docstring
Documentation for ReaderListenerMotor.py.

This script defines the ReaderListenerMotor class, which acts as a listener for FastDDS data and emits updates to a Socket.IO connection for web-based display.
"""

class ReaderListenerMotor(fastdds.DataReaderListener):
    """
    Creates a new class called ReaderListenerMotor which is a child of the parent class fastdds.DataReaderListener.

    The class is responsible for:
    - Listening for FastDDS data updates via the DataReaderListener interface.
    - Transmitting received FastDDS data to a connected Socket.IO server.

    Attributes:
        socketio (SocketIO): The Socket.IO instance used to emit data updates to connected clients.
    """
    def __init__(self, socketio):
        """
        Initializes the ReaderListenerMotor class.
        """
        super().__init__()
        self.socketio = socketio

    def on_subscription_matched(self, datareader, info):
        """
        Callback function triggered when the subscription state changes.

        Logs whether the subscriber has matched or unmatched with a publisher.
        """
        if info.current_count_change > 0:
            print(f"Subscriber matched publisher {info.last_publication_handle}")
        else:
            print(f"Subscriber unmatched publisher {info.last_publication_handle}")

    def on_data_available(self, reader):
        """
        Callback function triggered when data is available from the reader.

        This method takes the next sample, extracts FastDDS data, and emits it through the Socket.IO connection.
        If no data is available, logs an error message.

        Emits:
            - 'update_motor_data': Transmits duty cycle and seconds to WebSocket clients.
        """
        info = fastdds.SampleInfo()
        data = MotorCommands.MotorCommands()

        # Take the next sample from the reader
        reader.take_next_sample(data, info)
        duty_cycle = data.duty_cycle()
        sec = data.sec()

        # Print debug information
        print(f"Received data: Seconds={data.sec()}, Duty Cycle={data.duty_cycle()}")

        if reader.take_next_sample(data, info):
            # Emit data to connected WebSocket clients
            self.socketio.emit('update_motor_data', {'duty_cycle': duty_cycle, 'sec': sec})
        else:
            print("No data received or data invalid.")
