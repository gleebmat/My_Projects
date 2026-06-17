import json
import os
import sys
from openai import OpenAI
from ai_prompts.ai_prompts import prompts_for_initial_start as initial_prompt
from ai_prompts.ai_prompts import (
    prompts_before_parsing,
    important_prompt_before_parsing,
)
from ai_prompts.ai_response_formats import Whole_Turn
from dotenv import load_dotenv
from server.database import SessionLocal
import server.models as models

load_dotenv()

client = OpenAI()
client.api_key = os.getenv("OPENAI_API_KEY")


def load_game_data():
    # 1. Verify and read the game state file written by C++
    game_state = "game_state.json"
    game_config = "game_config.json"

    if not os.path.exists(game_state):
        print(
            f"[Python AI] Error: '{game_state}' not found. Did C++ write it successfully?"
        )
        sys.exit(1)
    if not os.path.exists(game_config):
        print(
            f"[Python AI] Error: '{game_config}' not found. Did C++ write it successfully?"
        )
        sys.exit(1)

    try:
        with open(game_config, "r") as f:
            game_config = json.load(f)
        with open(game_state, "r") as f:
            game_state = json.load(f)

        return game_config, game_state
    except Exception as e:
        print(f"[Python AI] Error reading JSON file: {e}")
        sys.exit(1)


def main():

    try:
        print("[Python AI] Starting AI processing...")

        game_config, game_state = load_game_data()
        rules = game_config.get("rules", [])

        action_num = game_state.get("action_number", 1)
        ai_units = game_state.get("ai_units", [])
        human_units = game_state.get("human_units", [])
        instructions = initial_prompt + str(rules)

        prompt = f"Tactical phase: Action {action_num}/2\n\n"

        instructions += f"""=== INITIAL UNITS CHARACTERISTICS ===\n
        {game_config.get("unit_characteristics")}\n"""

        prompt += "\n=== OCCUPIED TILES ===\n"

        for u in ai_units:
            if u["can_act"]:
                prompt += f"AI Unit occupies ({u['x']}, {u['y']})\n"

        for u in human_units:
            if u["alive"]:
                prompt += f"Enemy occupies ({u['x']}, {u['y']})\n"
        prompt += "\n=== YOUR SQUAD (AI SQUAD) ===\n"
        for u in ai_units:
            prompt += f"Index: {u['index']} | Type: {u['type']} | X: {u['x']} | Y: {u['y']} | HP: {u['hp']} | Max_Move: {u['max_move']} | Range: {u['range']} | can_act: {u['can_act']}\n"

        prompt += "\n=== ENEMY SQUAD (PLAYER SQUAD) ===\n"
        for u in human_units:
            prompt += f"Index: {u['index']} | Type: {u['type']} | X: {u['x']} | Y: {u['y']} | HP: {u['hp']} | Alive: {u['alive']}\n"

        prompt += "\n=== ATTACKABLE TARGETS FOR EACH AI UNIT (your units)===\n"
        for u in ai_units:
            if u["can_act"]:
                prompt += (
                    f"Unit Index: {u['index']} | "
                    f"Attackable Targets: {u['attackable_targets']}\n"
                )
        prompt += "\n=== ATTACKABLE TARGETS FOR EACH ENEMY UNIT (enemy units)===\n"
        for u in human_units:
            if u["alive"]:
                prompt += (
                    f"Unit Index: {u['index']} | "
                    f"Attackable Targets: {u['attackable_targets']}\n"
                )
        try:
            response = client.chat.completions.parse(
                model="gpt-4o",
                messages=[
                    {
                        "role": "system",
                        "content": instructions
                        + prompts_before_parsing
                        + important_prompt_before_parsing,
                    },
                    {"role": "user", "content": prompt},
                ],
                temperature=0.3,
                response_format=Whole_Turn,
            )

            raw_output = response.choices[0].message.parsed
            ai_decision_dict = raw_output.model_dump()
        except Exception as e:
            print(f"[Python AI] Error during OpenAI API call: {e}")
            # Save the result to the file
            # Save the result to the file for C++ runtime
        with open("ai_action.json", "w") as f:
            json.dump(ai_decision_dict, f, indent=2)

        print("[Python AI] Syncing board telemetry with PostgreSQL database...")
        db = SessionLocal()
        try:
            new_match = models.Match()

            db.add(new_match)
            db.commit()
            db.refresh(new_match)
            hp_data = {
                f"unit_{u['index']}": u["hp"] for u in game_state.get("ai_units", [])
            }
            current_turn = game_state.get("action_number", 1)
            acting_team_name = game_state.get("acting_team", "Unknown Team")

            new_turn = models.TurnTelemetry(
                turn_number=current_turn,
                ai_explanation=ai_decision_dict.get("explanation", ""),
                team=acting_team_name,
                hp_units=hp_data,
                match_id=new_match.id,
            )

            db.add(new_turn)
            db.commit()
        except Exception as e:
            print(f"[Python AI] Error syncing with database: {e}")
        finally:
            db.close()
    except Exception as e:
        print(f"[Python AI] Unexpected error: {e}")
        sys.exit(1)


if __name__ == "__main__":
    main()
