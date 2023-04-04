#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define ONVIF_PORT 3702

int main(int argc, char *argv[]) {
    // Create a UDP socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    // Set socket options for broadcast
    int broadcast = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }
    
    // Set up the destination address for discovery
    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(ONVIF_PORT);
    if (inet_aton("255.255.255.255", &dest_addr.sin_addr) == 0) {
        perror("inet_aton failed");
        exit(EXIT_FAILURE);
    }
    
    // Send the discovery message
    const char *discovery_message = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                                     "<e:Envelope xmlns:e=\"http://www.w3.org/2003/05/soap-envelope\""
                                     " xmlns:w=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\""
                                     " xmlns:d=\"http://schemas.xmlsoap.org/ws/2005/04/discovery\""
                                     " xmlns:dn=\"http://www.onvif.org/ver10/network/wsdl\">"
                                     "<e:Header>"
                                     "<w:MessageID>uuid:9f456d11-919e-4f65-9f47-56b2e4b4a4b4</w:MessageID>"
                                     "<w:To>urn:schemas-xmlsoap-org:ws:2005:04:discovery</w:To>"
                                     "<w:Action>http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe</w:Action>"
                                     "</e:Header>"
                                     "<e:Body>"
                                     "<d:Probe>"
                                     "<d:Types>dn:NetworkVideoTransmitter</d:Types>"
                                     "</d:Probe>"
                                     "</e:Body>"
                                     "</e:Envelope>";
    int bytes_sent = sendto(sockfd, discovery_message, strlen(discovery_message), 0,
                            (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (bytes_sent < 0) {
        perror("sendto failed");
        exit(EXIT_FAILURE);
    }
    
    // Wait for responses
    struct sockaddr_in recv_addr;
    socklen_t recv_addr_len = sizeof(recv_addr);
    char buffer[4096];
    int bytes_received = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                                  (struct sockaddr *)&recv_addr, &recv_addr_len);
    if (bytes_received < 0) {
        perror("recvfrom failed");
        exit(EXIT_FAILURE);
    }
    
    // Print the response
    printf("%.*s\n", bytes_received, buffer);
    
    // Clean up
    close(sockfd);
    return 0;
}
