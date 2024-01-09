import asyncio

class EchoServer:
    def __init__(self):
        self.sock = "./echo.sock"
        self.running = True
    
    async def operation(self, r:asyncio.StreamReader, w:asyncio.StreamWriter):
        data = await r.readline()
        #debug: print received data
        print(f"Received: \"{data.decode()}\" echoing..")
        w.write(data)
        await w.drain()
        w.write_eof()
        await w.drain()
        await w.wait_closed()
    
    async def __start_server(self):
        self.server = await asyncio.start_unix_server(self.operation, self.sock)
        self.addr = self.server.sockets[0].getsockname()
        print(f"address: {self.addr}")
        await self.server.serve_forever()

    def __close_server(self):
        self.server.close()
    
    async def run(self):
        self.running = True
        await self.__start_server()
        while self.running:
            pass
        self.__close_server()

    async def __aenter__(self):
        pass

    async def __aexit__(self):
        self.__close_server()


server = EchoServer()
asyncio.run(server.run())
