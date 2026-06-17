import requests
import json


def reverso_get_data(text: str, source="en", target="de") -> dict:
    url = "https://api.reverso.net/translate/v1/translation"

    payload = {
        "input": text,
        "from": source,
        "to": target,
        "options": {
            "contextResults": True,
            "languageDetection": True,
            "origin": "translation.web",
            "sentenceSplitter": True,
        },
        "format": "text",
    }

    headers = {
        "Content-Type": "application/json",
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/144.0.0.0 Safari/537.36",
        "Accept": "application/json",
        "Origin": "https://www.reverso.net",
        "Referer": "https://www.reverso.net/",
    }

    response = requests.post(url, json=payload, headers=headers)
    try:
        result = response.json()
    except Exception:
        raise Exception(response.status_code, response.text)

    return result


def reverso_translate_words(data: dict) -> list:
    translations = [
        item["translation"]
        for item in data["contextResults"]["results"]
        if item["translation"] != ""
    ]
    return translations or [data.get("translation", [None])[0]]


def reverso_original_examples(data: dict) -> list:
    translations = [
        sentence.replace("<em>", "").replace("</em>", "")
        for item in data["contextResults"]["results"]
        for sentence in item.get("sourceExamples", [])
    ]
    return translations or [data.get("translation", [None])[0]]


def reverso_translated_examples(data: dict) -> list:
    translations = [
        sentence.replace("<em>", "").replace("</em>", "")
        for item in data["contextResults"]["results"]
        for sentence in item.get("targetExamples", [])
    ]
    return translations or [data.get("translation", [None])[0]]
