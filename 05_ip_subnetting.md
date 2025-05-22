# Module 5: IP Subnetting 

## Understanding IP Addressing, Prefixes, and Subnet Masks

### IP Address Structure
- An IP address consists of:
  - **Network portion**
  - **Host portion**
- Knowing the number of bits for each part is essential.

### Prefix Length
- Indicates how many bits represent the network portion.
- Written in **slash notation**, e.g., `172.16.4.0/24`.
  - `/24` means first 24 bits are network bits.
  - Remaining bits are host bits.
- Different prefix lengths affect:
  - Host range
  - Broadcast address
  - Number of usable hosts

### Prefix vs Subnet Mask
- Both represent the network portion.
- **Prefix length** is easier for humans.
- **Subnet mask** is used by devices.
- Example: `/24` = `255.255.255.0` = binary `11111111.11111111.11111111.00000000`.

### Subnet Mask
- A 32-bit binary value:
  - 1s mark network bits.
  - 0s mark host bits.
- Written in dotted decimal notation.

### Default Subnet Masks for IP Classes

| Class | Default Subnet Mask |
|-------|---------------------|
| A     | 255.0.0.0           |
| B     | 255.255.0.0         |
| C     | 255.255.255.0       |

### Calculating Network Address (NID)
- Use bitwise **AND** between IP address and subnet mask:
  1. Convert IP and mask to binary.
  2. Perform logical AND on each bit.
  3. Convert result back to decimal.

#### Logical AND Table

| A | B | A AND B |
|---|---|---------|
| 0 | 0 | 0       |
| 0 | 1 | 0       |
| 1 | 0 | 0       |
| 1 | 1 | 1       |

### Example Calculations

#### 1. IP: `192.168.123.132`, Mask: `255.255.255.0`

- Convert to binary:
  - IP:    11000000.10101000.01111011.10000100
  - Mask:  11111111.11111111.11111111.00000000
- Perform bitwise AND:
  - Result:11000000.10101000.01111011.00000000
- Convert back to decimal:
  - Network ID: `192.168.123.0`

---

#### 2. IP: `10.10.10.10`, Mask: `255.255.255.0`

- Convert to binary:
  - IP:    00001010.00001010.00001010.00001010
  - Mask:  11111111.11111111.11111111.00000000
- Perform bitwise AND:
  - Result:00001010.00001010.00001010.00000000
- Convert back to decimal:
  - Network ID: `10.10.10.0`

---

#### 3. IP: `128.42.5.4`, Mask: `255.255.248.0`

- Convert to binary:
  - IP:    10000000.00101010.00000101.00000100
  - Mask:  11111111.11111111.11111000.00000000
- Perform bitwise AND:
  - Result:10000000.00101010.00000000.00000000
- Convert back to decimal:
  - Network ID: `128.42.0.0`


## Calculating Broadcast Address

- **Broadcast address** is found by setting all **host bits** in the IP address to 1.

---

### Example: IP `128.42.5.4`, Subnet Mask `255.255.248.0`

- IP in binary:  
  `10000000.00101010.00000101.00000100`

- Subnet mask in binary:  
  `11111111.11111111.11111000.00000000`

- Host bits = inverted subnet mask (last 11 bits):  
  `00000000.00000000.00000111.11111111`

- To get broadcast address:  
  Set all host bits to 1 in IP address.

- Result (binary):  
  `10000000.00101010.00000111.11111111`

- Broadcast address (decimal):  
  `128.42.7.255`

---

### Alternative Method

- Broadcast address = **Network address OR Inverted subnet mask**

Example:  
- IP: `130.45.34.36`  
- Subnet mask: `255.255.240.0` → binary `11111111.11111111.11110000.00000000`  
- Inverted mask: `00000000.00000000.00001111.11111111`

Perform bitwise OR of network address and inverted mask to get broadcast address.

---

This method works for any subnet mask, including non-octet-aligned masks.

## Determine the Number of Usable Hosts Given Network ID and Subnet Mask

- The prefix `/24` denotes the number of network bits in an IP address.
- For `/24`:
  - Network bits = 24 (i.e., 24 ones)
  - Host bits = 32 - 24 = 8 (i.e., 8 zeros)

