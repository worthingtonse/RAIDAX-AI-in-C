#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Constants based on protocol specifications
#define HEADER_SIZE 32
#define MAX_BODY_SIZE 1024
#define ECHO_PORT 8080
#define COMMAND_GROUP_ECHO 0
#define RAIDA_ID 3  // Example RAIDA ID
#define STATUS_NO_ERROR 0
#define ECHO_STATUS_CODE 0xFA  // Decimal 250

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

void print_hex(const uint8_t *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

void prepare_response_header(ResponseHeader *response_header, RequestHeader *request_header) {
    memset(response_header, 0, sizeof(ResponseHeader));

    // Set RAIDA ID
    response_header->raida_id = RAIDA_ID;

    // Set shard ID to 0
    response_header->shard_id = 0;

    // Set status to NO_ERROR
    response_header->status = STATUS_NO_ERROR;

    // Set command group
    response_header->command_group = COMMAND_GROUP_ECHO;

    // Copy client echo bytes
    response_header->client_echo = *(uint16_t*)request_header->echo;

    // Set response status code for Echo
    response_header->status = ECHO_STATUS_CODE;

    // Set body size to 0 (no body)
    response_header->body_size[0] = 0;
    response_header->body_size[1] = 0;
    response_header->body_size[2] = 0;
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    uint8_t buffer[HEADER_SIZE + MAX_BODY_SIZE];

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(ECHO_PORT);

    // Bind socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding failed");
        exit(1);
    }

    // Listen for connections
    listen(server_socket, 5);
    printf("Echo server listening on port %d\n", ECHO_PORT);

    while (1) {
        // Accept client connection
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        printf("Client connected\n");

        // Receive request header
        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received < HEADER_SIZE) {
            perror("Invalid request header");
            close(client_socket);
            continue;
        }

        RequestHeader *request_header = (RequestHeader*)buffer;
        ResponseHeader response_header;

        // Prepare response header
        prepare_response_header(&response_header, request_header);

        // Send response header
        if (send(client_socket, &response_header, sizeof(response_header), 0) < 0) {
            perror("Send failed");
        }

        close(client_socket);
    }

    close(server_socket);
    return 0;
}
