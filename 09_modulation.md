# Module 9: Modulation Techniques and Other Features in Communication

## Modulation and Demodulation

**Modulation** is the process of varying the parameters (amplitude, phase, or frequency) of a carrier signal according to the instantaneous values of a modulating signal. It enables the transmission of data using electrical or optical signals and is fundamental to telecommunication systems.

- **Modulating Signal**: The baseband signal that contains the message to be transmitted. It must be modulated for transmission.
- **Carrier Signal**: A high-frequency signal with defined amplitude, frequency, and phase but no information. It serves as the vehicle for the modulating signal.
- **Modulated Signal**: The outcome of combining the modulating signal with the carrier signal. It carries the information over a medium.

**Demodulation** is the process of retrieving the original modulating signal from the modulated carrier wave. A **demodulator** is the circuit responsible for this extraction.

## Purpose of Using Modulation in Communication

Modulation plays a vital role in communication systems for several reasons:

- **Long-Distance Transmission**: Modulation enables low-frequency signals to be transmitted over long distances by combining them with high-frequency carrier signals.

- **Multiplexing and Interference Reduction**: Multiple signals can be transmitted simultaneously through a common channel using multiplexers. Modulating each signal to different carrier frequencies prevents interference and allows receivers to select the desired signal.

- **Antenna Size**: The size of an antenna is inversely proportional to the frequency of the transmitted signal. Without modulation, low-frequency signals would require impractically large antennas. Modulating to higher frequencies reduces the required antenna size.

- **Channel Allocation and Noise Immunity**: Modulation allows for the allocation of more communication channels and improves resistance to noise.


## Types of Modulation and Analog Modulation

### Types of Modulation

Modulation is broadly classified into two types:

- **Analog Modulation**
- **Digital Modulation**

> *Figure 1: Modulation Types*

### Analog Modulation

In analog modulation, an analog (sinusoidal) signal is used as the carrier to modulate the message or data signal. The sinusoidal wave has three modifiable parameters, which define the types of analog modulation:

- **Amplitude Modulation (AM)**: Varies the amplitude of the carrier signal.
- **Frequency Modulation (FM)**: Varies the frequency of the carrier signal.
- **Phase Modulation (PM)**: Varies the phase of the carrier signal.

> *Figure 2: Analog Modulation*


## Amplitude Modulation (AM), Frequency Modulation (FM), and Phase Modulation (PM)

### Amplitude Modulation (AM)

In AM, the **amplitude** of the carrier signal varies according to the instantaneous amplitude of the modulating (message) signal. The carrier is a continuous wave that initially contains no information.

The message signal, the unmodulated carrier, and the resulting modulated signal show that the amplitude of the carrier changes to match the message signal. The shape of the original message signal can be traced from the envelope of the modulated signal.

#### Modulation Index

The **modulation index** (or modulation depth) describes the extent of modulation:

\[
\mu = \frac{A_m}{A_c}
\]

- \( A_m \): Amplitude of the modulating signal  
- \( A_c \): Amplitude of the carrier signal

- If \( \mu < 1 \), the result is **under-modulation**.
- If \( \mu > 1 \), the result is **over-modulation**.

---

### Frequency Modulation (FM)

In FM, the **frequency** of the carrier signal varies in accordance with the instantaneous amplitude of the modulating signal.

- The **amplitude** and **phase** of the carrier remain constant.
- When the modulating signal's amplitude increases, the carrier's frequency increases.
- When the modulating signal's amplitude decreases, the carrier's frequency decreases.

---

### Phase Modulation (PM)

In PM, the **phase** of the carrier signal varies based on the instantaneous amplitude of the modulating signal.

- The **amplitude** and **frequency** of the carrier remain constant.
- Positive amplitudes of the modulating signal shift the carrier's phase in one direction.
- Negative amplitudes shift it in the opposite direction.

## Comparison Between AM, FM, and PM

