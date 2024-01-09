import asyncio

class Client:
    def __init__(self):
        self.host = 'localhost'
        self.port = 9039
        self.r: asyncio.StreamReader
        self.w: asyncio.StreamWriter

    async def connect(self):
        r, w = await asyncio.open_connection(
            self.host, self.port)

        self.r = r
        self.w = w

    async def send(self, msg: str):
        self.w.write(f"{msg}<NYA_POLICY::SEPARATOR>".encode())
        await self.w.drain()

    async def run(self):
        await self.connect()
        while True:
            cmd = input("[cmd]> ")
            if cmd == "/quit":
                break
            await self.send(cmd)
        await self.send("<NYA_POLICY::DC>")
        self.w.close()


client = Client()
asyncio.run(client.run())
