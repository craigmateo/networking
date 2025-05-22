# Module 7: ARP and Common Network Utilities

## Address Resolution Protocol (ARP)

ARP maps an IPv4 address to a device’s physical MAC (Media Access Control) address on a Local Area Network (LAN).

### Functions of ARP

- Resolves IPv4 addresses to MAC addresses
- Maintains a cache of mappings (ARP cache)

## Resolving IPv4 Addresses to MAC Addresses

- Ethernet frames require a destination MAC address.
- When an IPv4 packet reaches the data link layer, the device checks its ARP cache for the corresponding MAC address.
- If found, the MAC address is used; if not:
  - An ARP request is broadcast to the local network.
  - All nodes receive the request, but only the device with the matching IP replies.
  - The sender updates its ARP cache with the received MAC address and sends the frame.

## Maintaining a Cache of Mappings

### Adding Entries to the ARP Table

- **Passive learning:** Devices populate the ARP table by observing network traffic.
- **Active querying:** Devices send ARP requests and add responses to the ARP cache.
- Entries are timestamped and expire unless configured statically.

### Getting the Map for a Frame

- ARP checks the cache for a matching MAC address.
- If not found, an ARP request is sent.
  - If a reply is received, the mapping is cached and used.
  - If no reply, the packet is dropped and an error may be reported (e.g., via ICMPv4).

## Mapping Destinations Outside the Local Network

- Frames cannot cross routers, so must first reach a gateway on the local network.
- If the destination is remote:
  - The source compares its IP with the destination's.
  - If they differ, the source sends the packet to the local router (gateway).
  - ARP is used to resolve the MAC address of the gateway.
- Once the MAC address of the gateway is known, the frame is sent.
- The router decapsulates the frame, examines the IPv4 destination, and forwards it accordingly.

## Proxy ARP

Proxy ARP allows a router to respond to ARP requests on behalf of remote hosts, effectively "faking" its identity to deliver packets outside the local network.

### How Proxy ARP Works

- A host may send an ARP request for an IPv4 address outside the local network, rather than sending it to the default gateway.
- A router configured with proxy ARP responds with its own MAC address.
- The host then sends packets to the router, believing it is the final destination.
- The router forwards the packet to the actual remote destination.

### When Proxy ARP Is Used

#### 1. Legacy IPv4 Implementations

- Some older IPv4 stacks always send ARP requests for any destination IP.
- Without proxy ARP, these hosts cannot communicate outside their subnet.
- Cisco routers enable proxy ARP by default on LAN interfaces.

#### 2. Misconfigured Subnet Masks

- A host with an incorrect subnet mask may believe a remote IP is local.
- For example, host A with a `/16` mask believes it is on the 172.16.0.0/16 network.
- When host A sends an ARP request for 172.16.20.100 or 172.16.20.200:
  - The router responds using proxy ARP.
  - Host A maps those addresses to the router's MAC (e.g., `00-00-0c-94-36-ab`).

#### 3. No Default Gateway

- If a host is not configured with a default gateway, proxy ARP can enable communication with remote subnets.
- This avoids the need for static routing or gateway configuration on the host.

## Removing Address Mappings

### ARP Cache Timers

- ARP entries expire after a set time if unused.
- Example: On Windows, ARP entries typically expire after 2 minutes.
  - If reused, the timer may extend (e.g., to 10 minutes).

### Manual Removal of ARP Entries

- ARP entries can be cleared manually using system commands.
- Once removed, new ARP requests and replies are needed to rebuild the mappings.

### Viewing and Managing the ARP Cache (Windows)

- Use the `arp` command to display, add, or remove ARP entries.
- Note: This command only manages the ARP table; it doesn't interact with the ARP protocol itself.
- ARP is a service integrated within IPv4, and its operation is transparent to upper-layer applications and users.

## ARP Broadcast Issues

Because ARP uses broadcast communication, it introduces challenges related to both network performance and security.

### Overhead on the Media

- ARP requests are broadcast frames, meaning every device on the local network must receive and process them.
- In normal conditions on a business network, the impact is minimal.
- However, simultaneous ARP activity by many devices (e.g., students logging into lab computers at once) can temporarily degrade performance.
- Once devices have resolved MAC addresses and cached them, the network load from ARP broadcasts decreases significantly.

### Security

- ARP can expose the network to certain security threats.
- **ARP spoofing (or ARP poisoning)** is a technique used by attackers to send fake ARP messages.
  - The attacker associates their MAC address with the IP address of another device.
  - This causes traffic meant for the legitimate device to be sent to the attacker.
- **Mitigation strategies** include:
  - Manually configuring static ARP associations.
  - Restricting network access to authorized MAC addresses using network device settings.

## Common Network Utilities

TCP/IP utilities are essential for diagnosing network issues and verifying connectivity. Below are 7 core tools that every network technician should understand:

- `Ping`
- `Tracert`
- `ARP`
- `Netstat`
- `Nbtstat`
- `NSLookup`
- `IPConfig`

These tools help you assess the health of your network, troubleshoot issues, and verify connectivity to remote hosts.

---

### Ping

The `ping` utility tests connectivity between two hosts using ICMP (Internet Control Message Protocol). It sends packets to a remote host and waits for a reply.

#### Use Cases
- Verify TCP/IP is installed and the network card is functioning.
- Test connectivity to websites or servers.

#### Examples

- Test the local TCP/IP stack:
  ```sh
  ping 127.0.0.1


