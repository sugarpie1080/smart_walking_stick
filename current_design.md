# Current Design
![threading](image.png)

Our current design utilises 3 threads: ToF Thread, Motor Thread, and DDS Thread.

## ToF Thread
Handles edge-triggered GPIO events to initiate distance measurements.

- block until edge on GPIO
- Check if a valid event occurred
    - If no, return to blocking
    - If yes, proceed
- Get distance reading from the TofSensor
- Trigger ToF callbacks (Motor thread, sending message to webapp)

## Motor Thread
Processes motor control data and outputs corresponding PWM values.

- block until data received
- Compute PWM value based on input command
- Send PWM signal to motor controller
- Trigger motor callbacks (Send message to Webapp)

## DDS Thread
Interfaces with FastDDS to send messages to the WebApp. 

- block until DDS message received
- Check message type:
    - If ToF data: forward ToFData FastDDS message
    - If motor command: forward MotorCommands FastDDS message

---

## Notes
- Each thread runs independently and concurrently.
- Callback mechanisms are used for decoupled data handling and WebApp updates.
- The FastDDS layer enables communication between this system and remote publishers/subscribers if required in a future installment.
