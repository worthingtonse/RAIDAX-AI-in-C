#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

// Constants based on protocol specifications
#define HEADER_SIZE 32
#define MAX_BODY_SIZE 1024
#define ECHO_PORT 8080
#define COMMAND_GROUP_ECHO 0
#define RAIDA_ID 3  // Example RAIDA ID
#define STATUS_NO_ERROR 0
#define ECHO_STATUS_CODE 0xFA  // Decimal 250
#define MAX_THREADS 50

// Request Header Structure
typedef struct {
    // Same structure as previous implementation
    uint8_t version;
    uint8_t split_id;
    uint8_t raida_id;
    uint8_t shard_id;
    uint8_t command_group;
    uint8_t command;
    uint8_t west_id[2];

    uint8_t pls_version;
    uint8_t application[2];
    uint8_t compression;
    uint8_t translation;
    uint8_t ai_translation;
    uint8_t reserved[2];

    uint8_t encryption_type;
    uint8_t denomination;
    uint8_t token_sn[4];
    uint16_t body_length;

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

// Thread argument structure
typedef struct {
    int socket;
    struct sockaddr_in client_addr;
    socklen_t client_len;
    uint8_t buffer[HEADER_SIZE + MAX_BODY_SIZE];
    ssize_t bytes_received;
} ThreadArgs;

// Mutex for thread synchronization
pthread_mutex_t thread_mutex = PTHREAD_MUTEX_INITIALIZER;
int active_threads = 0;

void print_hex(const uint8_t *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

void prepare_response_header(ResponseHeader *response_header, RequestHeader *request_header, uint16_t frame_count) {
    memset(response_header, 0, sizeof(ResponseHeader));

    response_header->raida_id = RAIDA_ID;
    response_header->shard_id = 0;
    response_header->status = STATUS_NO_ERROR;
    response_header->command_group = COMMAND_GROUP_ECHO;
    
    // Set UDP frame count
    response_header->udp_frame_count = frame_count;

    // Copy client echo bytes
    response_header->client_echo = *(uint16_t*)request_header->echo;

    // Set response status code for Echo
    response_header->status = ECHO_STATUS_CODE;

    // Set body size to 0 (no body)
    response_header->body_size[0] = 0;
    response_header->body_size[1] = 0;
    response_header->body_size[2] = 0;
}

void *handle_udp_client(void *arg) {
    ThreadArgs *thread_args = (ThreadArgs *)arg;
    
    // Ensure thread count doesn't exceed maximum
    pthread_mutex_lock(&thread_mutex);
    if (active_threads >= MAX_THREADS) {
        pthread_mutex_unlock(&thread_mutex);
        free(arg);
        return NULL;
    }
    active_threads++;
    pthread_mutex_unlock(&thread_mutex);

    // Validate received data
    if (thread_args->bytes_received < HEADER_SIZE) {
        fprintf(stderr, "Invalid UDP request header\n");
        goto cleanup;
    }

    RequestHeader *request_header = (RequestHeader*)thread_args->buffer;
    ResponseHeader response_header;

    // Prepare response header with frame count (can be modified based on actual implementation)
    prepare_response_header(&response_header, request_header, 1);

    // Send response header back to client
    ssize_t sent_bytes = sendto(thread_args->socket, 
                                &response_header, 
                                sizeof(response_header), 
                                0, 
                                (struct sockaddr*)&thread_args->client_addr, 
                                thread_args->client_len);

    if (sent_bytes < 0) {
        perror("UDP send failed");
    }

cleanup:
    // Decrement active thread count
    pthread_mutex_lock(&thread_mutex);
    active_threads--;
    pthread_mutex_unlock(&thread_mutex);

    free(arg);
    return NULL;
}

int main() {
    int udp_socket;
    struct sockaddr_in server_addr;
    uint8_t buffer[HEADER_SIZE + MAX_BODY_SIZE];

    // Create UDP socket
    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket < 0) {
        perror("UDP Socket creation failed");
        exit(1);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(ECHO_PORT);

    // Bind socket
    if (bind(udp_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("UDP Binding failed");
        exit(1);
    }

    printf("UDP Echo server listening on port %d\n", ECHO_PORT);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        // Allocate thread arguments
        ThreadArgs *thread_args = malloc(sizeof(ThreadArgs));
        if (!thread_args) {
            perror("Memory allocation failed");
            continue;
        }

        // Receive UDP packet
        thread_args->socket = udp_socket;
        thread_args->client_len = client_len;
        thread_args->bytes_received = recvfrom(udp_socket, 
                                               thread_args->buffer, 
                                               sizeof(thread_args->buffer), 
                                               0, 
                                               (struct sockaddr*)&thread_args->client_addr, 
                                               &thread_args->client_len);

        if (thread_args->bytes_received < 0) {
            perror("UDP receive failed");
            free(thread_args);
            continue;
        }

        // Create thread to handle client request
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_udp_client, thread_args) != 0) {
            perror("Thread creation failed");
            free(thread_args);
            continue;
        }

        // Detach thread to prevent resource leaks
        pthread_detach(thread_id);
    }

    close(udp_socket);
    return 0;
}
