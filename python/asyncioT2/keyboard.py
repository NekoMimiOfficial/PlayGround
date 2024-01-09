import asyncio

class Keyboard:
    def __init__(self):
        self.sock = "./echo.sock"
        self.r: asyncio.StreamReader
        self.w: asyncio.StreamWriter

    async def connect(self):
        r, w = await asyncio.open_unix_connection(self.sock)
        self.r = r
        self.w = w

    async def chatter(self):
        data = input("> ")
        self.w.write(data.encode())
        await self.w.drain()
        self.w.write_eof()
        await self.w.drain()
        await self.w.wait_closed()

    async def run(self):
        await self.connect()
        while True:
            await self.chatter()


keyboard = Keyboard()
asyncio.run(keyboard.run())
