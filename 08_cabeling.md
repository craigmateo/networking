# Module 8: Basic Cabling and Operation of Protocols

# Data Link Layer Summary

The **Data Link Layer** in the OSI model serves as an intermediary between the network layer and the physical layer. Its main roles include preparing network layer packets for transmission across different physical media and controlling access to those media.

## Key Functions
- **Framing:** Encapsulates packets from the network layer into frames suitable for the specific media.
- **Media Access Control (MAC):** Manages how devices gain access to the physical media and transmit frames.
- **Error Detection:** Checks received frames for errors and discards corrupted frames.
- **Insulation for Upper Layers:** Hides the complexity of different physical media from the upper layers, allowing protocols like IP to function independently of the media type.

## Media and Frame Handling
- Different media (e.g., Ethernet, satellite, wireless) require different data link protocols and frame types.
- At each network hop (e.g., routers), frames are decapsulated and re-encapsulated to match the next media type.
- Data link protocols define frame formats including headers and trailers containing control information such as addressing and error-checking fields.

## Frame Structure
- **Header:** Contains control information like addresses and frame start indicators.
- **Data:** The encapsulated network layer packet.
- **Trailer:** Contains error detection information and frame end markers.

## Sublayers
The Data Link Layer is often divided into:
- **Logical Link Control (LLC):** Handles communication with upper layers.
- **Media Access Control (MAC):** Handles hardware interaction and media access.

This layered and modular approach allows diverse media to be supported and enables innovation in network technologies without affecting higher-layer protocols.

## MAC Techniques Summary

### Overview
- **MAC (Media Access Control)** regulates how data frames are placed onto the physical media.
- Different data link protocols use different MAC methods depending on:
  - How nodes share the media.
  - The network topology (connection structure between nodes).

### MAC for Shared Media
- Shared media means multiple nodes use the same medium simultaneously.
- Two main MAC methods for shared media:
  1. **Controlled Access (Scheduled/Deterministic)**
     - Nodes take turns accessing the medium in a fixed sequence.
     - Predictable and orderly but can be inefficient due to waiting.
  2. **Contention-Based Access (Nondeterministic)**
     - Nodes compete to access the medium whenever they have data.
     - Uses **Carrier Sense Multiple Access (CSMA)** to detect if media is busy.
     - If busy, nodes wait and retry after a short delay.
     - If free, nodes transmit immediately.
     - Collisions can occur if two nodes transmit simultaneously, requiring retransmission.
     - Examples: Ethernet and wireless networks.

#### CSMA Variants
- **CSMA/CD (Collision Detect):**  
  Devices detect collisions and stop transmission, then retry later. Used in traditional Ethernet.
- **CSMA/CA (Collision Avoid):**  
  Devices notify intent before sending data to avoid collisions. Used in 802.11 wireless networks.

### MAC for Non-shared Media
- Non-shared media (e.g., point-to-point links) need minimal or no media access control.
- Data link protocols focus on duplex mode:
  - **Half-Duplex:** Devices transmit or receive at one time, but not simultaneously.  
    Arbitration rules resolve conflicts.
  - **Full-Duplex:** Devices can transmit and receive simultaneously; no arbitration needed.

## Logical Topology vs. Physical Topology Summary

### Network Topology Overview
- **Topology**: Arrangement and relationship of network devices and their interconnections.
- Two views of topology:
  - **Physical topology**: Actual physical layout of nodes and connections.
  - **Logical topology**: How data frames move logically between nodes, independent of physical layout.

### Logical Topology
- Defined by virtual connections between nodes.
- Determined by data link layer protocols.
- Influences network framing and MAC methods.
- Controls media access when multiple nodes share the same medium.

### Types of Topologies

#### Point-to-Point Topology
- Direct connection between two nodes.
- Simple MAC protocols; only two nodes transmit frames.

- **Duplex Modes**:
  - Half-duplex: Data flows one direction at a time.
  - Full-duplex: Data flows both directions simultaneously.

- Logical connections may include intermediate devices (virtual circuits) but do not change the logical topology.

