import asyncio
from subprocess import getoutput

class Server:
    def __init__(self):
        self.host = 'localhost'
        self.port = 9039
        self.server: asyncio.Server
        self.running = "No"
        self.loop = asyncio.get_event_loop()
        self.TR = True
        self.TVAL = 'on'

    async def runOpCode(self, c):
        if c == "<DEV_CTL::LIGHTS>":
            getoutput("termux-vibrate -d 40")
            getoutput(f"termux-torch {self.TVAL}")
            self.TVAL = 'off'

        elif c.startswith("<DEV_CTL::NOTIFY>"):
            part = c.split("CTL::NOTIFY>", 1)[1]
            if "][" in part:
                if part.startswith("[") and part.endswith("]"):
                    title = part.split("][", 1)[0].removeprefix("[")
                    body = part.split("][", 1)[1].removesuffix("]")
                    getoutput(f"termux-notification -t \"{title}\" -c \"{body}\" ")
        
        elif c == "<DEV_CTL::SRVQ>":
            self.running = "Dieing"
            self.TR = False
            self.server.close()
            await self.server.wait_closed()
            exit(0)

    async def handler(self, r:asyncio.StreamReader, w:asyncio.StreamWriter):
        while True:
            raw = await r.readuntil("<NYA_POLICY::SEPARATOR>".encode())
            data = raw.decode()
            data = data.removesuffix("<NYA_POLICY::SEPARATOR>")
            await self.runOpCode(data)
            if data == "<NYA_POLICY::DC>":
                break

    async def serve(self):
        self.server = await asyncio.start_server(
            self.handler, self.host, self.port
        )

    async def thread(self):
        while self.TR:
            while self.running == "Yes":
                await self.server.start_serving()

    async def run(self):
        await self.serve()
        async with self.server:
            await self.server.serve_forever()
        # srv = self.loop.create_task(self.thread())
        # print("I: started server")
        # while True:
            # await self.server.start_serving()
        # com = input("$: ")
        # while not com.startswith("/quit"):
        #     if com.startswith("/port "):
        #         try:
        #             port = int(com.split(" ", 1)[1])
        #             self.port = port
        #         except:
        #             print("E: Invalid port")
        #
        #     elif com.startswith("/stats"):
        #         print(f"Host: {self.host}")
        #         print(f"Port: {self.port}")
        #         print(f"                 ")
        #         print(f"Serving: {self.running}")
        #
        #     elif com.startswith("/close"):
        #         if self.running == "Yes":
        #             self.running = "No"
        #             print("I: closed server")
        #         else:
        #             print("I: server already offline")
        #
        #     elif com.startswith("/help"):
        #         print("I: Available commands:")
        #         print("=============================")
        #         print("/stats    shows server status")
        #         print("/port PORT  sets current port")
        #         print("/serve          start serving")
        #         print("/close           stop serving")
        #         print("/help")
        #         print("=============================")
        #         print("to exit use the /quit command")
        #
        #     elif com.startswith("/serve"):
        #         if self.running == "No":
        #             self.running = "Yes"
        #             print("I: started serving")
        #         else:
        #             print("I: already serving")
        #
        #     else:
        #         print("E: invalid command.. [/help][/quit]")
        #     com = input("$: ")
        #
        # self.running = "Dieing"
        # await asyncio.sleep(0.1)
        # self.TR = False


server = Server()
asyncio.run(server.run())
