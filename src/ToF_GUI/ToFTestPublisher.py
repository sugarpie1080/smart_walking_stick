# Copyright 2022 Proyectos y Sistemas de Mantenimiento SL (eProsima).
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
"""
ToF Publisher
"""
from threading import Condition
import time

import fastdds
import ToFData

DESCRIPTION = """ToF Publisher example for Fast DDS python bindings"""
USAGE = ('python3 ToFPublisher.py')

class WriterListener (fastdds.DataWriterListener) :
    def __init__(self, writer) :
        self._writer = writer
        super().__init__()


    def on_publication_matched(self, datawriter, info) :
        if (0 < info.current_count_change) :
            print ("Publisher matched subscriber {}".format(info.last_subscription_handle))
            self._writer._cvDiscovery.acquire()
            self._writer._matched_reader += 1
            self._writer._cvDiscovery.notify()
            self._writer._cvDiscovery.release()
        else :
            print ("Publisher unmatched subscriber {}".format(info.last_subscription_handle))
            self._writer._cvDiscovery.acquire()
            self._writer._matched_reader -= 1
            self._writer._cvDiscovery.notify()
            self._writer._cvDiscovery.release()


class Writer:


    def __init__(self):
        self._matched_reader = 0
        self._cvDiscovery = Condition()
        self.index = 0

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

        self.publisher_qos = fastdds.PublisherQos()
        self.participant.get_default_publisher_qos(self.publisher_qos)
        self.publisher = self.participant.create_publisher(self.publisher_qos)

        self.listener = WriterListener(self)
        self.writer_qos = fastdds.DataWriterQos()
        self.publisher.get_default_datawriter_qos(self.writer_qos)
        self.writer = self.publisher.create_datawriter(self.topic, self.writer_qos, self.listener)


    def write(self):
        data = ToFData.ToFData()
        data.distance(float(10))
        data.sec(self.index)
        data.nanosec(42)
        self.writer.write(data)
        print("Sending distance = {distance} : {sec}".format(distance=data.distance(), sec=data.sec()))
        self.index = self.index + 1


    def wait_discovery(self) :
        self._cvDiscovery.acquire()
        print ("Writer is waiting discovery...")
        self._cvDiscovery.wait_for(lambda : self._matched_reader != 0)
        self._cvDiscovery.release()
        print("Writer discovery finished...")


    def run(self):
        self.wait_discovery()
        for x in range(1000) :
            time.sleep(1)
            self.write()
        self.delete()


    def delete(self):
        factory = fastdds.DomainParticipantFactory.get_instance()
        self.participant.delete_contained_entities()
        factory.delete_participant(self.participant)


if __name__ == '__main__':
    print('Starting publisher.')
    writer = Writer()
    writer.run()
    exit()
