#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MotorMove.hpp"
#include "MotorMove.cpp"

class MockToFSensor : public ToFSensor {
public:
    MOCK_METHOD(void, register_callback, (MotorMove*), (override));
};

class MockPWM {
public:
    MOCK_METHOD(void, start, (int channel, int frequency), ());
    MOCK_METHOD(void, stop, (), ());
    MOCK_METHOD(void, setDutyCycle, (int dutyCycle), ());
};

class MockCallbackInterface : public CallbackInterface {
public:
    MOCK_METHOD(void, has_duty, (int dutyCycle), (override));
};

TEST(MotorMoveTest, ConvertDistanceToDutyCycle) {
    MockToFSensor mockTof;
    MockPWM mockPwm;
    MotorMove motorMove(&mockTof);

    EXPECT_EQ(motorMove.convert_distance_to_duty_cycle(0), 0);
    EXPECT_EQ(motorMove.convert_distance_to_duty_cycle(10), PWM_MAX);
    EXPECT_EQ(motorMove.convert_distance_to_duty_cycle(100), 0);
    EXPECT_GT(motorMove.convert_distance_to_duty_cycle(50), 0);
    EXPECT_LT(motorMove.convert_distance_to_duty_cycle(50), PWM_MAX);
}

TEST(MotorMoveTest, HasDistanceUpdatesMotor) {
    MockToFSensor mockTof;
    MockPWM mockPwm;
    MotorMove motorMove(&mockTof);

    EXPECT_CALL(mockPwm, setDutyCycle(testing::_)).Times(1);
    motorMove.has_distance(50);
    EXPECT_EQ(motorMove.convert_distance_to_duty_cycle(50), 60);
}

TEST(MotorMoveTest, RegisterCallback) {
    MockToFSensor mockTof;
    MockPWM mockPwm;
    MotorMove motorMove(&mockTof);

    MockCallbackInterface mockCallback;

    motorMove.register_callback(&mockCallback);

    motorMove.has_distance(50);

    EXPECT_CALL(mockCallback, has_duty(60)).Times(1);
}

TEST(MotorMoveTest, DestructorStopsMotor) {
    MockToFSensor mockTof;
    MockPWM mockPwm;

    {
        MotorMove motorMove(&mockTof);
        EXPECT_CALL(mockPwm, stop()).Times(1);
    }
}