- Media access depends on logical topology, not physical layout.

#### Multiaccess Topology
- Multiple nodes share the same medium.
- Only one node transmits at a time.
- All nodes receive frames, but only the addressed node processes them.

- MAC methods regulate access to reduce collisions, such as:
  - CSMA/CD
  - CSMA/CA
  - Token-passing

- Data link protocols balance control, protection, and overhead.

#### Ring Topology
- Nodes are logically arranged in a ring.
- Each node receives and passes frames along unless it is the destination.
- Controlled MAC method: token passing — only the token holder transmits.
- Physical cabling can differ from logical ring arrangement.

## Data Link Layer Protocols

OSI Layer 2 protocols work with IP at Layer 3, but the Layer 2 protocol depends on network topology and physical media.

Common Layer 2 protocols include:

- Ethernet  
- PPP  
- HDLC  
- Frame Relay  
- ATM  

The choice of protocol depends on network size and services. Figure 9 illustrates various Layer 2 frames transporting packets across an internetwork.

---

**Figure 9: Examples of Layer 2 Protocols**

An internetwork has two types of environments: LANs and WANs. Each of these environments have different requirements for frames.

A LAN typically uses a high-bandwidth technology that is capable of supporting large numbers of hosts. A LAN’s relatively small geographic area (a single building or a multi-building campus) and its high density of users make this technology cost effective.

However, using a high-bandwidth technology is usually not cost effective for WANs that cover large geographic areas (cities or multiple cities, for example). The cost of the long distance physical links and the technology used to carry the signals over those distances typically result in lower-bandwidth capacity.

The frames moving through WANs are exposed to more detrimental environments than those of LANs. This means that the frames traveling across WANs are more likely to be damaged than those in LANs. A difference in bandwidths and environments normally results in the use of different protocols for LANs and WANs, as described in the following sections.

---

### Ethernet Protocol for LANs

Ethernet, defined by IEEE 802.2 and 802.3, is the most common LAN technology supporting speeds from 10 Mbps to 10 Gbps.

Its frame format and OSI Layers 1 and 2 sublayers are consistent across variants, though media access methods vary.

Ethernet uses CSMA/CD for unacknowledged, connectionless communication over shared media, identifying devices by 48-bit MAC addresses in hexadecimal.

The Ethernet frame includes several key fields (see Figure 10).

---

**Figure 10 - Ethernet Protocol**

- **Preamble:** Used to time synchronization; this also contains a delimiter to mark the end of the timing information.  
- **Destination Address:** 48-bit MAC address for the destination node.  
- **Source Address:** 48-bit MAC address for the source node.  
- **Type:** Value to indicate which upper-layer protocol will receive the data after the Ethernet process is complete.  
- **Data or payload:** This is the PDU, typically an IPv4 packet that is to be transported over the media.  
- **Frame Check Sequence (FCS):** A CRC value used to check for damaged frames.

---

### PPP for WANs

PPP is a WAN protocol defined by RFCs, used to deliver frames between two nodes over various physical media like twisted-pair, fiber, satellite, and virtual links.

It uses sessions to create logical point-to-point connections, hiding physical media details and allowing multiple protocols to be encapsulated.

PPP sessions support option negotiation for:
- **Authentication:** Verifies nodes before communication.
- **Compression:** Reduces frame size to speed transmission.
- **Multilink:** Combines multiple physical links into one session.

Figure 11 shows the following basic fields in a PPP frame:

---

**Figure 11: Point-to-Point Protocol**

- **Flag:** A single byte that indicates the beginning or end of a frame. The flag field consists of the binary sequence 01111110.  
- **Address:** A single byte that contains the standard PPP broadcast address. PPP does not assign individual station addresses.  
- **Control:** A single byte that contains the binary sequence 00000011, which calls for transmission of user data in an un-sequenced frame.  
- **Protocol:** Two bytes that identify the protocol encapsulated in the data field of the frame.  
- **Data:** Zero or more bytes that contain the datagram for the protocol specified in the protocol field.  
- **Frame Check Sequence (FCS):** Normally 16 bits (2 bytes). By prior agreement, consenting PPP implementations can use a 32-bit (4-byte) FCS for improved error detection.

