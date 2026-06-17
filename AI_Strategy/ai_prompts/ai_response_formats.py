from pydantic import BaseModel, Field
from typing import Literal, Union, List


class Turn_Move(BaseModel):
    unit_index: int = Field(description="unit_index")
    action_type: str = "move"
    dx: int = Field(description="dx")
    dy: int = Field(description="dy")


class Turn_Attack(BaseModel):
    unit_index: int = Field(description="unit_index")
    action_type: str = "attack"
    target_index: int = Field(
        description="the index of the enemy unit you want to attack"
    )


class Whole_Turn(BaseModel):
    explanation: str = Field(
        description="A detailed explanation of the reasoning behind the chosen actions, including tactical considerations and how they align with the overall strategy to win the game."
    )
    actions: List[Union[Turn_Move, Turn_Attack]] = Field(
        description="A list of exactly 2 actions to perform this turn. Each action can be either a move or an attack (lowercase).",
        min_length=2,
        max_length=2,
    )
