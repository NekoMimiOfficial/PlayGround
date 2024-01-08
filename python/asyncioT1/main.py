import asyncio
import signal
import time

async def test():
    await asyncio.sleep(5)
    print("lol")

async def pepe():
    await asyncio.sleep(2)
    print("fuf")

async def joao():
    x = 1
    await asyncio.sleep(7)
    while True:
        print(x)
        await asyncio.sleep(1)
        x += 1

loop = asyncio.get_event_loop()

def miku():
    print("Sekai de ichiban no imesama")
    loop.stop()

loop.add_signal_handler(signal.SIGINT, lambda: loop.stop())
loop.add_signal_handler(signal.SIGTERM, lambda: loop.stop())
loop.add_signal_handler(5, lambda: miku())

loop.create_task(test())
loop.create_task(joao())
loop.create_task(pepe())

# loop.run_until_complete(loop.create_future())
loop.run_forever()