| Feature              | Amplitude Modulation (AM)                     | Frequency Modulation (FM)                     | Phase Modulation (PM)                        |
|----------------------|-----------------------------------------------|-----------------------------------------------|----------------------------------------------|
| Varying Parameter    | Amplitude of carrier signal                   | Frequency of carrier signal                   | Phase of carrier signal                      |
| Signal Quality       | More affected by noise                        | Better noise immunity than AM                 | Similar noise performance to FM              |
| Bandwidth Requirement| Low                                           | Higher than AM                                | Similar to or slightly higher than FM        |
| Power Efficiency     | Less efficient (carrier consumes power)       | More efficient                                | More efficient                               |
| Complexity           | Simple to implement                           | More complex                                  | More complex                                 |
| Application Examples | AM radio broadcasting                         | FM radio, TV sound transmission               | Some wireless communication systems          |

## Digital Modulation

Digital modulation involves modulating an analog carrier signal using a discrete (digital) signal, essentially performing digital-to-analog conversion. The modulated signal is always digital, representing binary data (0s and 1s).

Advantages of digital modulation include:
- Higher information capacity
- Improved data security
- Faster system availability
- Better quality communication

Due to these benefits, digital modulation is preferred for transmitting large amounts of data.

Common types of digital modulation techniques include:
- ASK (Amplitude Shift Keying)
- FSK (Frequency Shift Keying)
- PSK (Phase Shift Keying)


## Amplitude Shift Keying (ASK)

Amplitude Shift Keying (ASK) is a form of amplitude modulation where binary data is represented by variations in the amplitude of a carrier signal. 

- A high-frequency carrier signal is modulated such that:
  - Low input (0) results in no carrier output (zero value)
  - High input (1) results in the carrier signal being transmitted

### ASK Modulator

The ASK modulator includes:
- Carrier signal generator (continuous high-frequency carrier)
- Binary sequence (message signal)
- Band-limited (pulse-shaping) filter

When the input is high, a switch allows the carrier wave to pass through; when low, the switch is open and no voltage appears, producing a low output. The band-limiting filter shapes the pulses accordingly.

### ASK Demodulator

There are two main types of ASK demodulation:

1. **Asynchronous ASK Demodulator**  
   Components: Half-wave rectifier, low pass filter, comparator  
   - The modulated ASK signal is half-wave rectified, then filtered to remove high frequencies, producing an envelope-detected output. The comparator converts this to a digital signal.

2. **Synchronous ASK Demodulator**  
   Components: Square law detector, low pass filter, comparator, voltage limiter  
   - The square law detector outputs a voltage proportional to the square of the input amplitude. After filtering, the comparator and voltage limiter generate a clean digital output.

## Frequency Shift Keying (FSK)

Frequency Shift Keying (FSK) is a digital modulation technique where the frequency of the carrier signal varies according to the digital input signal.

- For binary **High (1)** input, the carrier frequency is high (Mark frequency).
- For binary **Low (0)** input, the carrier frequency is low (Space frequency).

### FSK Modulator

- Consists of two oscillators generating high and low frequencies.
- A switch controlled by the binary input selects the appropriate frequency.
- An internal clock synchronizes the oscillators to avoid abrupt phase discontinuities.

### FSK Demodulator

Two main types of FSK detectors exist:

1. **Asynchronous FSK Detector** (Non-coherent)
   - Components: Two band-pass filters (tuned to Mark and Space frequencies), two envelope detectors, and a decision circuit.
   - The signal is filtered and envelope-detected separately, then the decision circuit selects the most likely output and reshapes it to a rectangular waveform.

2. **Synchronous FSK Detector** (Coherent)
   - Components: Two mixers with local oscillators, two band-pass filters, and a decision circuit.
   - Mixers and filters demodulate the signal; the decision circuit selects the most probable output.
   - Requires minimum frequency separation between the two signals.
   - More complex than asynchronous detectors.

- Bandwidth of both demodulators depends on the bit rate of the signal.

## Phase Shift Keying (PSK)

PSK is a digital modulation technique where the **phase** of the carrier signal is varied to represent digital data. It is widely used in wireless LANs, biometric systems, RFID, and Bluetooth.

