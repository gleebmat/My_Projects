from pydantic import BaseModel, Field
from typing import Optional
from requests_to_reverso import requests_to_reverso as requests_to_reverso
from sqlalchemy.orm import Session


class Translation_of_words(BaseModel):
    model_config = {"from_attributes": True}

    translation: Optional[list[str]] = Field(default_factory=list)
    translated_examples: Optional[list[str]] = Field(default_factory=list)
    original_examples: Optional[list[str]] = Field(default_factory=list)


def reverso_translation_output(db: Session, user_data: str = "") -> dict:

    data = requests_to_reverso.reverso_get_data(text=user_data)
    translation = requests_to_reverso.reverso_translate_words(data)
    original_examples = requests_to_reverso.reverso_original_examples(data)
    translated_examples = requests_to_reverso.reverso_translated_examples(data)
    return {
        "translation": translation,
        "original_examples": original_examples,
        "translated_examples": translated_examples,
    }


class Reader_output(BaseModel):
    model_config = {"from_attributes": True}

    improved_text: str | None = None
    mistakes_solutions: list[str] | None = None
    is_processable: bool = None


class ChatRequest(BaseModel):
    message: str
    conversation_id: int = 1


class ChatResponse(BaseModel):
    response: str
