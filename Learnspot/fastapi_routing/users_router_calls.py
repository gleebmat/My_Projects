from fastapi import APIRouter
from output_models.translation_output import (
    Translation_of_words,
    reverso_translation_output,
)
from fastapi import Depends
from schemas.schemas import Translation_input as TranslationSchemas
from sqlalchemy.orm import Session
from dependencies.dependency import get_db
from databases.models.models import User
from dependencies.dependency import get_current_user
from schemas.schemas import UserRequest, UserResponse
from fastapi import HTTPException

router = APIRouter()


@router.post("/users/create_user", response_model=UserResponse)
def create_user(payload: UserRequest, db: Session = Depends(get_db)):
    if db.query(User).filter(User.login == payload.login).scalar():
        raise HTTPException(status_code=400, detail="Sorry, this User already exists")
    user = User(login=payload.login)
    db.add(user)
    db.commit()
    return user
