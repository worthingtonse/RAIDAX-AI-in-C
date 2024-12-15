#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

// Constants based on protocol specifications
#define HEADER_SIZE 32
#define MAX_BODY_SIZE 1024
#define ECHO_PORT 8080
#define COMMAND_GROUP_ECHO 0
#define RAIDA_ID 3  // Example RAIDA ID

// Request Header Structure
typedef struct {
    // Routing Group (8 bytes)
    uint8_t version;
    uint8_t split_id;
    uint8_t raida_id;
    uint8_t shard_id;
    uint8_t command_group;
    uint8_t command;
    uint8_t west_id[2];

    // Presentation Group (8 bytes)
    uint8_t pls_version;
    uint8_t application[2];
    uint8_t compression;
    uint8_t translation;
    uint8_t ai_translation;
    uint8_t reserved[2];

    // Encryption Group (8 bytes)
    uint8_t encryption_type;
    uint8_t denomination;
    uint8_t token_sn[4];
    uint16_t body_length;

    // Nonce Group (8 bytes)
    uint8_t nonce[6];
    uint8_t echo[2];
} __attribute__((packed)) RequestHeader;

// Response Header Structure
typedef struct {
    uint8_t raida_id;
    uint8_t shard_id;
    uint8_t status;
    uint8_t command_group;
    uint16_t udp_frame_count;
    uint16_t client_echo;
    uint8_t reserved;
    uint8_t body_size[3];
    uint32_t execution_time;
    uint8_t challenge_response[16];
} __attribute__((packed)) ResponseHeader;

void print_hex(const char* label, const uint8_t *data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

void populate_request_header(RequestHeader *header) {
    // Zero out the entire header first
    memset(header, 0, sizeof(RequestHeader));

    // Routing Group
    header->version = 1;
    header->raida_id = RAIDA_ID;
    header->command_group = COMMAND_GROUP_ECHO;
    header->command = 0;  // Echo command

    // Presentation Group
    header->pls_version = 1;

    // Encryption Group
    header->encryption_type = 0;  // No encryption

    // Generate random nonce and echo bytes
    srand(time(NULL));
    for (int i = 0; i < 6; i++) {
        header->nonce[i] = rand() & 0xFF;
    }
    header->echo[0] = rand() & 0xFF;
    header->echo[1] = rand() & 0xFF;

    // Body length (0 for echo)
    header->body_length = htons(2);  // Terminating bytes length
}

int main(int argc, char *argv[]) {
    const char* server_ip = argc > 1 ? argv[1] : "127.0.0.1";
    int num_requests = argc > 2 ? atoi(argv[2]) : 5;

    int udp_socket;
    struct sockaddr_in server_addr;
    RequestHeader request_header;
    ResponseHeader response_header;

    // Create UDP socket
    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket < 0) {
        perror("UDP Socket creation failed");
        exit(1);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(ECHO_PORT);
    
    // Convert IP address
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("Invalid address");
        exit(1);
    }

    // Set socket timeout
    struct timeval timeout;
    timeout.tv_sec = 5;  // 5 second timeout
    timeout.tv_usec = 0;
    if (setsockopt(udp_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        perror("Socket timeout setting failed");
        exit(1);
    }

    // Perform multiple echo requests
    for (int i = 0; i < num_requests; i++) {
        // Populate request header
        populate_request_header(&request_header);

        printf("\nSending Echo Request %d:\n", i + 1);
        print_hex("Request Header", (uint8_t*)&request_header, sizeof(request_header));

        // Send request
        ssize_t sent_bytes = sendto(udp_socket, 
                                    &request_header, 
                                    sizeof(request_header), 
                                    0, 
                                    (struct sockaddr*)&server_addr, 
                                    sizeof(server_addr));
        if (sent_bytes < 0) {
            perror("Send failed");
            continue;
        }

        // Receive response
        struct sockaddr_in response_addr;
        socklen_t response_addr_len = sizeof(response_addr);
        ssize_t received_bytes = recvfrom(udp_socket, 
                                          &response_header, 
                                          sizeof(response_header), 
                                          0, 
                                          (struct sockaddr*)&response_addr, 
                                          &response_addr_len);

        if (received_bytes < 0) {
            perror("Receive failed");
            continue;
        }

        // Validate response
        printf("Received Echo Response:\n");
        print_hex("Response Header", (uint8_t*)&response_header, sizeof(response_header));

        // Verify key response characteristics
        printf("\nResponse Validation:\n");
        printf("RAIDA ID: %d\n", response_header.raida_id);
        printf("Status: 0x%02X\n", response_header.status);
        printf("Command Group: %d\n", response_header.command_group);
        
        // Verify echo bytes match
        if (memcmp(request_header.echo, &response_header.client_echo, 2) == 0) {
            printf("Echo Bytes Match ✓\n");
        } else {
            printf("Echo Bytes Mismatch ✗\n");
            print_hex("Sent Echo", request_header.echo, 2);
            print_hex("Recv Echo", (uint8_t*)&response_header.client_echo, 2);
        }

        // Short delay between requests
        usleep(100000);  // 100ms
    }

    close(udp_socket);
    return 0;
}
