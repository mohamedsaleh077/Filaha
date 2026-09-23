import asyncio
from google import genai

async def get_ai_respond(msg):
    client = genai.Client()

    # Use client.aio for asynchronous requests
    interaction = await client.aio.interactions.create(
        model="gemma-4-26b-a4b-it",
        input=msg
    )
    
    return interaction.output_text


print(asyncio.run(get_ai_respond("HI")))