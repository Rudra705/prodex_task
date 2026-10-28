# Dual-Axis Solar Tracking System

**ProDex IIT Kharagpur — Internet of Things (IoT), Task 2**

**Tinkercad Simulation:** [Open](https://www.tinkercad.com/things/ieDN6osc7aq/editel?returnTo=%2Fcircuits&sharecode=GFEJ9CTA90skxpGRfUXhmScgbclA3UQvfuUmodMg0uY)

## 1. Project Overview

This project implements an Arduino-based dual-axis solar tracking system using four Light Dependent Resistors (LDRs) and two servo motors. The system compares light intensity from different directions and adjusts its horizontal and vertical target angles towards the brighter direction.

The project demonstrates light sensing, feedback-based position control, and servo motor interfacing using Tinkercad Circuits.

## 2. Objectives

- Detect light intensity using four LDRs.
- Control horizontal movement using one servo motor.
- Control vertical movement using a second servo motor.
- Reduce unnecessary movement using a light-difference threshold.
- Hold the current position when the overall light level is below a minimum threshold.
- Display sensor readings, servo angles, and operating status through the Serial Monitor.

## 3. Components Used

| Component | Quantity | Purpose |
|---|---:|---|
| Arduino Uno R3 | 1 | Main controller |
| Photoresistors (LDRs) | 4 | Detect light intensity from four directions |
| 10 kΩ resistors | 4 | Form voltage-divider circuits with the LDRs |
| Micro servo motors | 2 | Control horizontal and vertical movement |
| Breadboard | 1 | Circuit assembly |
| Jumper wires | As required | Electrical connections |

## 4. Circuit Connections

### LDR connections

Each LDR is connected with a 10 kΩ resistor to form a voltage divider. The junction between the LDR and resistor connects to the corresponding Arduino analog input.

| Sensor | Arduino Pin |
|---|---|
| Top-left (TL) | A0 |
| Top-right (TR) | A1 |
| Bottom-left (BL) | A2 |
| Bottom-right (BR) | A3 |

### Servo connections

| Servo | Signal Pin | Function |
|---|---|---|
| Pan servo | D10 | Horizontal rotation |
| Tilt servo | D9 | Vertical tilt |

The sensor circuits and servos use the circuit's power and ground connections. The two servos are controlled independently to simulate horizontal and vertical tracking. In a physical implementation, they would be mounted on perpendicular rotation axes.

## 5. Working Principle

### Step 1: Light detection

The Arduino reads the four LDRs using `analogRead()`. Each analog reading represents the voltage measured at the corresponding sensor input.

### Step 2: Sensor averaging

Five readings are taken from each LDR and averaged to reduce the effect of small fluctuations.

The system then calculates four directional averages:

- Left average = (TL + BL) / 2
- Right average = (TR + BR) / 2
- Top average = (TL + TR) / 2
- Bottom average = (BL + BR) / 2

### Step 3: Horizontal tracking

The left and right averages are compared. If their difference exceeds the threshold of 35, the pan servo's target angle changes by one degree in the direction selected by the control logic.

### Step 4: Vertical tracking

The top and bottom averages are compared independently. If their difference exceeds the same threshold, the tilt servo's target angle changes by one degree.

Both axes can be adjusted during the same control cycle.

### Step 5: Darkness protection and position limits

The average of all four LDR readings is compared with a minimum-light threshold of 80. If the reading is below this value, the system holds the existing target angles instead of attempting to track.

The target angles are limited to the range of 10° to 170° to avoid commanding the full servo travel range.

### Step 6: Serial monitoring

The Serial Monitor displays the four sensor readings, directional averages, servo target angles, and a status message. This helps observe the controller's response during simulation.

## 6. Additional Functionality

The following features extend the basic tracking logic:

- **Reading averaging:** Five samples per LDR are averaged before calculating directional differences.
- **Dead zone:** A threshold of 35 prevents corrections for small differences in light intensity.
- **Darkness protection:** Tracking corrections are skipped when the overall light reading is below the configured minimum.
- **Servo angle limits:** Target angles are restricted to 10°–170°.
- **Conditional servo commands:** A new target is sent to a servo only when its target angle changes.
- **Serial diagnostics:** Sensor readings, calculated averages, target angles, and status are displayed for testing.

## 7. Testing and Observations

The system can be tested by changing the illumination of individual photoresistors in Tinkercad.

| Test | Expected observation |
|---|---|
| Similar light on all four LDRs | Servo targets remain stable when directional differences are within the threshold |
| Left side brighter than right | Horizontal correction is triggered |
| Right side brighter than left | Horizontal correction is triggered in the opposite direction |
| Top side brighter than bottom | Vertical correction is triggered |
| Bottom side brighter than top | Vertical correction is triggered in the opposite direction |
| Overall light below the configured minimum | Target angles remain unchanged |
| Servo target reaches its configured limit | Target remains within 10°–170° |

The actual direction of servo movement must be verified against the sensor arrangement and mechanical mounting.

## 8. Simulation Evidence

### Circuit Design

![Solar tracker circuit](screenshots/circuit.png)

### Serial Monitor Output

![Solar tracker output](screenshots/tracking_output.png)

The screenshots should show the completed circuit and genuine Serial Monitor output from the simulation.

## 9. Limitations and Real-World Adaptation

This project demonstrates the basic control logic in a simulated environment. A practical solar tracker would require additional considerations:

- Calibrating individual LDR readings to compensate for differences between sensors.
- Selecting suitable light thresholds under different lighting conditions.
- Verifying servo directions and mechanical travel limits.
- Using an appropriate power supply for the servo motors.
- Providing a weather-resistant mounting structure for outdoor operation.
- Considering wind loads, panel weight, and long-term mechanical reliability.

The present implementation uses fixed thresholds and one-degree corrections. Further improvements could include adaptive thresholds, proportional movement, more advanced filtering, and a more accurate tracking mechanism.

## 10. Further Applications

The underlying sensing and position-control approach can be adapted for:

- Solar panel orientation systems.
- Light-following robotic platforms.
- Automatic lighting and daylight orientation systems.
- Light-sensitive positioning mechanisms.
- Educational demonstrations of embedded systems and feedback control.

## 11. Repository Contents

- `solar_tracker.ino` — Arduino source code.
- `README.md` — Project documentation.
- `screenshots/circuit.png` — Circuit screenshot.
- `screenshots/tracking_output.png` — Serial Monitor evidence.

## 12. Conclusion

The project demonstrates a dual-axis light-tracking system using four LDRs, an Arduino Uno, and two servo motors. By comparing directional light averages and applying threshold-based corrections, the system can adjust its horizontal and vertical target angles while reducing unnecessary movement under small light differences.

The simulation provides a foundation for understanding sensor interfacing, servo control, and feedback-based positioning in IoT applications.
