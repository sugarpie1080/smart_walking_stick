
 #include "ToFDataPublisher.hpp"
 #include <iostream>
 #include <thread>
 #include <chrono>
 
 namespace smart_stick
 {
     ToFDataPublisher::ToFDataPublisher(const char* chipname, int line)
         : BasePublisher("ToFDataTopic"), sensor_(chipname, line)
     {
     }
 
     void ToFDataPublisher::initialise()
     {
         sensor_.initialise();
     }
 
     void ToFDataPublisher::publishData()
     {
         while (true)
         {
             int value = gpiod_line_get_value(sensor_.getLine());
             if (value < 0)
             {
                 std::cerr << "Error reading GPIO value!" << std::endl;
                 break;
             }
             if (value == 1)
             {
                 float distance = sensor_.getDistance();
                 ToFData message;
                auto now = std::chrono::system_clock::now();
                auto duration = now.time_since_epoch();
                int32_t sec = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
                int32_t nanosec = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count() % 1000000000;
                message.sec(sec);
                message.nanosec(nanosec);
                message.distance(distance);
                 
                 if (publish(message))
                 {
                     std::cout << "Published distance: " << distance << " mm" << std::endl;
                 }
                 else
                 {
                     std::cerr << "Failed to publish distance data." << std::endl;
                 }
             }
         }
     }
 }
 