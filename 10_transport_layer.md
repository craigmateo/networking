# Module 10: Transport Layer Protocols and Purpose of Port Numbers

## Transport Layer

The **Transport Layer** is the 4th layer in the OSI model responsible for **end-to-end communication** between applications on different hosts. It enables multiple applications on a single device to communicate over the network simultaneously, ensuring data is delivered reliably and in order.

---

### Purpose

- Provides **transparent data transfer** between end users.
- Ensures **reliable data transfer** using flow control, segmentation, error control, and error recovery.
- Supports **connection-oriented** and **stateful protocols** that track segments and retransmit lost data.

---

### Key Responsibilities

- Tracking multiple simultaneous communications (conversations) between applications.
- Segmenting large application data into smaller **segments** for efficient transmission.
- Reassembling out-of-order segments into the correct sequence at the destination.
- Identifying applications via **port numbers** to direct data correctly.
- Managing **flow control** to prevent network resource overload.
- Handling **error recovery** by retransmitting lost or corrupted data.
- Initiating and managing sessions (connection setup) for communication.

---

### How It Works

- Multiple applications (email, web, messaging, VoIP) send data concurrently.
- The transport layer keeps each application’s data separate and directs it properly.
- Segmentation breaks data into manageable parts with headers for tracking.
- Segments may travel different routes and arrive out of order, but are reassembled correctly.
- Uses port numbers to distinguish between applications on the same host.
- Regulates data flow and retransmits lost segments for reliability.

---

The transport layer acts as the bridge between the **application layer** and the **network layers**, ensuring smooth, reliable communication regardless of the underlying network details.

## Transport Layer: Port Addressing

### Port Addressing

TCP and UDP services keep track of the various applications that are communicating. To differentiate the segments and datagrams for each application, both TCP and UDP have header fields that uniquely identify these applications.

---

### Identifying the Conversations

Each segment or datagram header contains a **source port** and **destination port**:

- **Source port:** The port number associated with the originating application on the local host.
- **Destination port:** The port number associated with the destination application on the remote host.

Port numbers are assigned differently depending on whether the message is a **request** or a **response**.

- Server processes use **static port numbers** assigned to them.
- Clients dynamically choose a port number for each conversation.

When a client sends a request to a server:

- The **destination port** is the static port number of the server process.
- The client software must know the server's port number (default or manually configured).
  
Example:  
A web browser sends a request to a web server using TCP and destination port **80** (the default port for HTTP).

The **source port** in the client’s request header is randomly generated, as long as it does not conflict with other ports in use on the system. This source port acts like a return address for the requesting application.

The transport layer keeps track of this port and the requesting application so that responses can be forwarded correctly. The source port number of the request becomes the **destination port** in the server’s response.

---

### Sockets and Socket Pairs

The combination of a transport layer **port number** and a network layer **IP address** uniquely identifies a specific process on a host. This combination is called a **socket**.

- Sometimes "port number" and "socket" are used interchangeably.
- Here, a **socket** = IP address + port number.

A **socket pair** consists of the source and destination IP addresses and port numbers, uniquely identifying a conversation between two hosts.

**Example:**  
- A web server running on IPv4 address `192.168.1.20` at port `80` is identified as socket `192.168.1.20:80`.
- A client at `192.168.100.48` with a dynamic port `49152` is identified as socket `192.168.100.48:49152`.

---

### Port Addressing Types and Tools

The **Internet Assigned Numbers Authority (IANA)** assigns port numbers.

Port number ranges:

| Port Type           | Number Range   | Description                                      |
|---------------------|----------------|------------------------------------------------|
| Well-known ports    | 0 to 1023      | Reserved for services and applications (e.g., HTTP, SMTP) |
| Registered ports    | 1024 to 49151  | Assigned to user processes or applications      |
| Dynamic/private ports| 49152 to 65535 | Assigned dynamically to client applications     |

#### Well-Known Ports

- Reserved for server applications.
- Common services: HTTP (80), POP3/SMTP (email), Telnet, etc.
- Clients use these ports to connect to services.

#### Registered Ports

- Assigned to user-installed applications.
- Clients can dynamically select a registered port as a source port.

#### Dynamic or Private Ports

- Also called **ephemeral ports**.
- Typically assigned dynamically to client applications initiating connections.
- Rarely used as destination ports except in peer-to-peer applications.