---

### Wireless Protocol for LANs

IEEE 802.11 (Wi-Fi) extends the 802 standards, using the same 802.2 LLC and 48-bit addressing but differs in MAC and physical layers to address wireless challenges like lack of physical connectivity and interference.

It uses a contention-based CSMA/CA media access with random backoff to reduce collisions. Data link acknowledgments ensure successful frame delivery by retransmitting if no acknowledgment is received.

802.11 also supports authentication, association (connecting devices), and privacy through encryption. The 802.11 frame includes fields for these services.

Figure 12:

---

**Figure 12: 802.11 Wireless LAN Protocol**

- **Protocol Version:** Version of 802.11 frame in use.  
- **Type and Subtype:** Identifies one of three functions and sub-functions of the frame: control, data, and management.  
- **To DS:** Set to 1 in data frames destined for the distribution system (devices in the wireless structure).  
- **From DS:** Set to 1 in data frames exiting the distribution system.  
- **More Fragments:** Set to 1 for frames that have another fragment.  
- **Retry:** Set to 1 if the frame is a retransmission of an earlier frame.  
- **Power Management:** Set to 1 to indicate that a node will be in power-save mode.  
- **More Data:** Set to 1 to indicate to a node in power-save mode that more frames are buffered for that node.  
- **Wired Equivalent Privacy (WEP):** Set to 1 if the frame contains WEP-encrypted information for security.  
- **Order:** Set to 1 in a data type frame that uses Strictly Ordered service class (does not need reordering).  
- **Duration/ID:** Depending on the type of frame, represents either the time, in microseconds, required to transmit the frame or an association identity (AID) for the station that transmitted the frame.  
- **Destination Address (DA):** MAC address of the final destination node in the network.  
- **Source Address (SA):** MAC address of the node that initiated the frame.  
- **Receiver Address (RA):** MAC address that identifies the wireless device that is the immediate recipient of the frame.  
- **Transmitter Address (TA):** MAC address that identifies the wireless device that transmitted the frame.  
- **Sequence Number:** Indicates the sequence number assigned to the frame; retransmitted frames are identified by duplicate sequence numbers.  
- **Fragment Number:** Indicates the number for each fragment of a frame.  
- **Frame Body:** Contains the information being transported; for data frames, typically an IP packet.  
- **FCS:** Contains a 32-bit cyclic redundancy check (CRC) of the frame.

## Following Data through an Internetwork

### Overview  
Understanding network communication involves examining how data passes through each layer between two hosts. This example follows an HTTP GET request from a client to a remote web server across an internetwork.

### Assumptions  
- Routing tables and ARP caches are complete.  
- DNS lookup is cached.  
- TCP session is established.  
- PPP physical circuit and session between routers are active.

### Client Side Processing  
- The browser initiates an HTTP GET request.  
- **Application Layer:** Adds HTTP header.  
- **Transport Layer:** Adds TCP header with source port (12345), destination port (80), sequence numbers, and flags.  
- **Network Layer:** Creates IP packet with source and destination IP addresses.  
- **Data Link Layer:** Uses ARP to find MAC address of Router B (default gateway), builds Ethernet II frame, and sends it using CSMA/CD and Manchester encoding.

### Router B Processing  
- Receives and verifies Ethernet frame via CRC.  
- Decapsulates frame, extracts IP packet.  
- Looks up routing table, forwards packet in a PPP frame over WAN link to Router A.

### Router A Processing  
- Receives and verifies PPP frame.  
- Decapsulates frame, forwards IP packet on LAN segment toward web server.  
- Uses ARP to find web server MAC address.  
- Builds Ethernet II frame and transmits using 4B/5B encoding.

### Web Server Processing  
- Receives and verifies Ethernet frame.  
- Decapsulates frame, passes IP packet to network layer.  
- Confirms destination IP address matches its own.  
- Processes TCP segment, reassembles data using sequence numbers.  
- Delivers HTTP GET request to web server application for response.

