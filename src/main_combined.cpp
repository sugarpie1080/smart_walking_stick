
 #include <ToFDataPublisher.hpp>
 #include <ObstacleDetection.hpp>
 #include <MockMotor.hpp>
 #include <iostream>
 #include <thread>
 #include <chrono>
 
 void run_tof_publisher(smart_stick::ToFDataPublisher &mypub, uint32_t samples)
 {
     std::cout << "Starting publisher." << std::endl;
 
     ToFData msg;
     msg.distance(10);
     msg.index(0);
     uint32_t samples_sent = 0;
 
     while (samples_sent < samples)
     {
         if (mypub.publish(msg))
         {
             samples_sent++;
             msg.index(samples_sent);
             std::cout << "Message: " << msg.distance() << " with index: " << msg.index()
                       << " SENT" << std::endl;
         }
         else
         {
             std::cout << "No messages sent as there is no listener." << std::endl;
         }
         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
     }
 }
 
 int main()
 {
     std::cout << "Starting combined publisher and subscriber." << std::endl;
 
     // Create publisher and subscriber objects
     smart_stick::ToFDataPublisher mypub;
     smart_stick::ObstacleDetectionSub mysub;
     smart_stick::MockMotor motorsub;
 
     // Initialize the subscriber
     mysub.init();
     mysub.set_listener(mysub.reader_);

     motorsub.init();
     motorsub.set_listener(motorsub.reader_);
 
     // Start publisher in a separate thread
     uint32_t samples = 10;
     std::thread pub_thread(run_tof_publisher, std::ref(mypub), samples);
 
     // Wait for user to stop
     std::cout << "Press Enter to stop." << std::endl;
     getchar();
 
     // Ensure publisher thread finishes
     pub_thread.join();
 
     return 0;
 }
 