# Module 6: Ethernet and Devices used in Communication Networks

## Ethernet Overview

### What is Ethernet?

Ethernet is a technology for connecting wired Local Area Networks (LANs), enabling devices to communicate using a standardized protocol. It governs how data is transmitted and formatted in a LAN. Ethernet cables carry data physically between devices.

### Ethernet and the OSI Model

Ethernet spans:
- **Layer 1 (Physical Layer):** Handles signals, media components, and transmission.
- **Layer 2 (Data Link Layer):** Manages framing, addressing, and media access.

The Ethernet standard is **IEEE 802.3**, which ensures compatibility with the OSI model.

### Ethernet Layer 1: Physical Layer

Defines:
- Electrical signals and bit streams
- Physical media and components
- Network topologies

### Ethernet Layer 2: Data Link Layer

#### Sublayers
- **Logical Link Control (LLC):** Interfaces with upper layers, adds control info, and is implemented in software (e.g., NIC drivers).
- **Media Access Control (MAC):** Handles frame creation, transmission, and media access; implemented in hardware.

#### MAC Functions
- **Data Encapsulation:** Adds headers/trailers to form frames.
  - Frame delimiting
  - Addressing (MAC addresses)
  - Error detection (CRC)
- **Media Access:** Controls when/how devices access shared media (e.g., CSMA/CD in legacy networks).

### Ethernet Frame Structure

Fields:
- **Preamble & Start Frame Delimiter**
- **Destination MAC Address**
- **Source MAC Address**
- **Length/Type**
- **Data and Pad**
- **Frame Check Sequence (FCS)**

### MAC Addresses

- A 48-bit identifier (12 hexadecimal digits)
- Added to frames for device-level addressing
- Structure:
  - **First 3 bytes (OUI):** Vendor-specific
  - **Last 3 bytes:** Unique identifier

#### Address Types
- **Burned-in Address (BIA) / Universally Administered Address (UAA):** Predefined in NIC ROM
- **Locally Administered Address (LAA):** Manually configured; useful for network security or device replacement

### Binary ↔ HEX ↔ Decimal Conversion Example

- Binary: `01010101`
- Split into nibbles: `0101` and `0101` → HEX: `0x55`
- Decimal: `64 + 16 + 4 + 1 = 85`

## CSMA/CD (Carrier Sense Multiple Access with Collision Detection)

Used in older Ethernet networks with a shared cable, CSMA/CD manages device communication to avoid data collisions.

### Key Steps

1. **Listen Before Sending**  
   A device checks the cable to ensure it is idle before transmitting data.

2. **Detecting a Collision**  
   If two devices transmit simultaneously, a collision occurs and devices detect this by monitoring electrical signals.

3. **Jam Signal and Random Backoff**  
   - Devices send a jam signal to notify others of the collision.  
   - Each device waits a random time before attempting to retransmit, reducing repeated collisions.

> **Note:** CSMA/CD is largely obsolete today because modern Ethernet switches provide dedicated collision-free channels for each device.

## Ethernet Physical Layer Summary

### Overview
- Ethernet dominates LAN and Internet traffic.
- Evolved to support fiber optics, high speeds (up to 10 Gbps), and long distances (MAN/WAN).
- Uses consistent Ethernet frame format across media types.

### Supported Media and Speeds
- **Media**: UTP copper, optical fiber
- **Common Speeds**:
  - 10 Mbps – 10BASE-T (Ethernet)
  - 100 Mbps – Fast Ethernet
  - 1000 Mbps – Gigabit Ethernet
  - 10 Gbps – 10-Gigabit Ethernet

### Ethernet Generations

#### 1. Historic Ethernet
- **Topology**: Physical bus, logical bus
- **Media**: Coaxial cable (Thicknet 10BASE5, Thinnet 10BASE2)
- **Access Method**: CSMA/CD
- **Limitations**:
  - Shared medium caused collisions
  - Limited scalability and reliability

#### 2. Legacy Ethernet
- **Topology**: Physical star with hubs, logical bus
- **Media**: UTP (10BASE-T)
- **Encoding**: Manchester
- **Connectors**: RJ-45
- **Challenges**:
  - Shared bandwidth
  - Collisions under heavy load
  - Half-duplex communication

#### 3. Current Ethernet (Fast Ethernet)
- **Speed**: 100 Mbps (100BASE-TX, 100BASE-FX)
- **Media**: Cat5 UTP, fiber
- **Encoding**: 4B/5B for signal integrity
- **Topology**: Physical star, logical point-to-point (with switches)
- **Improvements**:
  - Switches replace hubs
  - Full-duplex support eliminates collisions
  - Increased performance and reliability

### Gigabit Ethernet and Beyond
- **Speed**: 1000 Mbps and higher
- **Media**: UTP copper, single-mode & multimode fiber
- **Challenges**:
  - Timing and signal integrity critical
  - More complex encoding/decoding
  - Increased susceptibility to noise

### Key Concepts
- **Encoding**: Ensures synchronization and efficient signal transmission.
- **Switches**: Enable full bandwidth per port, reduce collisions.
- **Full-Duplex**: Allows simultaneous transmission and reception.

## Communication Devices

Computer networking devices are electronic components required for communication and interaction between devices on a computer network. Specifically, they mediate data transmission in a computer network.

Network devices/components can be classified by their location and role in the network.

---

### Core Devices

Core network components interconnect other network components.

#### Gateway
An interface providing compatibility between networks by converting transmission speeds, protocols, codes, or security measures.

#### Router
A networking device that forwards data packets between computer networks. Routers perform the "traffic directing" functions on the Internet. They work on **OSI layer 3**.

#### Switch
Connects devices on a computer network using packet switching to receive, process, and forward data to the destination device. Operates on **OSI layer 2**.

#### Bridge
Connects multiple network segments. Works on **OSI layers 1 and 2**.

#### Repeater
Receives a signal and retransmits it at a higher power or across an obstruction, enabling longer distance transmission.

#### Repeater Hub
Connects multiple Ethernet devices and acts as a single network segment. Operates at **OSI layer 1**. Participates in collision detection by forwarding a jam signal to all ports during a collision. Mostly obsolete today, replaced by switches.

---

### Hybrid Devices

Hybrid components can be found in the core or border of a network.

#### Multilayer Switch
A switch that also provides functionality at higher OSI layers beyond layer 2.

#### Protocol Converter
Converts between two different types of transmission protocols for interoperability.

#### Bridge Router (b-router)
Acts as both a bridge and a router. Routes packets for known protocols and forwards others like a bridge.

---

### Border Devices

These devices typically sit at the connection point of different networks (e.g., internal vs. external networks).

#### Proxy Server
A network service that allows clients to make indirect network connections to other services.

#### Firewall
Hardware or software that enforces network policies by controlling allowed and forbidden communications. Establishes a barrier between trusted internal networks and untrusted external networks (e.g., the Internet).

#### Network Address Translator (NAT)
Converts internal IP addresses to external ones and vice versa. Provided as either hardware or software.

---

### End Stations / Devices

These are user-end devices used for network access or dial-up connections.

#### Network Interface Controller (NIC)
Connects a computer to a wired network.

#### Wireless Network Interface Controller
Connects a computer to a wireless network.

#### Modem
Modulates and demodulates analog signals to transmit digital data over telephone lines.

#### Workstations
Includes laptops, desktops, and IP phones.

