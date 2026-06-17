from pydantic import BaseModel, Field, conlist
from typing import Optional
from agents_classes import agents_descriptions


class Format_for_improved_text(BaseModel):
    improved_text: str = Field(
        description=agents_descriptions.description_for_improved_text
    )
    mistakes_solutions: list[str] = Field(
        description=agents_descriptions.description_for_providing_mistakes_solutions
    )
    is_processable: bool = Field(
        description=agents_descriptions.description_for_rules_confidence
    )


class Format_for_handled_data(BaseModel):
    handled_data: list[str] = Field(
        description=agents_descriptions.description_for_handled_data
    )


class Format_for_tests(BaseModel):
    question_number: int = Field(desciption="The number of the question")
    text_of_question: str = Field(
        description="The full description of the task! Just without the final question"
    )
    task: str = Field(description="Just write the question itself")
    answer: str = Field(
        description="Write the full and detailed answer to your question, explain everything just as you wish the user has answered"
    )


class Full_Format_for_tests(BaseModel):
    questions: list[Format_for_tests] = Field(
        min_length=10, max_length=10, description="List of exactly 10 questions"
    )
