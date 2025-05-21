# Module 1: Introduction to Network Programming

## Network

- A network consists of two or more devices connected to each other.
- Examples of devices: Laptops/Desktops, Printers, TVs, Phones, Switches, Routers, etc.

## Data Networks

- Data networks facilitate the transmission and reception of digital data between devices.
- Common types of data: Voice, Video streams, Images, Texts, Graphics.

## Communicating over the Network and Network Elements

Networks of data or information vary in size and capabilities, but all networks have four essential elements in common:

1. **Rules or Agreements (Protocols)**: These define how messages are sent, directed, received, and interpreted.
2. **Messages**: The actual data or information being transmitted across the network.
3. **Medium**: The physical or logical infrastructure that connects devices (e.g., cables, wireless signals).
4. **Devices**: The hardware or software entities that communicate with each other through the network.

## OSI Model

The **Open Systems Interconnection (OSI)** model is a reference framework that helps understand data communications between networked systems. It breaks down network functions into seven layers:

1. **Physical Layer**: Defines the connector and interface specifications, along with medium requirements (e.g., cables, hardware connections).
2. **Data Link Layer**: Enables devices to access the network and transmit data. This layer provides a physical address for data transmission (e.g., Ethernet, Token Ring).
3. **Network Layer**: Provides logical addressing to route packets of data across multiple networks (e.g., IP addresses).
4. **Transport Layer**: Manages end-to-end communication between devices, including:
   - **TCP (Transmission Control Protocol)**: Connection-oriented communication.
   - **UDP (User Datagram Protocol)**: Connectionless communication.
5. **Session Layer**: Manages sessions and controls the flow of data, such as tracking byte counts exchanged between endpoints.
6. **Presentation Layer**: Ensures that data is properly formatted for the application to understand (e.g., encryption, compression).
7. **Application Layer**: Provides services for network applications and end users (e.g., file transfer, email).

![OSI Model](https://miro.medium.com/v2/resize:fit:500/format:webp/1*17Zz6v0HWIzgiOzQYmO6lA.jpeg)

## Mapping to the OSI Model (C Program Example)

Here’s how common C program functions map to the OSI model layers:

| **OSI Layer**       | **Corresponding Code/Function**         |
|---------------------|----------------------------------------|
| **7. Application**   | `read()`, `send()`                     |
| **6. Presentation**  | (Handled indirectly through encoding/encryption) |
| **5. Session**       | `accept()`, `close()`                  |
| **4. Transport**     | `socket()`, `listen()`                 |
| **3. Network**       | `bind()` (IP assignment)               |
| **2. Data Link**     | Managed by the OS and network drivers  |
| **1. Physical**      | Ethernet, Wi-Fi, hardware transmission |
