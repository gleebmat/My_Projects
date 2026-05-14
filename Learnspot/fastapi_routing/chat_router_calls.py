from fastapi import APIRouter, HTTPException
from fastapi import Depends
from sqlalchemy.orm import Session
from databases.models.models import User
from dependencies.dependency import get_current_user, get_db
from output_models.translation_output import ChatRequest, ChatResponse
from databases.services.service import build_messages, save_for_future_practice
from databases.models.models import Conversation, ChatMessage
from requests_to_openai.request_to_openai import chat_with_model

router = APIRouter()


@router.post("/chat", response_model=ChatResponse)
def chat_with_ai_agent(
    request: ChatRequest,
    db: Session = Depends(get_db),
    current_user: User = Depends(get_current_user),
):
    conversation = db.get(Conversation, request.conversation_id)
    if conversation is None:
        raise HTTPException(status_code=404, detail="Conversation not found")
    if conversation.user_id != current_user.id:
        raise HTTPException(status_code=403, detail="Not allowed")
    history = conversation.messages
    messages = build_messages(history=history, new_message=request.message)
    reply = chat_with_model(messages)
    save_for_future_practice(db=db, user_id=current_user.login, words=reply)
    db.add_all(
        [
            ChatMessage(
                conversation_id=conversation.id, role="user", content=request.message
            ),
            ChatMessage(
                conversation_id=conversation.id, role="assistant", content=reply
            ),
        ]
    )

    db.commit()

    return ChatResponse(response=reply, conversation_id=conversation.id)


@router.post("/conversations/create_new_conversation")
def create_new_conversation(
    db: Session = Depends(get_db), current_user: User = Depends(get_current_user)
):
    conversation = Conversation(user_id=current_user.id)
    db.add(conversation)
    db.commit()
    db.refresh(conversation)

    return {"conversation_id": conversation.id}


@router.get("/conversations/get_all_conversations")
def get_all_conversations(
    db: Session = Depends(get_db), current_user: User = Depends(get_current_user)
):
    conversations = (
        db.query(Conversation).filter(Conversation.user_id == current_user.id).all()
    )
    return [{"id": c.id, "title": f"Chat {c.id}"} for c in conversations]


@router.get("/conversations/{conversation_id}/messages")
def get_conversation_messages(
    conversation_id: int,
    db: Session = Depends(get_db),
    current_user: User = Depends(get_current_user),
):
    conversation = db.get(Conversation, conversation_id)

    if conversation is None:
        raise HTTPException(status_code=404, detail="Conversation not found")

    if conversation.user_id != current_user.id:
        raise HTTPException(status_code=403, detail="Not allowed")

    messages = (
        db.query(ChatMessage)
        .filter(ChatMessage.conversation_id == conversation_id)
        .order_by(ChatMessage.id.asc())
        .all()
    )

    return [
        {
            "role": m.role,
            "content": m.content,
            "id": m.id,
        }
        for m in messages
    ]
