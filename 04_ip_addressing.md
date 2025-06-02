# Module 4: IP Addressing

## 📘 Introduction
Welcome to Module 4 of your network programming course. This module covers IP addressing in detail, including addressing schemes, IP versions, and address types.

---

### 🎯 Learning Outcomes

By the end of this module, you should be able to:

- Explain the importance of addressing and naming schemes in IP network communications.
- Identify the MAC address of devices and explain its benefits in IP networks.
- Explain the coexistence of IP versions (IPv4 and IPv6).
- Perform Binary ↔ Decimal conversions.
- Identify different IPv4 classes and their default subnet masks.
- Distinguish between public and private network addresses.
- Explain:
  - Network address
  - Broadcast address
  - Unicast address
  - Multicast address
- Describe IPv6 address structure and identify its segments and types.

---

### 🗝️ Key Terms and Concepts

| Term | Description |
|------|-------------|
| **NIC (Network Interface Card)** | A chip on the motherboard that converts data into electrical signals for network transmission. |
| **OUI (Organizationally Unique Identifier)** | First 3 octets (24 bits) of a MAC address identifying the NIC manufacturer. |
| **Dual Stack** | Ability to run IPv4 and IPv6 in parallel on the same device or network. |
| **NAT (Network Address Translation)** | Converts internal (private) IP addresses to external (public) IPs for outbound communication. |

---

## Importance of Addressing and Naming Schemes in IP Networks

- Proper **addressing** and **naming schemes** are essential for managing and controlling networks efficiently.
- They help **identify nodes** (devices) correctly, simplify **network troubleshooting**, and ensure **security**.
- A well-structured addressing scheme makes it easier to detect problems and maintain security in the network.

## Network Addressing

In networking, there are two key types of addresses:

1. **MAC Address** (Physical address): Unique to the hardware, used for communication within the local network.
2. **IP Address** (Logical address): Assigned to each device in the network, used for routing traffic between networks.

### MAC Address
- A **MAC address** is a unique identifier assigned to each network interface card (NIC).
- It is usually represented as a string of six pairs of hexadecimal digits, separated by colons.

Example:
00:0a:95:9d:68:16

- MAC addresses help with **troubleshooting** and **MAC filtering** in networks.

### IP Address
- An **IP address** is assigned to every device connected to a TCP/IP-based network.
- It is logical, meaning it can be changed, unlike a MAC address, which is fixed to the device.
- IPv4 addresses are **32 bits** long, while IPv6 addresses are **128 bits** long.

Example IPv4 address:
172.16.81.100


## Binary to Decimal Conversion

Understanding how IP addresses are represented in binary and decimal is crucial for grasping how networks work.

- **Example Conversion**:

    ```
    Decimal: 10.1.23.19
    Binary: 00001010.00000001.00010111.00010011
    ```

- The process involves converting each octet (8 bits) from binary to decimal:
    - 1st octet: `00001010` (binary) = 10 (decimal)
    - 2nd octet: `00000001` (binary) = 1 (decimal)
    - 3rd octet: `00010111` (binary) = 23 (decimal)
    - 4th octet: `00010011` (binary) = 19 (decimal)

## IPv4 Class

IPv4 addresses are divided into five classes: A, B, C, D, and E. Each class serves different purposes.

| Class  | Network Bits | Host Bits | Range              | Example Address      |
|--------|---------------|-----------|--------------------|----------------------|
| A      | 8 bits        | 24 bits   | 1.0.0.0 to 127.255.255.255 | 10.0.0.1           |
| B      | 16 bits       | 16 bits   | 128.0.0.0 to 191.255.255.255 | 172.16.0.1        |
| C      | 24 bits       | 8 bits    | 192.0.0.0 to 223.255.255.255 | 192.168.1.1      |
| D      | N/A           | N/A       | Reserved for multicast | 224.0.0.1          |
| E      | N/A           | N/A       | Reserved for experimental use | 240.0.0.1          |

### Network Masks

A **network mask** helps identify the **network** and **host** portions of an IP address.

- **Class A**: `255.0.0.0`
- **Class B**: `255.255.0.0`
- **Class C**: `255.255.255.0`

### Private and Public IP Addresses

- **Private IP Address**: Used within private networks and not routable over the internet.
    - Example: `192.168.1.1`
- **Public IP Address**: Used for routing over the internet.
    - Example: `8.8.8.8` (Google DNS)

## Network Address and Broadcast Address

- **Network Address**: The first address in a network, used to identify the **network segment**. It cannot be assigned to a device.
    - Example: For the network `192.168.1.0/24`, the network address is `192.168.1.0`.

- **Broadcast Address**: The last address in the network, used to send packets to **all devices** in the network.
    - Example: For the network `192.168.1.0/24`, the broadcast address is `192.168.1.255`.

Example Network:
Network Range: 192.168.1.0 - 192.168.1.255 Network Address: 192.168.1.0 Broadcast Address: 192.168.1.255 Usable IP Range: 192.168.1.1 to 192.168.1.254


## Unicast and Multicast Addresses

- **Unicast**: A **one-to-one** communication between devices.
    - Example: Sending data from one computer to another.

- **Multicast**: A **one-to-many** communication where data is sent to a group of devices.
    - Example: Streaming a video to multiple users at once.

## IPv6 Address

IPv6 is the next-generation IP address format, introduced to solve the limitations of IPv4, particularly the exhaustion of available addresses.

- IPv6 uses **128 bits** for the address, compared to IPv4’s **32 bits**.
- An example of an IPv6 address:
    ```
    2001:0db8:85a3:0000:0000:8a2e:0370:7334
    ```
    This can be shortened as:
    ```
    2001:db8:85a3::8a2e:370:7334
    ```

### Network and Node Addresses (IPv6)

IPv6 also divides the address into two components:
1. **Network Prefix**: Identifies the network.
2. **Interface Identifier**: Identifies the device on the network.

**Example**:
Network Prefix: 2001:db8:85a3:: Interface Identifier: 8a2e:0370:7334

For more details on IPv6 addressing, refer to the official [IPv6 Overview by Oracle](https://docs.oracle.com/cd/E18752_01/html/816-4554/ipv6-overview-10.html).
