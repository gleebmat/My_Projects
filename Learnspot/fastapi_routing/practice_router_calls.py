from fastapi import APIRouter
from fastapi import Depends
from sqlalchemy.orm import Session
from databases.models.models import User
from dependencies.dependency import get_current_user, get_db
from databases.models.models import Words_to_practice, Words_to_practice_ai
from requests_to_openai.request_to_openai import (
    handle_user_data,
    practice_ai_tests,
)
from databases.services.service import save_for_future_practice_ai

router = APIRouter()


@router.get("/practice/get_all_words")  # all the words stored from different stages
def get_all_words_for_practice(
    db: Session = Depends(get_db), current_user: User = Depends(get_current_user)
):
    return (
        db.query(Words_to_practice)
        .filter(Words_to_practice.user_id == current_user.login)
        .all()
    )


@router.get(
    "/practice/let_ai_handle_your_data"
)  # we let agent decide what to store from the all-data database
def handling(
    db: Session = Depends(get_db), current_user: User = Depends(get_current_user)
):

    records = (
        db.query(Words_to_practice)
        .filter(Words_to_practice.user_id == current_user.login)
        .all()
    )
    data = [record.words for record in records]
    result = handle_user_data(data)
    save_for_future_practice_ai(
        db=db, user_id=current_user.login, words=result.handled_data
    )
    return result


@router.get("/practice/handled_data_by_ai")
def show_data_handled_by_ai(
    db: Session = Depends(get_db), current_user: User = Depends(get_current_user)
):
    return (
        db.query(Words_to_practice_ai)
        .filter(Words_to_practice_ai.user_id == current_user.login)
        .all()
    )


@router.post("/practice/practice_with_AI-Assistant")
def practice_with_ai_assistant(
    db: Session = Depends(get_db), current_user: User = Depends(get_current_user)
):
    return practice_ai_tests(
        db.query(Words_to_practice_ai)
        .filter(Words_to_practice_ai.user_id == current_user.login)
        .all()
    )
