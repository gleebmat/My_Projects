from fastapi import APIRouter
from fastapi import Depends
from sqlalchemy.orm import Session
from databases.models.models import User
from dependencies.dependency import get_current_user, get_db
from output_models.translation_output import Reader_output
from requests_to_openai.request_to_openai import text_improvements
from databases.services.service import (
    save_record_of_improved_texts,
    save_for_future_practice,
)
from databases.models.models import Texts

router = APIRouter()


@router.get("/texts", response_model=Reader_output)
def text_improvement(
    text: str,
    db: Session = Depends(get_db),
    current_user: User = Depends(get_current_user),
):
    result = text_improvements(user_text=text)
    save_record_of_improved_texts(
        db=db,
        original_text=text,
        mistakes_solutions=result.mistakes_solutions,
        improved_text=result.improved_text,
        user_id=current_user.login,
    )
    save_for_future_practice(
        db=db, words=result.improved_text, user_id=current_user.login
    )

    return result


@router.get("/texts/all")
def get_all_texts(
    db: Session = Depends(get_db), current_user: User = Depends(get_current_user)
):
    return db.query(Texts).filter(Texts.user_id == current_user.login).all()
