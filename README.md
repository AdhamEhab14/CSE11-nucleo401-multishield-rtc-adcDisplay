# NUCLEO-F401RE Multifunction Shield – RTC & Voltage Display

## 📌 Project Overview

This project is part of the **CSE211s – Introduction to Embedded Systems (Spring 2025)** course at Ain Shams University.  
It showcases a real-time clock (RTC) and analog voltage display using the **NUCLEO-F401RE** board and the **Arduino Multifunction Shield**.

---

## ⚙️ Features

- ⏱ **Real-Time Clock (RTC)**
  - Displays time (MM:SS) on a 4-digit 7-segment display.
  - Timer starts from 00:00 on power-up.
  - Pressing **Switch S1** resets the timer to zero.

- 🔋 **Analog Voltage Display**
  - Reads voltage from the onboard potentiometer using the NUCLEO's ADC.
  - Pressing **Switch S3** displays the current voltage (in volts) on the 7-segment display.
  - Releasing S3 returns to displaying time.
  - The RTC continues running in the background.

---

## 🧰 Hardware Used

- [NUCLEO-F401RE Development Board](https://www.st.com/en/evaluation-tools/nucleo-f401re.html)
- Arduino Multifunction Shield with:
  - 4-digit 7-segment display
  - Onboard potentiometer
  - Tactile push buttons (S1, S2, S3)

---

## 🚀 How It Works

- **Startup Code:** Initializes the system clock, GPIOs, ADC, and timers.
- **Main Loop:** 
  - Updates the 7-segment display with current time or voltage.
  - Polls button states to determine display mode.
- **Interrupt Service Routines (ISRs):**
  - Timer ISR updates the time counters every second.
  - External interrupts (if used) handle button presses cleanly.

---

## 📽 Demo Video

Watch the full system in action here:  
📺 [YouTube Demo – NUCLEO RTC & Voltage Display](https://youtu.be/23day6YDwYg)

---

## 🧠 Learning Objectives

- Configure and use ADC in embedded systems
- Interface and multiplex a 4-digit 7-segment display
- Handle multiple button inputs
- Manage real-time tasks with timers and ISRs

---

## 👨‍💻 Authors

**Team Members:**  
- Adham Ehab Saleh (2100679)  
- Omar Mohamed Fathy (2100503)  
- Mohamed Montasser Abdelwahab (2100543)

**Course Instructor:**  
- Dr. Mohamed H. El-Shafey  
- Faculty of Engineering, Ain Shams University

