import asyncio
import random

import sim4life


async def wait_for_sim4life(f, id):
    while(not f.ready()):
        await asyncio.sleep(0.1)
    print(f"sim4life task {id} done")

async def main():
    tasks = [wait_for_sim4life(sim4life.wait_async(random.randint(1,5)), i) for i in range(10)]
    await asyncio.gather(*tasks)
    

loop = asyncio.get_event_loop()
loop.run_until_complete(main())
loop.close()
