from sqlalchemy import Column, Integer, ForeignKey, String, Text, JSON
from sqlalchemy.orm import relationship
from server.database import Base


class Match(Base):
    __tablename__ = "matches"

    id = Column(Integer, primary_key=True, index=True)
    turns = relationship(
        "TurnTelemetry", back_populates="match", cascade="all, delete-orphan"
    )


class TurnTelemetry(Base):
    __tablename__ = "turn_telemetry"
    id = Column(Integer, primary_key=True, index=True)
    ai_explanation = Column(Text)
    match_id = Column(Integer, ForeignKey("matches.id"))
    team = Column(String, index=True)
    hp_units = Column(JSON)
    match = relationship("Match", back_populates="turns")
    turn_number = Column(Integer, index=True)
