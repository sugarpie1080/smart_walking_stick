import signal
import flask
from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import fastdds
import sys
sys.path.append("/usr/local/lib/python3/dist-packages/")
import ToFData
import MotorCommands
from Reader import Reader
from ReaderListenerToF import ReaderListenerToF
from ReaderListenerMotor import ReaderListenerMotor

app = Flask(__name__)
socketio = SocketIO(app)

# Route to serve the webpage
@app.route('/')
def index():
    return render_template('index.html')


if __name__ == '__main__':
    socketio = SocketIO(app)

    # Create the DDS reader
    reader = Reader(set_name="ToFData", topic_name="ToFDataTopic", topic_data_type=ToFData.ToFDataPubSubType,listener=ReaderListenerToF,socketio=socketio)
    reader_motor = Reader(set_name="MotorCommands", topic_name="MotorCommandsTopic", topic_data_type=MotorCommands.MotorCommandsPubSubType,listener=ReaderListenerMotor,socketio=socketio)

    # Capture Ctrl+C signal to clean up
    signal.signal(signal.SIGINT, lambda sig, frame: reader.delete() or exit(0))

    # Start the Flask web server
    socketio.run(app, host='0.0.0.0', port=5000)
