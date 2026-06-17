from fastapi import FastAPI, Depends, HTTPException
from sqlalchemy.orm import Session
import server.models as models
import server.schemas as schemas
from server.database import get_db, engine
from typing import List
from fastapi.middleware.cors import CORSMiddleware

models.Base.metadata.create_all(bind=engine)

app = FastAPI(title="Game State API")


app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:3000"],
    allow_methods=["*"],
    allow_headers=["*"],
)


@app.get("/turns", response_model=List[schemas.MatchResponse])
def get_all_turns(db: Session = Depends(get_db)):
    return db.query(models.Match).order_by(models.Match.id.desc()).all()


@app.get("/turn/{match_id}", response_model=schemas.MatchResponse)
def get_turn(match_id: int, db: Session = Depends(get_db)):
    match = (
        db.query(models.Match)
        .filter(models.Match.id == match_id)
        .order_by(models.Match.id.desc())
        .first()
    )
    if not match:
        raise HTTPException(status_code=404, detail="Match not found")
    return match
