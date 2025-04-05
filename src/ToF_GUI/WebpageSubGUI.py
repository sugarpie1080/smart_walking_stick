import signal
import flask
from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import fastdds
import sys
sys.path.append("/home/pi/Documents/smart_walking_stick/build/tmp/lib/python3.11/site-packages")
import ToFData
import MotorCommands
from Reader import Reader
app = Flask(__name__)
socketio = SocketIO(app)

# Route to serve the webpage
@app.route('/')
def index():
    return render_template('index.html')

# Custom ReaderListener to receive DDS data and emit via WebSocket
class ReaderListenerToF(fastdds.DataReaderListener):
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
            socketio.emit('update_data', {'sec': data.sec(), 'battery': 0.0, 'distance': data.distance()})
        else:
            print("No data received or data invalid.")

class ReaderListenerMotor(fastdds.DataReaderListener):
    def on_subscription_matched(self, datareader, info):
        if info.current_count_change > 0:
            print(f"Subscriber matched publisher {info.last_publication_handle}")
        else:
            print(f"Subscriber unmatched publisher {info.last_publication_handle}")
    def on_data_available(self, reader):
        info = fastdds.SampleInfo()
        data = MotorCommands.MotorCommands()
        reader.take_next_sample(data, info)
        duty_cycle = data.duty_cycle()

        print("values:")
        print(duty_cycle)

        if reader.take_next_sample(data, info):
            # Emit data to connected WebSocket clients
            socketio.emit('update_motor_data', {'duty_cycle': data.duty_cycle()})
        else:
            print("No data received or data invalid.")






if __name__ == '__main__':
    # Create the DDS reader
    reader = Reader(set_name="ToFData", topic_name="ToFDataTopic", topic_data_type=ToFData.ToFDataPubSubType,listener=ReaderListenerToF)
    reader_motor = Reader(set_name="MotorCommands", topic_name="MotorCommandsTopic", topic_data_type=MotorCommands.MotorCommandsPubSubType,listener=ReaderListenerMotor)

    # Capture Ctrl+C signal to clean up
    signal.signal(signal.SIGINT, lambda sig, frame: reader.delete() or exit(0))

    # Start the Flask web server
    socketio.run(app, host='0.0.0.0', port=5000)
