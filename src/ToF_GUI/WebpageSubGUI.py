"""
@file WebpageSubGUI.py
@Author: Kyle Watt
@Date: 2025-04-16
"""
import signal
import flask
from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import fastdds
import sys
sys.path.append("/usr/local/lib/python3/dist-packages/")
import ToFData
import MotorCommands
import Battery
from Reader import Reader
from ReaderListenerToF import ReaderListenerToF
from ReaderListenerMotor import ReaderListenerMotor
from ReaderListenerBattery import ReaderListenerBattery

"""@package docstring
Documentation for WebpageSubGUI.py.

This script sets up a Flask web application with Socket.IO integration. It uses FastDDS to subscribe to data topics (`ToFData` and `MotorCommands`) 
and emits the received data to connected WebSocket clients. The application serves as the control panel for a smart device like a walking stick.
"""

app = Flask(__name__)
socketio = SocketIO(app)

# Route to serve the webpage
@app.route('/')
def index():
    """
    Serves the main webpage.

    This route renders the `index.html` file, which contains the user interface for the smart walking stick control panel.

    @return: Rendered HTML template for the webpage.
    """
    return render_template('index.html')

if __name__ == '__main__':
    """
    Main entry point for running the Flask application.

    Steps performed:
    1. Initializes the Socket.IO instance.
    2. Creates FastDDS readers for `ToFData` and `MotorCommands` topics.
    3. Starts the Flask web server.

    Signal Handling:
    - The script listens for the SIGINT signal (Ctrl+C) and cleans up the DDS reader before exiting.
    """
    socketio = SocketIO(app)

    # Create the DDS reader for Time-of-Flight data
    reader = Reader(
        set_name="ToFData",
        topic_name="ToFDataTopic",
        topic_data_type=ToFData.ToFDataPubSubType,
        listener=ReaderListenerToF,
        socketio=socketio
    )

    # Create the DDS reader for MotorCommands data
    reader_motor = Reader(
        set_name="MotorCommands",
        topic_name="MotorCommandsTopic",
        topic_data_type=MotorCommands.MotorCommandsPubSubType,
        listener=ReaderListenerMotor,
        socketio=socketio
    )

    reader_battery = Reader(
        set_name="Battery",
        topic_name="BatteryCommandsTopic",
        topic_data_type=Battery.MotorCommandsPubSubType,
        listener=ReaderListenerBattery
        socketio=socketio
    )

    # Capture Ctrl+C signal to clean up DDS resources
    signal.signal(signal.SIGINT, lambda sig, frame: reader.delete() or exit(0))

    # Start the Flask web server with Socket.IO
    socketio.run(app, host='0.0.0.0', port=5000)
