#include "mbed.h"

// Shift register pins (common anode)
DigitalOut latchPin(D4);
DigitalOut clockPin(D7);
DigitalOut dataPin(D8);

// Buttons
DigitalIn s1(A1); // Reset
DigitalIn s3(A3); // Voltage display

// ADC input
AnalogIn pot(A0);

// 7-segment digit patterns (common anode, inverted)
const uint8_t digitPattern[10] = {
    static_cast<uint8_t>(~0x3F), // 0
    static_cast<uint8_t>(~0x06), // 1
    static_cast<uint8_t>(~0x5B), // 2
    static_cast<uint8_t>(~0x4F), // 3
    static_cast<uint8_t>(~0x66), // 4
    static_cast<uint8_t>(~0x6D), // 5
    static_cast<uint8_t>(~0x7D), // 6
    static_cast<uint8_t>(~0x07), // 7
    static_cast<uint8_t>(~0x7F), // 8
    static_cast<uint8_t>(~0x6F)  // 9
};

// Digit enable pins (via shift register)
const uint8_t digitPos[4] = {0x01, 0x02, 0x04, 0x08};

// Time tracking
volatile int seconds = 0, minutes = 0;
Ticker timerTicker;

// Min/max voltage
float minVoltage = 3.3f;
float maxVoltage = 0.0f;

// ========== Functions ==========

// Timer ISR to update seconds/minutes
void updateTime() {
    seconds++;
    if (seconds >= 60) {
        seconds = 0;
        minutes = (minutes + 1) % 100;
    }
}

// Shift out one byte MSB-first
void shiftOutMSBFirst(uint8_t value) {
    for (int i = 7; i >= 0; i--) {
        dataPin = (value & (1 << i)) ? 1 : 0;
        clockPin = 1;
        clockPin = 0;
    }
}

// Send data to shift register
void writeToShiftRegister(uint8_t segments, uint8_t digit) {
    latchPin = 0;
    shiftOutMSBFirst(segments);
    shiftOutMSBFirst(digit);
    latchPin = 1;
}

// Display 4-digit number with optional decimal point
void displayNumber(int number, bool showDecimal = false, int decimalPos = -1) {
    int digits[4] = {
        (number / 1000) % 10,
        (number / 100) % 10,
        (number / 10) % 10,
        number % 10
    };

    for (int i = 0; i < 4; i++) {
        uint8_t pattern = digitPattern[digits[i]];
        if (showDecimal && i == decimalPos) {
            pattern &= ~0x80; // Enable decimal point (DP)
        }
        writeToShiftRegister(pattern, digitPos[i]);
        ThisThread::sleep_for(2ms);
    }
}

// Read potentiometer voltage in volts
float readVoltage() {
    return pot.read() * 3.3f;
}

// ========== Main ==========

int main() {
    // Configure inputs
    s1.mode(PullUp);
    s3.mode(PullUp);

    // Start RTC ticker
    timerTicker.attach(&updateTime, 1.0f); // every 1 second

    while (true) {
        // Reset clock on S1 press
        if (!s1) {
            seconds = 0;
            minutes = 0;
            ThisThread::sleep_for(200ms); // Debounce
        }

        // Read voltage
        float voltage = readVoltage();
        minVoltage = fmin(minVoltage, voltage);
        maxVoltage = fmax(maxVoltage, voltage);

        // Display mode: Voltage or Time
        if (!s3) {
            // Voltage display mode: e.g. 2.45 V → 245
            int voltageDisplay = static_cast<int>(voltage * 100);
            displayNumber(voltageDisplay, true, 1); // X.XX
        } else {
            // Time display mode: MM.SS format
            int displayTime = minutes * 100 + seconds;
            displayNumber(displayTime, true, 1); // M.MS
        }
    }
}
