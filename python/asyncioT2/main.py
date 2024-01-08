import asyncio
import signal

loop = asyncio.get_event_loop()
srv = loop.create_unix_server(asyncio.protocols.BufferedProtocol, "./lock")
clt = loop.create_connection(asyncio.protocols.BufferedProtocol, "127.0.0.1")

async def crtSrv():
    await srv.throw(BaseException.add_note(BaseException, "fuf"))
    await srv.send("henlo")

async def gets():
    await clt.send("hewwo")

loop.add_signal_handler(signal.SIGINT, lambda: loop.stop())
loop.add_signal_handler(signal.SIGTERM,lambda: loop.stop())
loop.create_task(crtSrv())
loop.create_task(gets())
loop.run_forever()