Subnet mask in binary: 11111111.11111111.11111111.00000000

- **Total number of hosts** is calculated by the formula:  
\( h = 2^x \)  
where \( x \) = number of host bits (zeros).

- For `/24`,  
\( h = 2^8 = 256 \)

- From this total, **2 addresses are reserved**:
- The **network address** (first IP)
- The **broadcast address** (last IP)

- So, **usable hosts** = \( 256 - 2 = 254 \).

---

### Another Example

- IP address: `128.42.0.0/21`
- Network bits = 21
- Host bits = 32 - 21 = 11

- Total number of hosts:  
\( 2^{11} = 2048 \)

- Usable hosts = \( 2048 - 2 = 2046 \)

---

> For better understanding on how to calculate usable host IDs on a network, consider watching a tutorial video.

## Subnetting

**Subnetting** is the process of borrowing bits from the **host** portion of an IP address to divide a larger network into smaller networks called **subnets**. After subnetting, the IP address is split into three fields:  
**NETWORK | SUBNET | HOST**

Two IP addresses are always reserved in each subnet:  
- One for the subnet identifier  
- One for the subnet broadcast address

---

### Benefits of Subnetting

- **Conservation of IP addresses:**  
  Smaller subnets reduce waste of IP addresses. For example, a Class C network has 254 hosts, but if you only need 20 hosts, subnetting avoids wasting 234 addresses.
  
- **Reduced network traffic:**  
  Smaller broadcast domains limit broadcast traffic within subnet boundaries.

- **Simplification:**  
  Easier troubleshooting by isolating problems within smaller subnetworks.

---

### Subnetting Process

- Consider a Class C network with 256 total addresses:  
  - 1 address for the network  
  - 1 address for the broadcast  
  - Leaves 254 addresses for hosts

- Dividing the network into 8 equal subnets results in:  
  - Each subnet has 32 addresses  
  - 2 addresses per subnet reserved for network and broadcast  
  - 30 usable host addresses per subnet  
  - Total usable hosts decrease to 240, but management improves

---

### Example: Using 5 Bits for Subnetting in a Class C Address

- IP address: `192.168.10.44`
- Network bits: originally 24, after subnetting become 24 + 5 = 29 bits
- Subnet mask: `/29` → `255.255.255.248`

---

### Total Number of Subnets

- The subnet mask value `248` in the last octet (`11111000`) shows 5 bits used for subnetting.
- Number of subnets = \( 2^5 = 32 \)
- If the **all-zeros** subnet is not used, subnets reduce to 31.
- If the **all-ones** subnet is also not used, subnets reduce to 30.

---

### Hosts Per Subnet

- Remaining host bits = 3 (because 8 bits in last octet - 5 subnet bits = 3)
- Total hosts per subnet = \( 2^3 = 8 \)
- Usable hosts per subnet = 8 - 2 = 6 (subtract network & broadcast addresses)

---

### Calculating Subnet Addresses

- To find valid subnet addresses for the `/29` mask, subtract 248 from 256:  
  \( 256 - 248 = 8 \), which is the **subnet increment**.
  
- Subnets are:  
  `0, 8, 16, 24, 32, 40, ..., 248`

- The IP `192.168.10.44` belongs to the subnet starting at `192.168.10.40`.

---

### Summary Table

| Subnet | First Host | Last Host | Broadcast |
|--------|------------|-----------|-----------|
| 0      | 1          | 6         | 7         |
| 8      | 9          | 14        | 15        |
| 16     | 17         | 22        | 23        |
| ...    | ...        | ...       | ...       |
| 40     | 41         | 46        | 47        |
| ...    | ...        | ...       | ...       |
| 248    | 249        | 254       | 255       |

---

This breakdown helps you understand how subnetting splits a larger network into smaller, manageable parts with efficient IP usage.

## CIDR Notation

**CIDR** stands for **Classless Inter-Domain Routing** and is an alternative to traditional subnetting. It specifies the number of significant bits in an IP address that make up the network portion by appending a suffix to the IP address.

