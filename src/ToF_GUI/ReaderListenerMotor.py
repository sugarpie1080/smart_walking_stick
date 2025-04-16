import signal
import flask
from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import fastdds
import MotorCommands

class ReaderListenerMotor(fastdds.DataReaderListener):
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
        data = MotorCommands.MotorCommands()
        reader.take_next_sample(data, info)
        duty_cycle = data.duty_cycle()
        sec = data.sec()


        print(f"Received data: Seconds={data.sec()}, Duty Cycle ={data.duty_cycle()}")

        if reader.take_next_sample(data, info):
            # Emit data to connected WebSocket clients
            self.socketio.emit('update_motor_data', {'duty_cycle': data.duty_cycle(), 'sec': data.sec()})
        else:
            print("No data received or data invalid.")