## Physical Layer

The OSI physical layer is responsible for encoding binary digits from data link layer frames into signals and transmitting/receiving these signals across physical media like copper wires, optical fiber, and wireless. The bits represent all upper-layer information and must be transmitted reliably despite media distortions and interference.

### Key Functions:
- Encode data-link frames into recognizable signal patterns.
- Use physical media and connectors to transmit signals.
- Represent bits as voltage, light, or radio waves.
- Include control signals to mark the start and end of frames.
- Decode received signals back into bits for the data link layer.

### Physical Layer Elements:
- Physical media and connectors
- Bit representation on media
- Encoding of data and control info
- Transmitter and receiver circuitry

### Operation:
- Each medium uses unique signaling but IP frames remain unchanged.
- Signal patterns mark frame boundaries to avoid transmission failure.
- Physical communication relies on:
  - Physical components
  - Encoding
  - Signaling

Encoding groups bits into patterns recognizable by Layer 1 devices and adds control codes for frame boundaries. Signaling converts these patterns into signals appropriate to the medium (e.g., voltage changes on copper).

### Signaling and Encoding:
- Converts logical binary data into physical energy signals.
- Signals represent bits within defined bit times (time to send one bit).
- Synchronization between sender and receiver ensures bits are read correctly.

### Signal Variations:
- Amplitude (signal strength)
- Frequency (signal rate)
- Phase (signal position)

All devices must use the same signaling method to communicate successfully.

### Signaling Methods:

**Nonreturn to Zero (NRZ):**  
- Samples voltage during bit time; high voltage = 1, low voltage = 0  
- No constant zero voltage; requires extra signaling for synchronization  
- Less efficient and more prone to interference; used on lower-speed links  

**Manchester Encoding:**  
- Voltage changes in the middle of bit time indicate bits  
- Low-to-high transition = 1, high-to-low = 0  
- Transitions at bit edges handle consecutive identical bits  
- Standard for 10BASE-T Ethernet (10 Mbps)  

Higher-speed links use other encoding standards.

---

*Figures referenced in the original text illustrate encapsulation, encoding, and signal patterns.*

## Physical Media

### Connecting Communication

The physical layer handles network media and signaling, representing bits as voltages, radio frequencies, or light pulses. Standards ensure cables and connectors work correctly with data link layers.

### Types of Physical Media

This layer sets standards for network components like copper and fiber cables and defines how bits are transmitted electrically or optically.

### Copper Media

Copper is the most common medium for LANs, connecting hosts to devices. It carries data as electrical pulses, but is vulnerable to noise and attenuation. Cable design improvements reduce these effects.

#### Copper Cable Types

- **Unshielded Twisted-Pair (UTP):** Most common, with four twisted pairs to minimize interference (crosstalk). Categories (Cat 3, 5, 5e, 6) define performance and bandwidth. Uses RJ-45 connectors with TIA/EIA 568A or 568B wiring standards.
- **Coaxial Cable:** Legacy LAN medium with a central copper wire and outer shielding, now mostly used for wireless antenna connections.
- **Shielded Twisted-Pair (STP):** Twisted pairs with additional shielding to reduce EMI, mostly replaced by Ethernet but useful in high-interference environments.

#### Copper Safety

Copper cables carry current and may pose risks like electrical shorts or lightning damage, especially over long runs between buildings. Fiber or wireless connections can mitigate these risks.

### Fiber Media

Fiber-optic cables use light pulses through glass or plastic cores, allowing higher bandwidth and longer distances without signal boosters. Fiber is immune to electrical interference and safer over long distances.

- **Single-mode fiber:** Small core, less light dispersion, suitable for long distances.
- **Multimode fiber:** Larger core, used for shorter distances.

Fiber cables usually have paired cores for full-duplex communication. Light sources include lasers or LEDs, and photodiodes decode signals at the receiver. Special handling and training are required for fiber installation.