### Key Points:
- CIDR notation expresses an IP address and its network mask as:  
  `192.168.0.15/24`  
  This means the first 24 bits are significant for network routing (equivalent to subnet mask `255.255.255.0`).

- CIDR enables **supernets** — larger, more flexible network blocks not possible with traditional classful subnet masks.

- Example:  
  Traditional Class C networks `192.168.0.0` and `192.168.1.0` cannot be combined using `255.255.255.0` masks.  
  Using CIDR, they can be combined as:  
  `192.168.0.0/23`  
  where 23 bits define the network portion.

### Binary Representation:

- Network `192.168.0.0` in binary:  
  `11000000.10101000.00000000.00000000`

- Network `192.168.1.0` in binary:  
  `11000000.10101000.00000001.00000000`

- CIDR `/23` means the first 23 bits are network bits, equivalent to subnet mask `255.255.254.0` or binary:  
  `11111111.11111111.11111110.00000000`

- This means the 24th bit can be either 0 or 1, and both addresses still fall within the same network block.

---

### Summary

CIDR provides more flexibility and control over IP address blocks by allowing continuous ranges to be specified with variable-length network prefixes, improving on the limitations of traditional subnetting.

## Addresses for User Devices

Most devices on a network—such as PCs, IP phones, printers, and PDAs—are end-user devices, which require the largest number of IP addresses. IP addresses can be assigned in two main ways: **statically** or **dynamically**.

### Static Assignment of Addresses
- The network administrator manually configures the IP address, subnet mask, and default gateway on each host.
- Commonly used for devices that need a fixed address, like printers and servers.
- Advantages:
  - Ensures devices are always reachable at the same IP.
  - Provides greater control over network resources.
- Disadvantages:
  - Time-consuming to configure each device.
  - Risk of IP address conflicts if addresses are duplicated.
- Requires careful record-keeping of assigned IP addresses.

### Dynamic Assignment of Addresses
- Uses **DHCP (Dynamic Host Configuration Protocol)** to automatically assign IP addresses and other network information.
- The DHCP server manages an **address pool** from which IPs are leased to clients.
- Benefits:
  - Reduces manual configuration and errors.
  - IP addresses are leased temporarily; returned to the pool when devices disconnect.
  - Especially useful for mobile or transient users.
- Preferred for large networks due to ease of management.

---

### Summary

Static IP assignment provides stability and control for important devices, while DHCP offers flexibility and automation for large, dynamic networks.

## Addresses for Hosts Accessible from the Internet

- Devices accessible from outside the corporation are usually servers.
- These devices must have **static IPv4 addresses**.
- Internet-facing servers require **public IP addresses**.
- Often, servers reside in private address spaces internally, requiring the perimeter router or firewall to **translate internal addresses to public addresses (NAT)**.
- Predictable static addresses are crucial for reliable external access.

## Addresses for Intermediary Devices

- Intermediary devices (routers, switches, firewalls) handle most network traffic.
- These devices provide points for network management, monitoring, and security.
- Many intermediary devices require **Layer 3 addresses** for management or operation.
- Devices like hubs, switches, and wireless access points don’t need IP addresses to function but need them for configuration access.
- Addresses for intermediary devices are usually **manually assigned** and kept separate from user device address ranges for predictability.

## Addresses for Routers and Firewalls

- Routers and firewalls have an IPv4 address assigned to **each interface**, with each interface on a different network.
- Router interfaces typically use either the **lowest or highest address** in their network block, consistently applied across the organization.
- These interfaces act as the **gateway** for hosts in their networks.
- Routers/firewalls play a critical role in network security by filtering packets based on source/destination IPs.
- Grouping devices into logical address groups (e.g., users, servers, peripherals, networking devices) allows for more efficient security rule management using summary addresses.
- Summary addresses simplify rule creation and reduce the number of security rules needed.

---

### Address Grouping Example

- Device address groups (user hosts, servers, peripherals, networking devices) are assigned to distinct address blocks within the network.
- The middle octet is marked as `x` to indicate that this addressing scheme can be uniformly applied across similar networks.
- This consistent design enables universal address allocation and security policy enforcement across the organization.