---

### Using Both TCP and UDP

Some applications use **both** TCP and UDP protocols.

Example:  
**DNS** uses UDP for fast, low-overhead queries, but TCP for reliable transmission of larger data. Both use port number 53.

---

### Common Ports for TCP and UDP

Examples of well-known and registered ports are often listed in port tables, like:

| Service       | TCP Port | UDP Port |
|---------------|----------|----------|
| HTTP          | 80       | -        |
| DNS           | 53       | 53       |
| SMTP          | 25       | -        |
| DHCP          | -        | 67, 68   |

---

### The `netstat` Command

`netstat` is a network utility used to display active TCP connections on a host.

- Shows protocol, local address and port, remote address and port, and connection state.
- Helps identify unexplained or unwanted TCP connections, which may be security risks.
- Also useful for troubleshootin

## Transport Layer: Segmentation and Reassembly

An application passes data down through various protocols to create a Protocol Data Unit (PDU) that is transmitted over the network medium. At the application layer, data is segmented into pieces before transmission.

- A UDP segment is called a **datagram**.
- A TCP segment is simply called a **segment**.

The headers differ in their functions:

- **UDP header:** Contains source and destination ports.
- **TCP header:** Contains source and destination ports, plus sequencing, acknowledgments, and flow control.

At the destination host, the process reverses, and the data is reassembled and passed up to the application.

---

### Why Segmentation?

Some applications transmit very large amounts of data—sometimes many gigabytes. Sending all data in one large chunk would be impractical because:

- It could take minutes or hours to send.
- No other network traffic could be transmitted simultaneously.
- If errors occur, the entire data file would need to be resent.
- Network devices lack large enough memory buffers to store huge chunks during transmission or reception.

Segment size varies based on the network technology and physical medium used.

---

### Segmentation Benefits

Dividing application data into segments:

- Ensures data fits within media limits.
- Enables multiplexing data from different applications onto the same medium.

---

### TCP vs UDP Segmentation

- **TCP:**  
  Each segment header contains a **sequence number**. This allows the destination’s transport layer to reassemble segments in the correct order, ensuring the application receives data exactly as sent.

- **UDP:**  
  Tracks conversations but does **not** include sequence numbers in the header. It does not guarantee order or connection maintenance. UDP’s simpler design reduces overhead and can result in faster data transfer.

---

### Handling Out-of-Order Packets

Packets can arrive out of order because they may take different network paths. Applications using UDP must tolerate that data might not arrive in the order it was sent.

---

*Figure 13 illustrates Transport Layer functions including segmentation and reassembly.*

## Transmission Control Protocol (TCP)

TCP is a connection-oriented protocol that ensures reliable, ordered delivery of data between hosts.

### Key Concepts

- **Connection Establishment:** Uses a three-way handshake (SYN, SYN-ACK, ACK) to start a session.
- **Data Transfer:** Data segments are tracked with sequence and acknowledgment numbers for reliability.
- **Connection Termination:** Uses a four-step process with FIN and ACK flags to close sessions.
- **Control Flags:** Important TCP flags include SYN (start connection), ACK (acknowledge data), FIN (end connection), RST (reset connection), PSH (push data), and URG (urgent data).
- **Flow Control:** TCP uses windowing and acknowledgments to control data flow and retransmit lost segments.

TCP provides reliable, ordered, and error-checked delivery of a stream of bytes between applications.

## User Datagram Protocol (UDP)

UDP is a simple, connectionless protocol with low overhead. It does not guarantee reliability, ordering, or flow control like TCP.

### Key Points

- **Low Overhead vs. Reliability:**  
  UDP is faster due to minimal protocol features. Applications needing reliability must handle it themselves. Suitable for real-time apps (games, VoIP) and simple queries (DNS).

- **Datagram Reassembly:**  
  UDP sends data in datagrams without establishing sessions. Datagrams may arrive out of order, and UDP delivers them as received. Ordering is left to the application.

- **Server Processes:**  
  UDP servers listen on well-known ports and receive datagrams sent to those ports.

- **Client Processes:**  
  UDP clients pick a random source port and send datagrams to server ports. Since UDP is connectionless, data is sent immediately once ports are set.

- **Communication:**  
  Source and destination ports remain constant during a transaction, with roles reversed for return data.


