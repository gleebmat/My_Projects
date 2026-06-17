from pydantic import BaseModel
from typing import Any, List, Optional, Dict


class TurnTelemetryResponse(BaseModel):
    id: int
    team: str
    hp_units: Dict[str, Any]
    ai_explanation: Optional[str] = None

    class Config:
        from_attributes = True


class MatchResponse(BaseModel):
    id: int
    turns: List[TurnTelemetryResponse] = []

    class Config:
        from_attributes = True
