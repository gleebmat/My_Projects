import os
import json
from dotenv import load_dotenv
from openai import OpenAI
from pydantic import BaseModel, Field
from agents_classes import agent_classes
from agents_classes import agents_descriptions
from agents_classes.agents_descriptions import (
    system_prompt_for_chatting,
    system_prompt_for_handling_user_data,
    description_for_making_tests,
)
from databases.services.service import save_for_future_practice_ai

load_dotenv()
client = OpenAI(api_key=os.getenv("OPENAI_API_KEY"))


def text_improvements(user_text: str):
    completion = client.beta.chat.completions.parse(
        model="gpt-4o-mini",
        messages=[
            {
                "role": "system",
                "content": agents_descriptions.system_prompt_for_improving_texts,
            },
            {"role": "user", "content": user_text},
        ],
        response_format=agent_classes.Format_for_improved_text,
    )
    result = completion.choices[0].message.parsed
    return result


def chat_with_model(messages):
    system_prompt = {
        "role": "system",
        "content": system_prompt_for_chatting,
    }

    completion = client.chat.completions.create(
        model="gpt-4o-mini", messages=[system_prompt] + messages
    )

    return completion.choices[0].message.content


def handle_user_data(data):
    unique_data = list(dict.fromkeys(data))

    data_text = "/&&/ ".join(unique_data)
    completion = client.beta.chat.completions.parse(
        model="gpt-4o-mini",
        messages=[
            {"role": "system", "content": system_prompt_for_handling_user_data},
            {"role": "user", "content": data_text},
        ],
        response_format=agent_classes.Format_for_handled_data,
    )
    result = completion.choices[0].message.parsed
    return result


def practice_ai_tests(database):
    data = [{"words": each.words} for each in database]
    completion = client.beta.chat.completions.parse(
        model="gpt-4o-mini",
        messages=[
            {"role": "system", "content": description_for_making_tests},
            {"role": "user", "content": json.dumps(data)},
        ],
        response_format=agent_classes.Full_Format_for_tests,
    )
    result = completion.choices[0].message.parsed

    return result
