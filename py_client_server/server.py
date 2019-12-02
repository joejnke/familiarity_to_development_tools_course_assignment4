import clieServModule

def server(port_num):
    return clieServModule.server(port_num)

def start_serving(server_fd):
    clieServModule.startServer(server_fd)

if __name__ == "__main__":
    port = 8080
    server_fd = server(port)
    start_serving(server_fd)