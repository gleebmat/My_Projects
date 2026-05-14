from fastapi import HTTPException
from pydantic import BaseModel, Field, field_validator


class Translation_input(BaseModel):
    translation: str = Field(..., max_length=1000)

    @field_validator("translation")
    def empty(cls, v: str) -> str:
        v = v.strip()

        if not v:
            raise ValueError(...)
        return v


class UserRequest(BaseModel):
    login: str = Field(..., max_length=127)

    @field_validator("login")
    def empty(cls, v: str) -> str:
        v = v.strip()

        if not v:
            raise ValueError("Your login cannot be empty")

        return v


class UserResponse(UserRequest):
    model_config = {"from_attributes": True}

    id: int
