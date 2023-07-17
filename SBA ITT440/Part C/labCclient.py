import socket

def main():
    server_ip = '127.0.0.1'
    server_port = 8888

    # Create socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Prompt user for a number
    number = int(input("Please enter a number: "))

    # Send number to server
    sock.sendto(str(number).encode(), (server_ip, server_port))

    # Receive result from server
    data, server_address = sock.recvfrom(1024)
    result = data.decode()

    print("Result: {}".format(result))

if __name__ == '__main__':
    main()

