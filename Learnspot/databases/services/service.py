from sqlalchemy.orm import Session
from databases.models.models import Translation, Texts
from databases.models.models import Words_to_practice, Words_to_practice_ai


def save_record_of_translations(db: Session, translated_words: list[str], user_id: int):
    record = Translation(
        user_id=user_id,
        charachteristics="translated_words",
        translated_words=translated_words,
    )

    db.add(record)
    db.commit()
    db.refresh(record)

    return record


def save_record_of_improved_texts(
    db: Session,
    original_text: str,
    mistakes_solutions: list[str],
    improved_text: str,
    user_id: int,
):
    record = Texts(
        user_id=user_id,
        characteristics="improved_text",
        original_text=original_text,
        mistakes_solutions=mistakes_solutions,
        improved_text=improved_text,
    )

    db.add(record)
    db.commit()
    db.refresh(record)

    return record


def build_messages(history, new_message: str):
    messages = []

    for msg in history:
        messages.append({"role": msg.role, "content": msg.content})

    messages.append({"role": "user", "content": new_message})

    return messages


def save_for_future_practice(db: Session, words: str, user_id: int):
    new_word = Words_to_practice(user_id=user_id, words=words)
    db.add(new_word)
    db.commit()
    db.refresh(new_word)
    pass


def save_for_future_practice_ai(db: Session, words: str, user_id: int):
    new_words = Words_to_practice_ai(user_id=user_id, words=words)
    db.add(new_words)
    db.commit()
    db.refresh(new_words)
