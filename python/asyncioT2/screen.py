import asyncio

class Screen:
    def __init__(self):
        self.sock = "./echo.sock"
        self.r: asyncio.StreamReader
        self.w: asyncio.StreamWriter

    async def connect(self):
        r, w = await asyncio.open_unix_connection(self.sock)
        self.r = r
        self.w = w

    async def monitor(self):
        data = await self.r.readline()
        print(f"[Server]> {data.decode()}")

    async def run(self):
        await self.connect()
        while True:
            await self.monitor()


screen = Screen()
asyncio.run(screen.run())
