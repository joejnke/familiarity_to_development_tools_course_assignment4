import clieServModule

def client(port_num):
    return clieServModule.client(port_num)

def send_request(client_fd):
    clieServModule.request(client_fd)

if __name__ == "__main__":
    port = 8080
    client_fd = client(port)
    send_request(client_fd)