### Types of PSK

- **Binary Phase Shift Keying (BPSK):**
  - Also called 2-phase PSK or Phase Reversal Keying.
  - Uses two phases: 0° and 180°.
  - The carrier signal phase is inverted (180° shift) for binary 1; no phase shift for binary 0.
  - BPSK is a Double Side Band Suppressed Carrier (DSBSC) scheme.

- **BPSK Modulator:**
  - Uses a balanced modulator multiplying carrier sine wave and binary input.
  - Output: carrier wave at either 0° or 180° phase depending on input bit.

- **BPSK Demodulator:**
  - Comprises a mixer with local oscillator, bandpass filter, and detector.
  - Recovers band-limited baseband signal and regenerates original binary bit stream.
  - Requires bit clock for decision circuit in detection.

---

- **Quadrature Phase Shift Keying (QPSK):**
  - Uses four phase shifts: 0°, 90°, 180°, 270°.
  - Sends 2 bits per symbol (called bigits), doubling data rate efficiency over BPSK.
  - Also a DSBSC scheme.

- **QPSK Modulator:**
  - Input bits are split into even and odd bits.
  - Two multipliers modulate these with the carrier (one phase-shifted by 90°).
  - Outputs combined to form QPSK signal.

- **QPSK Demodulator:**
  - Uses two product detectors, bandpass filters, integrators.
  - Demodulates two BPSK signals simultaneously.
  - Recovers pairs of bits, which are converted back to serial data.

## Noise

Noise is an unwanted signal that interferes with the original message signal, corrupting its parameters. It typically enters the communication system at the channel or receiver, causing the message to be altered.

Noise is random, unpredictable, and has no fixed pattern, frequency, or amplitude. While it cannot be completely eliminated, measures are taken to reduce its effects.

---

### Effects of Noise

- **Limits operating range:** Noise restricts the weakest signal an amplifier or receiver can process.
- **Affects receiver sensitivity:** Sensitivity is the minimum input signal required for quality output, and noise lowers this sensitivity.

---

### Types of Noise

Noise is classified based on its source:

#### External Noise
Originates outside the receiver, usually in the communication channel or medium. It cannot be fully eliminated; best efforts focus on minimizing its impact.

Common examples:
- Atmospheric noise (irregularities in atmosphere)
- Extra-terrestrial noise (solar, cosmic)
- Industrial noise

#### Internal Noise
Generated inside the receiver by its components during operation. This noise is measurable and can be reduced with good receiver design.

Common examples:
- Thermal agitation noise (Johnson or electrical noise)
- Shot noise (random electron/hole movement)
- Transit-time noise (during signal transitions)
- Miscellaneous noise (flicker, resistance effect, mixer noise)

---

### Signal-to-Noise Ratio (SNR)

The ratio of signal power to noise power. A higher SNR indicates better quality of the received signal.

---

### Figure of Merit (F)

Defined as the ratio of output SNR to input SNR, representing system performance quality.

## Synchronous and Asynchronous Communication

In **Serial Transmission**, data is sent bit by bit sequentially. There are two types:

- **Synchronous Transmission**
- **Asynchronous Transmission**

### Key Differences:

| Feature                       | Synchronous Transmission                         | Asynchronous Transmission                        |
|-------------------------------|-------------------------------------------------|-------------------------------------------------|
| **Clock synchronization**      | Sender and receiver clocks must be synchronized | No clock synchronization required               |
| **Data framing**               | Uses synchronization characters                  | Uses start and stop bits                          |
| **Parity bit**                 | Not necessarily required                          | Parity bit added for error checking              |
| **Message indication**         | Synchronization characters alert data transmission start/end | Start/stop bits signal data transmission start/end |

In synchronous transmission, data is sent in blocks or frames synchronized by clock signals, whereas asynchronous transmission sends data one byte at a time, framed by start and stop bits.

---

### Figure 25 – Synchronous vs Asynchronous Communication

*(Typically includes a side-by-side comparison diagram illustrating clock alignment, framing, and data flow differences.)*



