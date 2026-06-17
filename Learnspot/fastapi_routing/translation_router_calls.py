from fastapi import APIRouter
from output_models.translation_output import (
    Translation_of_words,
    reverso_translation_output,
)
from databases.services.service import (
    save_record_of_translations,
    save_for_future_practice,
)
from fastapi import Depends
from schemas.schemas import Translation_input as TranslationSchemas
from sqlalchemy.orm import Session
from dependencies.dependency import get_db
from databases.models.models import Translation as TranslationModels
from databases.models.models import User
from dependencies.dependency import get_current_user


router = APIRouter()


@router.post("/translation/translate", response_model=Translation_of_words)
def tranlsation_of_words(
    user_input: TranslationSchemas,
    db: Session = Depends(get_db),
    current_user: User = Depends(get_current_user),
):
    text = user_input.translation

    result = reverso_translation_output(db, text)

    save_record_of_translations(
        db=db, translated_words=result["translation"] or [], user_id=current_user.login
    )
    save_for_future_practice(
        db=db, user_id=current_user.login, words=result["translation"][0]
    )
    return result


@router.get("/translation/get_all_translations")
def get_all_translations(
    db: Session = Depends(get_db), current_user: User = Depends(get_current_user)
):
    return (
        db.query(TranslationModels)
        .filter(TranslationModels.user_id == current_user.login)
        .all()
    )
