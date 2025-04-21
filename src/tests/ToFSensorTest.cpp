#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ToFSensor.hpp"
#include "ToFSensor.cpp"
#include <gpiod.h>

// Mock gpiod chip and line
class MockGpiodChip {
public:
    MOCK_METHOD(gpiod_line*, get_line, (int pin), ());
    MOCK_METHOD(int, close, (), ());
};

class MockGpiodLine {
public:
    MOCK_METHOD(int, request_both_edges_events, (const char* consumer), ());
    MOCK_METHOD(int, event_wait, (timespec* timeout), ());
    MOCK_METHOD(int, event_read, (gpiod_line_event* event), ());
    MOCK_METHOD(void, release, (), ());
};

// Mock VL53L0X sensor
class MockVL53L0X {
public:
    MOCK_METHOD(void, initialize, (), ());
    MOCK_METHOD(void, startContinuous, (), ());
    MOCK_METHOD(void, setMeasurementTimingBudget, (int timing), ());
    MOCK_METHOD(uint16_t, readRangeContinuousMillimeters, (), ());
};

// Mock CallbackInterface
class MockCallbackInterface : public CallbackInterface {
public:
    MOCK_METHOD(void, has_distance, (float distance), (override));
};

// Mock the ToFSensor's dependencies and behavior
class MockToFSensor : public ToFSensor {
public:
    MockToFSensor(const char* chipname, int pin)
        : ToFSensor(chipname, pin) {}

    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, initialise, (), (override));
    MOCK_METHOD(void, worker, (), (override));
};

// Test cases for ToFSensor
TEST(ToFSensorTest, StartGPIO) {
    MockToFSensor mockSensor("gpio_chip_name", 5);
    MockGpiodChip mockChip;
    MockGpiodLine mockLine;

    // Expectations
    EXPECT_CALL(mockChip, get_line(5)).WillOnce(testing::Return(&mockLine));
    EXPECT_CALL(mockLine, request_both_edges_events("temp")).WillOnce(testing::Return(0));

    // Test if start correctly initializes GPIO chip and line
    mockSensor.start();

    // Verify that GPIO line and events were requested correctly
    testing::Mock::VerifyAndClearExpectations(&mockChip);
    testing::Mock::VerifyAndClearExpectations(&mockLine);
}

TEST(ToFSensorTest, RegisterCallback) {
    MockToFSensor mockSensor("gpio_chip_name", 5);
    MockCallbackInterface mockCallback;

    // Register the callback
    mockSensor.register_callback(&mockCallback);

    // We can't directly verify callback registration, but we can mock the callback calls in other tests
}

TEST(ToFSensorTest, InitialiseSensor) {
    MockToFSensor mockSensor("gpio_chip_name", 5);
    MockVL53L0X mockVL53L0X;

    // Expectations
    EXPECT_CALL(mockVL53L0X, initialize()).Times(1);
    EXPECT_CALL(mockVL53L0X, startContinuous()).Times(1);
    EXPECT_CALL(mockVL53L0X, setMeasurementTimingBudget(20000)).Times(1);

    // Test if initialise correctly initializes the sensor
    mockSensor.initialise();

    // Verify expectations
    testing::Mock::VerifyAndClearExpectations(&mockVL53L0X);
}

TEST(ToFSensorTest, WorkerReadsDistance) {
    MockToFSensor mockSensor("gpio_chip_name", 5);
    MockCallbackInterface mockCallback;
    MockVL53L0X mockVL53L0X;
    MockGpiodLine mockLine;

    // Set up expectations
    uint16_t mockDistance = 500;
    EXPECT_CALL(mockLine, event_wait(testing::_)).WillOnce(testing::Return(1)); // Simulate event
    EXPECT_CALL(mockVL53L0X, readRangeContinuousMillimeters()).WillOnce(testing::Return(mockDistance));
    EXPECT_CALL(mockCallback, has_distance(testing::_)).WillOnce(testing::Invoke([mockDistance](float dist) {
        EXPECT_FLOAT_EQ(dist, static_cast<float>(mockDistance));
    }));

    // Simulate worker running
    mockSensor.register_callback(&mockCallback);
    mockSensor.worker();  // We need to simulate a worker thread

    // Verify that callback has been called with the correct distance
    testing::Mock::VerifyAndClearExpectations(&mockCallback);
}

TEST(ToFSensorTest, DestructorCleanup) {
    MockToFSensor mockSensor("gpio_chip_name", 5);
    MockGpiodChip mockChip;
    MockGpiodLine mockLine;

    // Set up expectations for cleanup
    EXPECT_CALL(mockChip, close()).Times(1);
    EXPECT_CALL(mockLine, release()).Times(1);

    // Simulate destruction
    mockSensor.~ToFSensor();

    // Verify cleanup has been called
    testing::Mock::VerifyAndClearExpectations(&mockChip);
    testing::Mock::VerifyAndClearExpectations(&mockLine);
}