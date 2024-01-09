import asyncio

async def tcp_echo_client(message):
    reader, writer = await asyncio.open_unix_connection('./echo.sock')

    print(f'Send: {message!r}')
    writer.write(message.encode())
    writer.write_eof()

    data = await reader.read(100)
    print(f'Received: {data.decode()!r}')

    print('Close the connection')
    writer.close()
    await writer.wait_closed()

async def main():
    while True:
        await tcp_echo_client("foo")
        await asyncio.sleep(1)

asyncio.run(main())
