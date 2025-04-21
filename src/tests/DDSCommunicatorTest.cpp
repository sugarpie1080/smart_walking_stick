#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "DDSCommunicator.hpp"
#include "DDSCommunicator.cpp"

// Mock ToFSensor
class MockToFSensor : public ToFSensor {
public:
    MOCK_METHOD(void, register_callback, (DDSCommunicator*), (override));
};

// Mock MotorMove
class MockMotorMove : public MotorMove {
public:
    MOCK_METHOD(void, register_callback, (DDSCommunicator*), (override));
};

// Mock ToFData and MotorCommands
class MockToFData {
public:
    MOCK_METHOD(void, sec, (int32_t), ());
    MOCK_METHOD(void, nanosec, (int32_t), ());
    MOCK_METHOD(void, distance, (float), ());
};

class MockMotorCommands {
public:
    MOCK_METHOD(void, sec, (int32_t), ());
    MOCK_METHOD(void, nanosec, (int32_t), ());
    MOCK_METHOD(void, duty_cycle, (int), ());
};

// Mock publisher class
class MockPublisher {
public:
    MOCK_METHOD(void, publish, (const MockToFData&), ());
    MOCK_METHOD(void, publish, (const MockMotorCommands&), ());
};

TEST(DDSCommunicatorTest, HasDistanceUpdates) {
    MockToFSensor mockTof;
    MockMotorMove mockMotorMove;
    MockPublisher mockPublisher;
    
    DDSCommunicator ddsComm(&mockTof, &mockMotorMove);

    // Mock the callbacks
    EXPECT_CALL(mockTof, register_callback(&ddsComm)).Times(1);
    EXPECT_CALL(mockMotorMove, register_callback(&ddsComm)).Times(1);

    // Test if has_distance properly sets the distance
    ddsComm.has_distance(50.0f);
    
    // Verify that distance_ready flag is true and last_distance is set to 50.0
    // Optionally, verify that the worker thread processes the data after the notify_all() call
}

TEST(DDSCommunicatorTest, HasDutyUpdates) {
    MockToFSensor mockTof;
    MockMotorMove mockMotorMove;
    MockPublisher mockPublisher;
    
    DDSCommunicator ddsComm(&mockTof, &mockMotorMove);

    // Mock the callbacks
    EXPECT_CALL(mockTof, register_callback(&ddsComm)).Times(1);
    EXPECT_CALL(mockMotorMove, register_callback(&ddsComm)).Times(1);

    // Test if has_duty properly sets the duty cycle
    ddsComm.has_duty(75);

    // Verify that duty_cycle_ready flag is true and last_duty_cycle is set to 75
}

TEST(DDSCommunicatorTest, PublishDistance) {
    MockToFSensor mockTof;
    MockMotorMove mockMotorMove;
    MockPublisher mockPublisher;
    
    DDSCommunicator ddsComm(&mockTof, &mockMotorMove);
    
    // Mock the publishing function
    EXPECT_CALL(mockPublisher, publish(testing::_)).Times(1);

    // Set a distance and verify publish_distance is called with correct data
    ddsComm.has_distance(50.0f);

    // Create expected message
    MockToFData expectedMessage;
    EXPECT_CALL(expectedMessage, sec(testing::_)).Times(1);
    EXPECT_CALL(expectedMessage, nanosec(testing::_)).Times(1);
    EXPECT_CALL(expectedMessage, distance(50.0f)).Times(1);

    ddsComm.publish_distance();
}

TEST(DDSCommunicatorTest, PublishDutyCycle) {
    MockToFSensor mockTof;
    MockMotorMove mockMotorMove;
    MockPublisher mockPublisher;
    
    DDSCommunicator ddsComm(&mockTof, &mockMotorMove);

    // Mock the publishing function
    EXPECT_CALL(mockPublisher, publish(testing::_)).Times(1);

    // Set a duty cycle and verify publish_duty_cycle is called with correct data
    ddsComm.has_duty(60);

    // Create expected message
    MockMotorCommands expectedMessage;
    EXPECT_CALL(expectedMessage, sec(testing::_)).Times(1);
    EXPECT_CALL(expectedMessage, nanosec(testing::_)).Times(1);
    EXPECT_CALL(expectedMessage, duty_cycle(60)).Times(1);

    ddsComm.publish_duty_cycle();
}

TEST(DDSCommunicatorTest, WorkerHandlesPublishing) {
    MockToFSensor mockTof;
    MockMotorMove mockMotorMove;
    MockPublisher mockPublisher;
    
    DDSCommunicator ddsComm(&mockTof, &mockMotorMove);

    // Mock the callbacks
    EXPECT_CALL(mockTof, register_callback(&ddsComm)).Times(1);
    EXPECT_CALL(mockMotorMove, register_callback(&ddsComm)).Times(1);

    // Mock the publishing methods
    EXPECT_CALL(mockPublisher, publish(testing::_)).Times(1).WillOnce(testing::Invoke([&](const MockToFData& message){
        // Verify the published message
        EXPECT_FLOAT_EQ(message.distance(), 50.0f);
    }));

    // Set a distance and duty cycle, trigger the worker
    ddsComm.has_distance(50.0f);
    ddsComm.has_duty(60);
    
    // Simulate the worker processing the message
    ddsComm.worker();
}
