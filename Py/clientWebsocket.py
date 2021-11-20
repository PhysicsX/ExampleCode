#!/usr/bin/env python

import asyncio
import websockets
import threading
import sys

async def hello():
    for x in range(100000):
        async with websockets.connect("ws://localhost:8083") as websocket:
            await websocket.send(str(x))
            name = await websocket.recv()
            #print("< {}".format(name))
            print(name,end = ' ', flush=True)
            sys.stdout.flush()

#asyncio.run(hello())


async def main():

    await asyncio.wait([
        hello(),
        hello(),
        hello(),
        hello(),
        hello(),
        hello(),
        hello(),
        hello(),
        hello(),
        hello(),
        hello()
])

loop = asyncio.get_event_loop()
loop.run_until_complete(main())